#ifndef SR_SENDER_H
#define SR_SENDER_H
#include "RdtSender.h"
class sr_sender : public RdtSender
{
private:
	int base, nextseqnum; //基序号 下一个分组序号
	int N, k; //发送窗口大小 序列长度
	bool * ifrcv; //窗口中每个位置是否有接受的值
	Packet* sndwinbuf; //发送方窗口缓存

private:
	bool insendbuf(int seqnum); //是否在发送方的滑动窗口中
	void showbuf(); //显示发送方的发送窗口

public:
	bool getWaitingState();//获取现在是否能发送
	//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;
	//如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	bool send(const Message& message); 
	void receive(const Packet& packet); //接受确认Ack，将被NetworkServiceSimulator调用
	void timeoutHandler(int seqnum); //Timeout handler，将被NetworkServiceSimulator调用

public:
	sr_sender();
	virtual ~sr_sender();
};
#endif // ! 



