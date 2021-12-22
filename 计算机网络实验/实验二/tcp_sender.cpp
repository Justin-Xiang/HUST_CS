#include "stdafx.h"
#include "tcp_sender.h"
#include "Global.h"
using namespace std;

tcp_sender::tcp_sender() :k(8), N(4), sndwinbuf(new Packet[8])
{
	//初始化
	base = 0;
	nextseqnum = 0;
	resend = 0;
}

tcp_sender::~tcp_sender() {

}

//将报文发送给接收方
bool tcp_sender::send(const Message& message) {
	if (getWaitingState()) {
		pUtils->printPacket("发送方：发送窗口满，无法发送", sndwinbuf[nextseqnum]);;
		return false;
	}
	else { //处理下一个要发的分组
		sndwinbuf[nextseqnum].acknum = -1; //忽略该字段
		sndwinbuf[nextseqnum].seqnum = nextseqnum; //下一个要发送的序列号；
		sndwinbuf[nextseqnum].checksum = 0; //初始checksum置0
		memcpy(sndwinbuf[nextseqnum].payload, message.data, sizeof(message.data)); //data
		sndwinbuf[nextseqnum].checksum = pUtils->calculateCheckSum(sndwinbuf[nextseqnum]); //计算checksum
		pUtils->printPacket("发送方：发送方发送报文", sndwinbuf[nextseqnum]);
		//展示滑动窗口
		cout << "发送方：发送方发送前的滑动窗口：\n";
		showbuf();
		//在base=nextseqnum时候启动定时器
		if (base == nextseqnum) {
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		}
		//将报文发送给接收方
		pns->sendToNetworkLayer(RECEIVER, sndwinbuf[nextseqnum]);
		nextseqnum = (nextseqnum + 1) % k; //准备发送下一个报文
		cout << "发送方：发送方发送后的滑动窗口：\n";
		showbuf();
		return true;
	}
}

void tcp_sender::receive(const Packet& ackpkt)
{
	//比较校验和，检查分组是否被损坏
	int checksum;
	checksum = pUtils->calculateCheckSum(ackpkt);
	if (checksum != ackpkt.checksum) {
		pUtils->printPacket("发送方：校验和不正确，分组损坏", ackpkt);
		return;
	}
	else { //否则准备接收返回的报文
		if (insendbuf(ackpkt.acknum)) {
			cout << "发送方：接收到ACK：" << ackpkt.acknum << endl;
			base = (ackpkt.acknum + 1) % 8;
			pns->stopTimer(SENDER, 0);
			if (base != nextseqnum) {
				pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
			}
			resend = 0;
			//接受ACK后的滑动窗口
			cout << "发送方：发送方接收ACK后的滑动窗口：\n";
			showbuf();
		}
		else {
			if (resend == 3) {
				pns->sendToNetworkLayer(RECEIVER, sndwinbuf[base]);
				resend = 0;
				pUtils->printPacket("\n\n发送方：收到三个冗余ACK，进行重传", sndwinbuf[base]);
			}
			else {
				resend = resend + 1;
			}
		}
	}
}

//是否应该等待
bool tcp_sender::getWaitingState() //true为窗口满（要等待）
{
	int limitseq = base + N;
	int crntcap = limitseq % k; //目前窗口容量到达序号
	int crntocup = nextseqnum % k; //目前占用到的序号
	return crntcap == crntocup;
}

//超时了之后，重传所需分组
void tcp_sender::timeoutHandler(int seqnum)
{
	pUtils->printPacket("发送方：有分组发生超时", sndwinbuf[base]);
	pns->sendToNetworkLayer(RECEIVER, sndwinbuf[base]);
	pns->stopTimer(SENDER, 0);
	pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	pUtils->printPacket("发送方：重传完成", sndwinbuf[base]);
}

//判断当前分组是否在发送方窗口中
bool tcp_sender::insendbuf(int seqnum)
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
void tcp_sender::showbuf()
{
	for (int i = 0; i < k; i++) { //碰到窗口开头输出括号
		if (i == base)
		{
			cout << "(";
			printf("(");
		}
		cout << i;
		printf("%d", i); //打印序号
		if (i == nextseqnum) {
			cout << "|";
			printf("|");
		}//碰到下一个待发的分组，输出分隔符'|'
		if (i == (base + N) % k) {
			cout << ")";
			printf(")");
		}//碰到窗口结尾输出反括号
		cout << " ";
		printf(" ");
	}
	cout << "\n";
	printf("\n");
}
