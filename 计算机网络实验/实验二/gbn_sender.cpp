#include "stdafx.h"
#include "gbn_sender.h"
#include "Global.h"
using namespace std;

gbn_sender::gbn_sender() : N(4), k(8), sndwinbuf(new Packet[8])
{
	//����ź���һ����ų�ʼ��Ϊ0
	base = 0;
	nextseqnum = 0;

}

bool gbn_sender::send(const Message& message) {
	//�����ж��Ƿ�����
	if (getWaitingState()) {
		//����������� �����ݷ��ظ��ϲ�
		pUtils->printPacket("���ͷ������ʹ����� �޷�����", sndwinbuf[nextseqnum]);
		return false;
	}
	else if (insendbuf(nextseqnum)) { //������һ��Ҫ���ķ���
		//�����ж��Ƿ��ڻ���������
		//���±���
		sndwinbuf[nextseqnum].acknum = -1; //���Ը��ֶ�
		sndwinbuf[nextseqnum].seqnum = nextseqnum; //��һ��Ҫ���͵����к�
		sndwinbuf[nextseqnum].checksum = 0; //��ʼ��Ϊ0
		memcpy(sndwinbuf[nextseqnum].payload, message.data, sizeof(message.data));
		sndwinbuf[nextseqnum].checksum = pUtils->calculateCheckSum(sndwinbuf[nextseqnum]);
		pUtils->printPacket("���ͷ������ͱ���", sndwinbuf[nextseqnum]);
		cout << "���ͷ�������ǰ�Ļ�������";
		showbuf();
		//gbn�Ķ�ʱ����base == nextseqnum��ʱ������
		if (base == nextseqnum) {
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		}
		pns->sendToNetworkLayer(RECEIVER, sndwinbuf[nextseqnum]);
		nextseqnum = (nextseqnum + 1) % k;
		cout << "���ͷ������ͺ�Ļ�������";
		showbuf();
		return false;
	}
}

//���ս��շ����صı���
void gbn_sender::receive(const Packet& ackpkt) {
	int checksum;
	checksum = pUtils->calculateCheckSum(ackpkt);
	if (checksum != ackpkt.checksum) {
		pUtils->printPacket("���ͷ�:����Ͳ���ȷ ������", ackpkt);
	}
	else //���շ��صı���
	{
		if (insendbuf(ackpkt.acknum)) {
			cout << "���ͷ������յ�ACK��" << ackpkt.acknum << endl;
			base = (ackpkt.acknum + 1) % 8;
			pns->stopTimer(SENDER, 0);
			if (base != nextseqnum) {
				pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
			}
			cout << "���ͷ�������ACK��Ļ������ڣ�\n";
			showbuf();
		}
	}
}

//�Ƿ�Ӧ�õȴ�
bool gbn_sender::getWaitingState() { //������ʱҪ�ȴ�
	int limitseq = base + N;
	int crntcap = limitseq % k; //Ŀǰ���������������
	int crntocap = nextseqnum % k; //Ŀǰռ�õ������
	return crntcap == crntocap;
}


//�ش�����
void gbn_sender::timeoutHandler(int seqnum) {
	pUtils->printPacket("���ͷ����з��鷢����ʱ", sndwinbuf[seqnum]);
	pns->sendToNetworkLayer(RECEIVER, sndwinbuf[base]);
	pns->stopTimer(SENDER, 0);
	pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	pUtils->printPacket("���ͷ����ش����", sndwinbuf[base]);
}

//�жϵ�ǰ�����Ƿ��ڷ��ʹ�����
bool gbn_sender::insendbuf(int seqnum) {
	//��ſռ�Ϊһ���� ��Ҫ�жϻ��Ƿ��β������ͷ��
	int end = (base + N) % k;
	
	if (base < end) {
		return seqnum < end && seqnum >= base; //�����ж�
	}
	else {
		return seqnum >= base || seqnum < end; //�����ж�
	}
}

//��ӡ���ʹ���
void gbn_sender::showbuf() {
	for (int i = 0; i < k; i++) {
		if (i == base) {
			cout << "(";
			printf("(");
		}
		cout << i;
		printf("%d", i);
		if (i == nextseqnum) {
			cout << "|";
			printf("|");
		}
		if (i == (base + N) % k) {
			cout << ")";
			printf(")");
		}
		
		cout << " ";
		printf(" ");
	}
	cout << " \n";
	printf(" \n");
}

gbn_sender::~gbn_sender(){
	delete[] sndwinbuf;
}

