#include "NetWork.h"

CNetWork oNetWork;
CNetWork::~CNetWork()
{
	closesocket(gClientSocket);
}
int CNetWork::InitNetWork()
{
	/* ��ʼ��;Winsock1.1 */
	WSADATA wsd ; /*����ṹ�������洢��WSAStartup�������ú󷵻ص� Windows Sockets ���ݡ�������Winsock.dll ִ�е����ݡ�*/
	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0) {
		gErrorCode = WSAGetLastError();
		printf("WSAStartup() failed error code:%d!\n",gErrorCode);
		exit(0);
	}

	/* �����׽���; */
	gClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (gClientSocket == INVALID_SOCKET) {
		gErrorCode = WSAGetLastError();
		fprintf(stderr, "socket() failed: %d\n", gErrorCode);
	}
	printf("[OK]\n");

	/* ���󶨷�������ַ�ṹ; */
	memset(&server_add, 0, sizeof(server_add));
	server_add.sin_family			= AF_INET;/*����Э��;*/
	server_add.sin_port				= htons(5566);/*�󶨶˿ں�;*/
	server_add.sin_addr.S_un.S_addr	= inet_addr("127.1.1.188");//htonl(INADDR_ANY);

	/*���ӷ�����*/
	int cr = connect(gClientSocket,(const sockaddr *)&server_add, sizeof(server_add));
	if ( cr == -1)
	{
		std::cout << "connect error. return code:"<<cr<<std::endl ;
	}
	return 0;
}

int CNetWork::Recv(char * packet,unsigned short size)
{
	int recvsize = 0;
	recvsize = recv(gClientSocket,packet,size,0);
	return 0;
}


int CNetWork::Send(char * packet,unsigned short size)
{
	send(gClientSocket,packet,size,0);
	return 0;
}


int CNetWork::RecvData()
{
	int recvsize = 0;
	recvsize = recv(gClientSocket,(char *)&senddata,sizeof(senddata),0);
	if (recvsize>0)
	{
		std::cout<<"recvsize:"<<recvsize<<" send_data.id:"<<senddata.iType<<" send_data.type:"<<senddata.iSize<<std::endl;
	}
	return recvsize;
}

int CNetWork::SendData()
{

	struct testpacketbody1
	{
		int aa;
		float bb;
		testpacketbody1():aa(123123123),bb(2.121212){}
	}tb1;testpacketbody1 t1;

	struct testpacketbody2
	{
		int a2;
		int b2;
		int c2;
		testpacketbody2():a2(11111),b2(22222),c2(33333){}
	}tb2;testpacketbody2 t2;

	
	int recvsize = 0;

	senddata.iType = 1048577;
	senddata.iSize = sizeof(t1);
	send(gClientSocket,(char *)&senddata,sizeof(senddata),0);
	send(gClientSocket,(char *)&tb1,sizeof(testpacketbody1),0);

	senddata.iType = 1048578;
	senddata.iSize = sizeof(t2);
	send(gClientSocket,(char *)&senddata,sizeof(senddata),0);
	send(gClientSocket,(char *)&tb2,sizeof(testpacketbody2),0);


	senddata.iType = 1048577;
	senddata.iSize = sizeof(t1);
	send(gClientSocket,(char *)&senddata,sizeof(senddata),0);
	send(gClientSocket,(char *)&tb1,sizeof(testpacketbody1),0);

	recvsize = recv(gClientSocket,(char *)&senddata,sizeof(senddata),0);
	if (recvsize>0)
	{
		std::cout<<"recvsize:"<<recvsize<<" send_data.id:"<<senddata.iType<<" send_data.type:"<<senddata.iSize<<std::endl;
	}
	
	//system("pause");
	//std::cout << "close socket.\n" ;
	return 0;
}


