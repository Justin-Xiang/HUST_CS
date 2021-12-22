#ifndef SR_SENDER_H
#define SR_SENDER_H
#include "RdtSender.h"
class sr_sender : public RdtSender
{
private:
	int base, nextseqnum; //����� ��һ���������
	int N, k; //���ʹ��ڴ�С ���г���
	bool * ifrcv; //������ÿ��λ���Ƿ��н��ܵ�ֵ
	Packet* sndwinbuf; //���ͷ����ڻ���

private:
	bool insendbuf(int seqnum); //�Ƿ��ڷ��ͷ��Ļ���������
	void showbuf(); //��ʾ���ͷ��ķ��ʹ���

public:
	bool getWaitingState();//��ȡ�����Ƿ��ܷ���
	//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;
	//�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	bool send(const Message& message); 
	void receive(const Packet& packet); //����ȷ��Ack������NetworkServiceSimulator����
	void timeoutHandler(int seqnum); //Timeout handler������NetworkServiceSimulator����

public:
	sr_sender();
	virtual ~sr_sender();
};
#endif // ! 



