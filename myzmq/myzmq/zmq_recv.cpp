//����zmq��ͷ�ļ� 
#include <zmq.h>
#include "stdio.h"

#if 1

int main(int argc, char * argv[])
{
	void * pCtx = NULL;
	void * pSock = NULL;
	const char * pAddr = "tcp://*:7766";

	//����context��zmq��socket ��Ҫ��context�Ͻ��д��� 
	if ((pCtx = zmq_ctx_new()) == NULL)
	{
		return 0;
	}
	//����zmq socket ��socketĿǰ��6������ ������ʹ��dealer��ʽ
	//����ʹ�÷�ʽ��ο�zmq�ٷ��ĵ���zmq�ֲᣩ 
	if ((pSock = zmq_socket(pCtx, ZMQ_DEALER)) == NULL)
	{
		zmq_ctx_destroy(pCtx);
		return 0;
	}
	int iRcvTimeout = 5000;// millsecond
	//����zmq�Ľ��ճ�ʱʱ��Ϊ5�� 
	if (zmq_setsockopt(pSock, ZMQ_RCVTIMEO, &iRcvTimeout, sizeof(iRcvTimeout)) < 0)
	{
		zmq_close(pSock);
		zmq_ctx_destroy(pCtx);
		return 0;
	}
	//�󶨵�ַ tcp://*:7766 
	//Ҳ����ʹ��tcpЭ�����ͨ�ţ�ʹ������˿� 7766
	if (zmq_bind(pSock, pAddr) < 0)
	{
		zmq_close(pSock);
		zmq_ctx_destroy(pCtx);
		return 0;
	}
	printf("bind at : %s\n", pAddr);
	while (1)
	{
		char szMsg[1024] = { 0 };
		printf("waitting...\n");
		errno = 0;
		//ѭ���ȴ����յ�������Ϣ��������5��û�нӵ���Ϣʱ��
		//zmq_recv�������ش�����Ϣ ����ʹ��zmq_strerror�������д���λ 
		if (zmq_recv(pSock, szMsg, sizeof(szMsg), 0) < 0)
		{
			printf("error = %s\n", zmq_strerror(errno));
			continue;
		}
		printf("received message : %s\n", szMsg);
	}

	return 0;
}

#endif