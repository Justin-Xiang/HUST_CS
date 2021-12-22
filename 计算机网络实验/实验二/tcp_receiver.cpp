#include "stdafx.h"
#include "tcp_receiver.h"
#include "Global.h"
using namespace std;
tcp_receiver::tcp_receiver() : k(8)
{
	//��ʼ��
	expectSequenceNumberRcvd = 0;
	lastAckPkt.acknum = -1; //��ʼ״̬�£��ϴη��͵�ȷ�ϰ���ȷ�����Ϊ-1��ʹ�õ���һ�����ܵ����ݰ�����ʱ��ȷ�ϱ��ĵ�ȷ�Ϻ�Ϊ-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//���Ը��ֶ�
	memset(lastAckPkt.payload, '.', Configuration::PAYLOAD_SIZE);
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

tcp_receiver::~tcp_receiver()
{
}

void tcp_receiver::receive(const Packet& packet)
{
	//���շ�����checksum��������Դ�checksum��ͬ��������ack����
	if (packet.checksum != pUtils->calculateCheckSum(packet)) {
		pUtils->printPacket("���շ������鱻�𻵣�У���벻��ȷ", packet);
		pns->sendToNetworkLayer(SENDER, lastAckPkt); //���鱻�𻵣��ͷ��������һ��ack
		return;
	}
	//�����ڴ�����ţ�������ack����
	if (packet.seqnum != expectSequenceNumberRcvd) {
		pUtils->printPacket("���շ��������Ų��ǽ��շ����ڴ��� ", packet);
		pns->sendToNetworkLayer(SENDER, lastAckPkt); //�����ڴ������ݰ����ͷ��������һ��ack
		return;
	}
	//ʣ�µ�����ǰ�˳����ķ��飬���²�����ack
	else {
		//��ȡ���ݣ�����Ӧ�ò�
		Message data;
		memcpy(data.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, data);
		//����ack���ظ����ͷ�
		lastAckPkt.acknum = packet.seqnum; //����ack�ţ����Ƿ������кţ�
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt); //����У���
		pUtils->printPacket("���շ������շ���ȷ���ղ�����ACK", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//���ظ����ͷ�
		expectSequenceNumberRcvd = (expectSequenceNumberRcvd + 1) % k; //ȷ����һ���ڴ����ܵ����
	}
	cout << "Ŀǰ���ص�ack���Ϊ: " << lastAckPkt.acknum << "\n" << endl;
}