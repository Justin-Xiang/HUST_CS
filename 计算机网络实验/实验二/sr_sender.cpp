#include "stdafx.h"
#include "sr_sender.h"
#include "Global.h"
#include "Tool.h"
using namespace std;

sr_sender::sr_sender() :k(8), N(4), ifrcv(new bool[8]), sndwinbuf(new Packet[8])
{
	base = 0;
	nextseqnum = 0;
	//���Ƚ�����״̬ȫ����Ϊδ����
	for (int i = 0; i < k; i++) {
		ifrcv[i] = false;
	}
}

sr_sender::~sr_sender() {
	delete[] sndwinbuf;
	delete[] ifrcv;
}

bool sr_sender::send(const Message& message) {
	if (getWaitingState()) {
		pUtils->printPacket("���ͷ������ʹ��������޷�����", sndwinbuf[nextseqnum]);
		return false;
	}
	else if (insendbuf(nextseqnum)) {
		//����ڴ����� ����
		sndwinbuf[nextseqnum].acknum = -1; //���Ը��ֶ�
		sndwinbuf[nextseqnum].seqnum = nextseqnum; //��һ��Ҫ���͵����кţ�
		memcpy(sndwinbuf[nextseqnum].payload, message.data, sizeof(message.data)); //data
		sndwinbuf[nextseqnum].checksum = pUtils->calculateCheckSum(sndwinbuf[nextseqnum]); //����checksum
		pUtils->printPacket("���ͷ������ͷ����ͱ���Ϊ", sndwinbuf[nextseqnum]);
		//���ͱ���ǰ�ķ��ͷ�����
		cout << "���ͷ������ͷ�����ǰ�Ļ������ڣ�\n";
		showbuf();
		//Ϊÿһ�����飬������ʱ��
		pns->startTimer(SENDER, Configuration::TIME_OUT, nextseqnum);
		//���͸����շ�
		pns->sendToNetworkLayer(RECEIVER, sndwinbuf[nextseqnum]);
		nextseqnum = (nextseqnum + 1) % k; //׼��������һ������
		cout << "���ͷ������ͷ����ͺ�Ļ������ڣ�\n";
		showbuf();
		return true;

	}
	else { //ֱ�Ӻ���
		return false;
	}
}

void sr_sender::receive(const Packet& ackpkt) {
	//���ȱȽ�У��� ����Ƿ���
	int checksum;
	checksum = pUtils->calculateCheckSum(ackpkt);
	if (checksum != ackpkt.checksum) {
		pUtils->printPacket("���ͷ���У��Ͳ���ȷ�����鱻��", ackpkt);
		return;
	}
	else { //����׼�����շ��صı���
		if (insendbuf(ackpkt.acknum)) {
			cout << "���ͷ����Ѿ����յ�ACK��" << ackpkt.acknum << endl;
			pns->stopTimer(SENDER, ackpkt.acknum); //ֹͣ��ʱ
			ifrcv[ackpkt.acknum] = true; //����ǰ������Ϊ�ѱ�����
			while (ifrcv[base] == true) { //ѭ���������ڣ���û�з���Ϊֹ
				ifrcv[base] = false; //�ͷŸô���
				base = (base + 1) % k; //����ƶ�����
			}
			//���յ�ACK�󻬶������ƶ�
			cout << "���ͷ����յ����շ����ص�ACK,�������ڱ�Ϊ��\n";
			showbuf();
		}
	}
}

//�Ƿ�Ҫ�ȴ�
bool sr_sender::getWaitingState() {
	int limitseq = base + N;
	int crntcap = limitseq % k; //Ŀǰ���������������
	int crntocup = nextseqnum % k; //Ŀǰռ�õ������
	 return (crntcap == crntocup); //�жϵ�ǰ������Ƿ��Ѿ������ڵ�ĩβ
}

//��ʱ֮���ش�
void sr_sender::timeoutHandler(int seqnum)
{
	//�����ݰ���ʱ�������ش�
	pUtils->printPacket("���ͷ����з��鷢����ʱ", sndwinbuf[seqnum]);
	pns->sendToNetworkLayer(RECEIVER, sndwinbuf[seqnum]);
	pns->stopTimer(SENDER, seqnum); //��seqnum������ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqnum); //��seqnum������ʱ��
	pUtils->printPacket("���ͷ����ش����", sndwinbuf[base]);
}

//�ж��Ƿ��ڷ��ͷ�������
bool sr_sender::insendbuf(int seqnum)
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
void sr_sender::showbuf()
{
	for (int i = 0; i < k; i++) { //�������ڿ�ͷ�������
		if (i == base) {
			cout << "(";
			printf("(");
		}
		//�ڷ��ͻ������ڵ�Ԫ��
		if (insendbuf(i) && i >= nextseqnum) {
			cout << i << ":empty"; //�����ڣ���״̬
			printf("%d:empty", i);
		}
		else if (insendbuf(i) && ifrcv[i] == false) { //�����ڣ��ѷ���ûack״̬
			cout << i << ":sent";
			printf("%d:send", i);
		}
		else if (insendbuf(i) && ifrcv[i] == true) { //ack״̬
			cout << i << ":acked";
			printf("%d:acked", i);
		}
		if (i == (base + N) % k)
		{
			cout << ")"; //�������ڽ�β���������
			printf(")");
		}
		if (insendbuf(i) == false)
		{
			cout << i << ":N"; //���ڴ����ڵ�Ԫ��
			printf("%d:N", i);
		}
		cout << " ";
		printf(" ");
	}
	cout << "\n";
	printf("\n");
}