// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "LibEvent.h"
int _tmain(int argc, _TCHAR* argv[])
{	
	CLibEvent libEvent;
	libEvent.StartServer(7000,1,100,60*2,60*2);
	getchar();
	libEvent.StopServer();
	return 0;
}

