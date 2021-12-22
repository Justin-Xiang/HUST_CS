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
		pUtils->printPacket("接收方：分组被损坏，校验码不正确", packet);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
		return;
	}

	if (packet.seqnum != expectSequenceNumberRcvd) {
		pUtils->printPacket("接收方：这个序号不是接收方所期待的", packet);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
		return;
	}
	//上面两种方法为丢弃分组 累计确认的方法
	else {
		Message data;
		memcpy(data.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, data);
		lastAckPkt.acknum = packet.seqnum;
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("接收方：接收方正确并返回ACK", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
		expectSequenceNumberRcvd = (expectSequenceNumberRcvd + 1) % 8;
	}
	cout << "接收方：目前返回的ACK序号为：" << lastAckPkt.acknum << endl;
}