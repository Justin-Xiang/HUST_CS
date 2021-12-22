#include "stdafx.h"
#include "tcp_receiver.h"
#include "Global.h"
using namespace std;
tcp_receiver::tcp_receiver() : k(8)
{
	//初始化
	expectSequenceNumberRcvd = 0;
	lastAckPkt.acknum = -1; //初始状态下，上次发送的确认包的确认序号为-1，使得当第一个接受的数据包出错时该确认报文的确认号为-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//忽略该字段
	memset(lastAckPkt.payload, '.', Configuration::PAYLOAD_SIZE);
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

tcp_receiver::~tcp_receiver()
{
}

void tcp_receiver::receive(const Packet& packet)
{
	//接收方计算checksum，如果和自带checksum不同，不更新ack返回
	if (packet.checksum != pUtils->calculateCheckSum(packet)) {
		pUtils->printPacket("接收方：分组被损坏，校验码不正确", packet);
		pns->sendToNetworkLayer(SENDER, lastAckPkt); //分组被损坏，就发送最近的一个ack
		return;
	}
	//不是期待的序号，不更新ack返回
	if (packet.seqnum != expectSequenceNumberRcvd) {
		pUtils->printPacket("接收方：这个序号不是接收方所期待的 ", packet);
		pns->sendToNetworkLayer(SENDER, lastAckPkt); //不是期待的数据包，就发送最近的一个ack
		return;
	}
	//剩下的情况是按顺到达的分组，更新并返回ack
	else {
		//提取数据，交给应用层
		Message data;
		memcpy(data.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, data);
		//制作ack返回给发送方
		lastAckPkt.acknum = packet.seqnum; //更新ack号（就是分组序列号）
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt); //计算校验和
		pUtils->printPacket("接收方：接收方正确接收并返回ACK", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//返回给发送方
		expectSequenceNumberRcvd = (expectSequenceNumberRcvd + 1) % k; //确定下一个期待接受的序号
	}
	cout << "目前返回的ack序号为: " << lastAckPkt.acknum << "\n" << endl;
}