#include "stdafx.h"
#include "sr_receiver.h"
#include "Global.h"
using namespace std;

sr_receiver::sr_receiver() :k(8), N(4), ifrcv(new bool[8]), rcvwinbuf(new Packet[8])
{
	//初始化
	base = 0;
	for (int i = 0; i < k; i++) { //初始化的时候，窗口中所有位置都没有占用
		ifrcv[i] = false;
	}
	lastAckPkt.acknum = -1; //初始状态下，上次发送的确认包的确认序号为-1，使得当第一个接受的数据包出错时该确认报文的确认号为-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//忽略该字段
	memset(lastAckPkt.payload, '.', Configuration::PAYLOAD_SIZE);
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

sr_receiver::~sr_receiver() {
	delete[] ifrcv;
	delete[] rcvwinbuf;
}

//接收端接受分组
void sr_receiver::receive(const Packet& packet) {
	int checksum;
	checksum = pUtils->calculateCheckSum(packet);
	if (checksum != packet.checksum) { //校验和错误，分组损坏
		pUtils->printPacket("接收方：分组被损坏，校验码不正确", packet);
		//这里不像GBN一样重传最近ack，等待超时重传
		return;
	}
	else {
		if (inrcvbuf(packet.seqnum) == false) { //不在接收窗口内，发送上一次ACK
			pUtils->printPacket("接收方：不是期望的分组 ", packet);
			lastAckPkt.acknum = packet.seqnum; //发送ack
			lastAckPkt.seqnum = -1; //忽略这个字段
			memset(lastAckPkt.payload, '.', Configuration::PAYLOAD_SIZE);
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);
			return;
		}
		else { //如果是当前窗口内的内容，根据条件则滑动窗口或者缓存，返回ack
			cout << "接收方：收到数据包，序号为：" << packet.seqnum << endl;
			rcvwinbuf[packet.seqnum] = packet; //窗口中该位置被分组占据
			ifrcv[packet.seqnum] = true; //将当前序号变为已经接受
			lastAckPkt.acknum = packet.seqnum; //更新ack
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt); //计算校验和
			pUtils->printPacket("接收方：接收到接收方想要的当前分组，发送ack", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt); //返回ACK给发送方
			int i = 0;
			while (ifrcv[base] == true && i <= 4) { //移动窗口，发送缓存数据
				i++;
				//提取数据，交给应用层
				Message data;
				memcpy(data.data, rcvwinbuf[base].payload, sizeof(rcvwinbuf[base].payload));
				pns->delivertoAppLayer(RECEIVER, data);
				ifrcv[base] = false; //该字段归还为没有接受的状态
				base = (base + 1) % k; //处理下一个序号
			}
			cout << "接收方：接收端窗口滑动：\n";
			showbuf();
		}
	}
}

//判断当前分组是否在发送方窗口中
bool sr_receiver::inrcvbuf(int seqnum)
{
	int end = (base + N) % k;
	//分两种情况，首先是发送方窗口末尾的序列号大于起始序列号，证明升序排列
	if (base < end) {
		//该分组序列号seqnum要限制在发送窗口的首尾序号之间
		return seqnum < end&& seqnum >= base;
	}
	else {
		//窗口末尾序列号小于起始序列号，
		//证明其排列是从开始序列号到k-1,然后再从0到末尾，我们将其限制在这个范围
		return seqnum >= base || seqnum < end;
	}
}

//打印发送窗口
void sr_receiver::showbuf()
{
	for (int i = 0; i < k; i++) { //碰到窗口开头输出括号
		if (i == base) {
			cout << "(";
			printf("(");
		}
		//在发送缓冲区内的元素
		if (inrcvbuf(i) && ifrcv[i] == true) { //已经缓存的状态
			cout << i << ":stored";
			printf("%d:stored", i);
		}
		else if (inrcvbuf(i)) { //缓冲区内没缓存，空状态
			cout << i << ":empty";
			printf("%d:empty", i);
		}
		if (i == (base + N) % k) {
			cout << ")"; //碰到窗口结尾输出反括号
			printf(")");
		}
		if (inrcvbuf(i) == false) {
			cout << i << ":X"; //不在窗口内的元素
			printf("%d:X");
		}
		cout << " ";
		printf(" ");
	}
	cout << "\n";
	printf("\n");
}