#include "stdafx.h"
#include "tcp_sender.h"
#include "Global.h"
using namespace std;

tcp_sender::tcp_sender() :k(8), N(4), sndwinbuf(new Packet[8])
{
	//��ʼ��
	base = 0;
	nextseqnum = 0;
	resend = 0;
}

tcp_sender::~tcp_sender() {

}

//�����ķ��͸����շ�
bool tcp_sender::send(const Message& message) {
	if (getWaitingState()) {
		pUtils->printPacket("���ͷ������ʹ��������޷�����", sndwinbuf[nextseqnum]);;
		return false;
	}
	else { //������һ��Ҫ���ķ���
		sndwinbuf[nextseqnum].acknum = -1; //���Ը��ֶ�
		sndwinbuf[nextseqnum].seqnum = nextseqnum; //��һ��Ҫ���͵����кţ�
		sndwinbuf[nextseqnum].checksum = 0; //��ʼchecksum��0
		memcpy(sndwinbuf[nextseqnum].payload, message.data, sizeof(message.data)); //data
		sndwinbuf[nextseqnum].checksum = pUtils->calculateCheckSum(sndwinbuf[nextseqnum]); //����checksum
		pUtils->printPacket("���ͷ������ͷ����ͱ���", sndwinbuf[nextseqnum]);
		//չʾ��������
		cout << "���ͷ������ͷ�����ǰ�Ļ������ڣ�\n";
		showbuf();
		//��base=nextseqnumʱ��������ʱ��
		if (base == nextseqnum) {
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		}
		//�����ķ��͸����շ�
		pns->sendToNetworkLayer(RECEIVER, sndwinbuf[nextseqnum]);
		nextseqnum = (nextseqnum + 1) % k; //׼��������һ������
		cout << "���ͷ������ͷ����ͺ�Ļ������ڣ�\n";
		showbuf();
		return true;
	}
}

void tcp_sender::receive(const Packet& ackpkt)
{
	//�Ƚ�У��ͣ��������Ƿ���
	int checksum;
	checksum = pUtils->calculateCheckSum(ackpkt);
	if (checksum != ackpkt.checksum) {
		pUtils->printPacket("���ͷ���У��Ͳ���ȷ��������", ackpkt);
		return;
	}
	else { //����׼�����շ��صı���
		if (insendbuf(ackpkt.acknum)) {
			cout << "���ͷ������յ�ACK��" << ackpkt.acknum << endl;
			base = (ackpkt.acknum + 1) % 8;
			pns->stopTimer(SENDER, 0);
			if (base != nextseqnum) {
				pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
			}
			resend = 0;
			//����ACK��Ļ�������
			cout << "���ͷ������ͷ�����ACK��Ļ������ڣ�\n";
			showbuf();
		}
		else {
			if (resend == 3) {
				pns->sendToNetworkLayer(RECEIVER, sndwinbuf[base]);
				resend = 0;
				pUtils->printPacket("\n\n���ͷ����յ���������ACK�������ش�", sndwinbuf[base]);
			}
			else {
				resend = resend + 1;
			}
		}
	}
}

//�Ƿ�Ӧ�õȴ�
bool tcp_sender::getWaitingState() //trueΪ��������Ҫ�ȴ���
{
	int limitseq = base + N;
	int crntcap = limitseq % k; //Ŀǰ���������������
	int crntocup = nextseqnum % k; //Ŀǰռ�õ������
	return crntcap == crntocup;
}

//��ʱ��֮���ش��������
void tcp_sender::timeoutHandler(int seqnum)
{
	pUtils->printPacket("���ͷ����з��鷢����ʱ", sndwinbuf[base]);
	pns->sendToNetworkLayer(RECEIVER, sndwinbuf[base]);
	pns->stopTimer(SENDER, 0);
	pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	pUtils->printPacket("���ͷ����ش����", sndwinbuf[base]);
}

//�жϵ�ǰ�����Ƿ��ڷ��ͷ�������
bool tcp_sender::insendbuf(int seqnum)
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
void tcp_sender::showbuf()
{
	for (int i = 0; i < k; i++) { //�������ڿ�ͷ�������
		if (i == base)
		{
			cout << "(";
			printf("(");
		}
		cout << i;
		printf("%d", i); //��ӡ���
		if (i == nextseqnum) {
			cout << "|";
			printf("|");
		}//������һ�������ķ��飬����ָ���'|'
		if (i == (base + N) % k) {
			cout << ")";
			printf(")");
		}//�������ڽ�β���������
		cout << " ";
		printf(" ");
	}
	cout << "\n";
	printf("\n");
}
