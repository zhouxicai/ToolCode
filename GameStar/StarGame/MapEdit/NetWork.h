#ifndef _CNET_WORK_H
#define _CNET_WORK_H

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>

#include <Windows.h>
#include <iostream>
//#include "WinSock.h"
#include "WinSock2.h"
#include <MSWSock.h>   

#pragma comment(lib,"WS2_32.lib") 

	/*收发数据*/
	struct SSendData 
	{
		int iType;
		int iSize;
	};

class CNetWork
{
public:
	~CNetWork();
	int InitNetWork();
	int SendData();
	int RecvData();
	int Recv(char * packet,unsigned short size);
	int Send(char * packet,unsigned short size);
	
private:
	sockaddr_in server_add;
	int gClientSocket;
	int gErrorCode;
	SSendData senddata;
};
extern CNetWork oNetWork;

#endif