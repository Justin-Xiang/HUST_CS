#ifndef TCP_SENDER_H
#define TCP_SENDER_H
#include "RdtSender.h"
class tcp_sender :public RdtSender
{
private:
	int base, nextseqnum; //基序号，下一个分组序号
	int N, k; //发送窗口大小，序列长度
	int resend; //记录收到的冗余ACK个数，超过三个重传
	Packet* sndwinbuf;		//发送方窗口缓存

private:
	bool insendbuf(int seqnum); //在发送方的滑动窗口中
	void showbuf(); //展示发送方的滑动窗口

public:

	bool getWaitingState();
	bool send(const Message& message);						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(const Packet& ackpkt);						//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqnum);					//Timeout handler，将被NetworkServiceSimulator调用

public:
	tcp_sender();
	virtual ~tcp_sender();
};
#endif // ! TCP_SENDER_H



