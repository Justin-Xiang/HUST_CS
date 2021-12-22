#include "stdafx.h"
#include "gbn_receiver.h"
#include "Global.h"

gbn_receiver::gbn_receiver(): k(8){
	expectSequenceNumberRcvd = 0;
	lastAckPkt.acknum = -1;
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;
	memset(lastAckPkt.payload, '.', Configuration::PAYLOAD_SIZE);
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

gbn_receiver::~gbn_receiver() {

}

void gbn_receiver::receive(const Packet& packet) {
	if (packet.checksum != pUtils->calculateCheckSum(packet)) {
		pUtils->printPacket("���շ������鱻�𻵣�У���벻��ȷ", packet);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
		return;
	}

	if (packet.seqnum != expectSequenceNumberRcvd) {
		pUtils->printPacket("���շ��������Ų��ǽ��շ����ڴ���", packet);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
		return;
	}
	//�������ַ���Ϊ�������� �ۼ�ȷ�ϵķ���
	else {
		Message data;
		memcpy(data.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, data);
		lastAckPkt.acknum = packet.seqnum;
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("���շ������շ���ȷ������ACK", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
		expectSequenceNumberRcvd = (expectSequenceNumberRcvd + 1) % 8;
	}
	cout << "���շ���Ŀǰ���ص�ACK���Ϊ��" << lastAckPkt.acknum << endl;
}