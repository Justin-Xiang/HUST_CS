#include "RdtReceiver.h"
class gbn_receiver :public RdtReceiver
{
private:
	int expectSequenceNumberRcvd; //�ڴ��յ�����һ���������
	Packet lastAckPkt;
	const int k; //��ų���k
public:
	gbn_receiver();
	virtual ~gbn_receiver();

public:
	void receive(const Packet& packet);
};

