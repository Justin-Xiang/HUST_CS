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
	bool inrcvbuf(int seqnum); //�ڽ��շ�����
	void showbuf(); //չʾ���շ���������

public:
	sr_receiver();
	virtual ~sr_receiver();

public:
	void receive(const Packet& packet); //���ձ���

};

#endif // ! 



