// StopWait.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "StopWaitRdtSender.h"
#include "StopWaitRdtReceiver.h"
#include "gbn_sender.h"
#include "gbn_receiver.h"
#include "sr_sender.h"
#include "sr_receiver.h"
#include "tcp_sender.h"
#include "tcp_receiver.h"

int main(int argc, char* argv[])
{

	//Rdt Test
//	RdtSender *ps = new StopWaitRdtSender();
//	RdtReceiver * pr = new StopWaitRdtReceiver();
////	pns->setRunMode(0);  //VERBOSģʽ
//	pns->setRunMode(1);  //����ģʽ
//	pns->init();
//	pns->setRtdSender(ps);
//	pns->setRtdReceiver(pr);
//	pns->setInputFile("D:\\CI_lab2\\rdt\\Windows VS2017\\input.txt");
//	pns->setOutputFile("D:\\CI_lab2\\rdt\\Windows VS2017\\output.txt");
//
//	pns->start();
//
//	delete ps;
//	delete pr;
//	delete pUtils;									//ָ��Ψһ�Ĺ�����ʵ����ֻ��main��������ǰdelete
//	delete pns;										//ָ��Ψһ��ģ�����绷����ʵ����ֻ��main��������ǰdelete
//	
//	return 0;
// 

	////gbn test

	//RdtSender* ps_gbn = new gbn_sender();
	//RdtReceiver* pr_gbn = new gbn_receiver();

	//pns->setRunMode(1);  //����ģʽ

	//////gbn
	//pns->init();
	//pns->setRtdSender(ps_gbn);
	//pns->setRtdReceiver(pr_gbn);
	//pns->setInputFile("D:\\CI_lab2\\rdt\\Windows VS2017\\input.txt");
	//pns->setOutputFile("D:\\CI_lab2\\rdt\\Windows VS2017\\output.txt");
	//ofstream tcp_log;
	//tcp_log.open("D:\\CI_lab2\\rdt\\Windows VS2017\\output.log");
	//cout.rdbuf(tcp_log.rdbuf());
	//pns->start();

	//delete ps_gbn;
	//delete pr_gbn;
	//delete pUtils;
	//delete pns;

	//return 0;

	/*RdtSender* ps_sr = new sr_sender();
	RdtReceiver* pr_sr = new sr_receiver();
	pns->init();
	pns->setRtdSender(ps_sr);
	pns->setRtdReceiver(pr_sr);
	pns->setInputFile("D:\\CI_lab2\\rdt\\Windows VS2017\\input.txt");
	pns->setOutputFile("D:\\CI_lab2\\rdt\\Windows VS2017\\output.txt");
	ofstream tcp_log;
	tcp_log.open("D:\\CI_lab2\\rdt\\Windows VS2017\\output.log");
	cout.rdbuf(tcp_log.rdbuf());
	pns->start();

	delete ps_sr;
	delete pr_sr;
	delete pUtils;
	delete pns;

	return 0;*/

	//tcp test
	RdtSender* ps_tcp = new tcp_sender();
	RdtReceiver* pr_tcp = new tcp_receiver();
	pns->init();
	pns->setRtdSender(ps_tcp);
	pns->setRtdReceiver(pr_tcp);
	pns->setInputFile("D:\\CI_lab2\\rdt\\Windows VS2017\\input.txt");
	pns->setOutputFile("D:\\CI_lab2\\rdt\\Windows VS2017\\output.txt");
	ofstream tcp_log;
	tcp_log.open("D:\\CI_lab2\\rdt\\Windows VS2017\\output.log");
	cout.rdbuf(tcp_log.rdbuf());
	pns->start();

	delete ps_tcp;
	delete pr_tcp;
	delete pUtils;
	delete pns;

	return 0;
}

