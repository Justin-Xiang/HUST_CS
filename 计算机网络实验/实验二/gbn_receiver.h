#include "RdtReceiver.h"
class gbn_receiver :public RdtReceiver
{
private:
	int expectSequenceNumberRcvd; //期待收到的下一个报文序号
	Packet lastAckPkt;
	const int k; //序号长度k
public:
	gbn_receiver();
	virtual ~gbn_receiver();

public:
	void receive(const Packet& packet);
};

