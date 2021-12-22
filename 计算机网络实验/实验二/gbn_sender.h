#ifndef GBN_SENDER_H
#define GBN_SENDER_H
#include "DataStructure.h"
#include "RdtSender.h"
class gbn_sender : public RdtSender
{
private:
	int base, nextseqnum; //����� ��һ�����
	int N, k; //���ڴ�С ��ų���
	Packet	* sndwinbuf; //���ʹ��ڻ�����

private:
	bool insendbuf(int seqnum); //�ڷ��ͷ��Ļ���������
	void showbuf(); //��ʾ���ͷ��Ļ�������

public:
	bool getWaitingState();

	//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;
	//�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	bool send(const Message& message); 
	void receive(const Packet& ackpkt); //����ȷ��Ack������NetworkServiceSimulator����
	void timeoutHandler(int seqnum); //TimeOutHandler

public:
	gbn_sender();
	virtual ~gbn_sender();
};
#endif
