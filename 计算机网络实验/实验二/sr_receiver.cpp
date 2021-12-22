#include "stdafx.h"
#include "sr_receiver.h"
#include "Global.h"
using namespace std;

sr_receiver::sr_receiver() :k(8), N(4), ifrcv(new bool[8]), rcvwinbuf(new Packet[8])
{
	//��ʼ��
	base = 0;
	for (int i = 0; i < k; i++) { //��ʼ����ʱ�򣬴���������λ�ö�û��ռ��
		ifrcv[i] = false;
	}
	lastAckPkt.acknum = -1; //��ʼ״̬�£��ϴη��͵�ȷ�ϰ���ȷ�����Ϊ-1��ʹ�õ���һ�����ܵ����ݰ�����ʱ��ȷ�ϱ��ĵ�ȷ�Ϻ�Ϊ-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//���Ը��ֶ�
	memset(lastAckPkt.payload, '.', Configuration::PAYLOAD_SIZE);
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

sr_receiver::~sr_receiver() {
	delete[] ifrcv;
	delete[] rcvwinbuf;
}

//���ն˽��ܷ���
void sr_receiver::receive(const Packet& packet) {
	int checksum;
	checksum = pUtils->calculateCheckSum(packet);
	if (checksum != packet.checksum) { //У��ʹ��󣬷�����
		pUtils->printPacket("���շ������鱻�𻵣�У���벻��ȷ", packet);
		//���ﲻ��GBNһ���ش����ack���ȴ���ʱ�ش�
		return;
	}
	else {
		if (inrcvbuf(packet.seqnum) == false) { //���ڽ��մ����ڣ�������һ��ACK
			pUtils->printPacket("���շ������������ķ��� ", packet);
			lastAckPkt.acknum = packet.seqnum; //����ack
			lastAckPkt.seqnum = -1; //��������ֶ�
			memset(lastAckPkt.payload, '.', Configuration::PAYLOAD_SIZE);
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);
			return;
		}
		else { //����ǵ�ǰ�����ڵ����ݣ����������򻬶����ڻ��߻��棬����ack
			cout << "���շ����յ����ݰ������Ϊ��" << packet.seqnum << endl;
			rcvwinbuf[packet.seqnum] = packet; //�����и�λ�ñ�����ռ��
			ifrcv[packet.seqnum] = true; //����ǰ��ű�Ϊ�Ѿ�����
			lastAckPkt.acknum = packet.seqnum; //����ack
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt); //����У���
			pUtils->printPacket("���շ������յ����շ���Ҫ�ĵ�ǰ���飬����ack", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt); //����ACK�����ͷ�
			int i = 0;
			while (ifrcv[base] == true && i <= 4) { //�ƶ����ڣ����ͻ�������
				i++;
				//��ȡ���ݣ�����Ӧ�ò�
				Message data;
				memcpy(data.data, rcvwinbuf[base].payload, sizeof(rcvwinbuf[base].payload));
				pns->delivertoAppLayer(RECEIVER, data);
				ifrcv[base] = false; //���ֶι黹Ϊû�н��ܵ�״̬
				base = (base + 1) % k; //������һ�����
			}
			cout << "���շ������ն˴��ڻ�����\n";
			showbuf();
		}
	}
}

//�жϵ�ǰ�����Ƿ��ڷ��ͷ�������
bool sr_receiver::inrcvbuf(int seqnum)
{
	int end = (base + N) % k;
	//����������������Ƿ��ͷ�����ĩβ�����кŴ�����ʼ���кţ�֤����������
	if (base < end) {
		//�÷������к�seqnumҪ�����ڷ��ʹ��ڵ���β���֮��
		return seqnum < end&& seqnum >= base;
	}
	else {
		//����ĩβ���к�С����ʼ���кţ�
		//֤���������Ǵӿ�ʼ���кŵ�k-1,Ȼ���ٴ�0��ĩβ�����ǽ��������������Χ
		return seqnum >= base || seqnum < end;
	}
}

//��ӡ���ʹ���
void sr_receiver::showbuf()
{
	for (int i = 0; i < k; i++) { //�������ڿ�ͷ�������
		if (i == base) {
			cout << "(";
			printf("(");
		}
		//�ڷ��ͻ������ڵ�Ԫ��
		if (inrcvbuf(i) && ifrcv[i] == true) { //�Ѿ������״̬
			cout << i << ":stored";
			printf("%d:stored", i);
		}
		else if (inrcvbuf(i)) { //��������û���棬��״̬
			cout << i << ":empty";
			printf("%d:empty", i);
		}
		if (i == (base + N) % k) {
			cout << ")"; //�������ڽ�β���������
			printf(")");
		}
		if (inrcvbuf(i) == false) {
			cout << i << ":X"; //���ڴ����ڵ�Ԫ��
			printf("%d:X");
		}
		cout << " ";
		printf(" ");
	}
	cout << "\n";
	printf("\n");
}