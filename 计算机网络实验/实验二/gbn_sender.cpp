#include "stdafx.h"
#include "gbn_sender.h"
#include "Global.h"
using namespace std;

gbn_sender::gbn_sender() : N(4), k(8), sndwinbuf(new Packet[8])
{
	//基序号和下一个序号初始化为0
	base = 0;
	nextseqnum = 0;

}

bool gbn_sender::send(const Message& message) {
	//首先判断是否已满
	if (getWaitingState()) {
		//如果窗口已满 将数据返回给上层
		pUtils->printPacket("发送方：发送窗口满 无法发送", sndwinbuf[nextseqnum]);
		return false;
	}
	else if (insendbuf(nextseqnum)) { //处理下一个要发的分组
		//首先判断是否在滑动窗口中
		//更新变量
		sndwinbuf[nextseqnum].acknum = -1; //忽略该字段
		sndwinbuf[nextseqnum].seqnum = nextseqnum; //下一个要发送的序列号
		sndwinbuf[nextseqnum].checksum = 0; //初始化为0
		memcpy(sndwinbuf[nextseqnum].payload, message.data, sizeof(message.data));
		sndwinbuf[nextseqnum].checksum = pUtils->calculateCheckSum(sndwinbuf[nextseqnum]);
		pUtils->printPacket("发送方：发送报文", sndwinbuf[nextseqnum]);
		cout << "发送方：发送前的滑动窗口";
		showbuf();
		//gbn的定时器在base == nextseqnum的时候启动
		if (base == nextseqnum) {
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		}
		pns->sendToNetworkLayer(RECEIVER, sndwinbuf[nextseqnum]);
		nextseqnum = (nextseqnum + 1) % k;
		cout << "发送方：发送后的滑动窗口";
		showbuf();
		return false;
	}
}

//接收接收方返回的报文
void gbn_sender::receive(const Packet& ackpkt) {
	int checksum;
	checksum = pUtils->calculateCheckSum(ackpkt);
	if (checksum != ackpkt.checksum) {
		pUtils->printPacket("发送方:检验和不正确 分组损坏", ackpkt);
	}
	else //接收返回的报文
	{
		if (insendbuf(ackpkt.acknum)) {
			cout << "发送方：接收到ACK：" << ackpkt.acknum << endl;
			base = (ackpkt.acknum + 1) % 8;
			pns->stopTimer(SENDER, 0);
			if (base != nextseqnum) {
				pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
			}
			cout << "发送方：接收ACK后的滑动窗口：\n";
			showbuf();
		}
	}
}

//是否应该等待
bool gbn_sender::getWaitingState() { //窗口满时要等待
	int limitseq = base + N;
	int crntcap = limitseq % k; //目前窗口容量到达序号
	int crntocap = nextseqnum % k; //目前占用到的序号
	return crntcap == crntocap;
}


//重传分组
void gbn_sender::timeoutHandler(int seqnum) {
	pUtils->printPacket("发送方：有分组发生超时", sndwinbuf[seqnum]);
	pns->sendToNetworkLayer(RECEIVER, sndwinbuf[base]);
	pns->stopTimer(SENDER, 0);
	pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	pUtils->printPacket("发送方：重传完成", sndwinbuf[base]);
}

//判断当前分组是否在发送窗口中
bool gbn_sender::insendbuf(int seqnum) {
	//序号空间为一个环 故要判断环是否从尾部穿到头部
	int end = (base + N) % k;
	
	if (base < end) {
		return seqnum < end && seqnum >= base; //正常判断
	}
	else {
		return seqnum >= base || seqnum < end; //反向判断
	}
}

//打印发送窗口
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

