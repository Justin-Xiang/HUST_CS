#ifndef GBN_SENDER_H
#define GBN_SENDER_H
#include "DataStructure.h"
#include "RdtSender.h"
class gbn_sender : public RdtSender
{
private:
	int base, nextseqnum; //基序号 下一个序号
	int N, k; //窗口大小 序号长度
	Packet	* sndwinbuf; //发送窗口缓存区

private:
	bool insendbuf(int seqnum); //在发送方的滑动窗口中
	void showbuf(); //显示发送方的滑动窗口

public:
	bool getWaitingState();

	//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;
	//如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	bool send(const Message& message); 
	void receive(const Packet& ackpkt); //接受确认Ack，将被NetworkServiceSimulator调用
	void timeoutHandler(int seqnum); //TimeOutHandler

public:
	gbn_sender();
	virtual ~gbn_sender();
};
#endif
