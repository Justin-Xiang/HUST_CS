#ifndef SR_RECEIVER_H
#define SR_RECEIVER_H
#include "RdtReceiver.h"
class sr_receiver :public RdtReceiver
{
private:
	int base;
	int N, k;
	bool* ifrcv;
	Packet* rcvwinbuf;
	Packet lastAckPkt;
private:
	bool inrcvbuf(int seqnum); //在接收方窗口
	void showbuf(); //展示接收方滑动窗口

public:
	sr_receiver();
	virtual ~sr_receiver();

public:
	void receive(const Packet& packet); //接收报文

};

#endif // ! 



