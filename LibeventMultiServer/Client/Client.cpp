// Client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../Server/CProtocol.h"

#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")
#pragma comment (lib,"wsock32.lib")

class Client
{
public:
	Client()
	:m_sock_id(INVALID_SOCKET)
	{
		WSADATA WSAData;
		WSAStartup(0x0201, &WSAData);
	}
	~Client()
	{
		if (m_sock_id!=INVALID_SOCKET)
		{
			closesocket(m_sock_id);
		}
		WSACleanup();
	}
	void Test(char* server,int port)
	{
		if (m_sock_id==INVALID_SOCKET)
		{
			m_sock_id=create_socket(server, port);
		}
		if (m_sock_id)
		{
			login(m_sock_id);
			logout(m_sock_id);
		}	
	}
private:
	SOCKET m_sock_id;
private:
	SOCKET create_socket(char* server, int port)
	{
		SOCKET sockfd=socket(AF_INET, SOCK_STREAM, 0);
		if (SOCKET_ERROR!=sockfd)
		{
			struct sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_addr.s_addr = inet_addr(server);
			addr.sin_port = htons(port);
			connect(sockfd, (struct sockaddr *) &addr, sizeof(struct sockaddr));
		}	
		return sockfd;
	}

	int send_cmd(SOCKET c, int cmd, char *data, size_t data_len)
	{
		Head *h = (Head *) (data);
		h->pkglen = sizeof(Head)+data_len;
		h->stx = emStx;
		h->nFunID = cmd;
		int rs = send(c, data, h->pkglen, 0);	
		return rs == h->pkglen;
	}
	
	int recv_cmd(SOCKET c, char *data, size_t data_len)
	{
		int rs=recv(c,data,data_len,0);
		if (rs>0)
		{
			Head *h = (Head *)(data);
			if (h->pkglen==rs)
			{
				Proto_Login_Rsp *login=(Proto_Login_Rsp*)(data+sizeof(Head));
				return 1;
			}
		}
		return 0;
	}

	void login(SOCKET sock_id)
	{
		char buf[emMaxBuffLen]={0};
		Proto_Login_Req *login=(Proto_Login_Req*)(buf+sizeof(Head));
		login->uid=10;
		send_cmd(sock_id,emFunLogin,buf,sizeof(Proto_Login_Req));
	}

	void logout(SOCKET sock_id)
	{
		char buf[emMaxBuffLen]={0};
		if (recv_cmd(sock_id,buf,sizeof(buf)))
		{
			Proto_Login_Req *login=(Proto_Login_Req*)(buf+sizeof(Head));
			login->uid=10;
			send_cmd(sock_id,emFunLogout,buf,sizeof(Proto_Login_Req));
		}		
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	
	char* server = "127.0.0.1";
	int port = 7000;
	Client client;
	client.Test(server,port);
	getchar();
	return 0;
}
