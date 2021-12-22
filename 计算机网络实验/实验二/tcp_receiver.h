#ifndef TCP_RECEIVER_H
#define TCP_RECEIVER_H
#include "RdtReceiver.h"
class tcp_receiver : public RdtReceiver
{
private:
	int expectSequenceNumberRcvd;
	Packet lastAckPkt;
	const int k;
public:
	tcp_receiver();
	virtual ~tcp_receiver();
public:
	void receive(const Packet& packet);
};
#endif

