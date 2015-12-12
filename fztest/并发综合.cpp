#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include "互斥锁.h"

DWORD WINAPI TestThread2(LPVOID);
DWORD WINAPI TestThread3(LPVOID);
int shared_data;
void setdata(int modify_value)
{
	CLimitSingleInstance cmutex(0);
	cmutex.Lock();
	shared_data+=modify_value;
	cmutex.Unlock();
}
void thread_test()
{
	HANDLE hThread;
	DWORD dwThreadId;//线程ID

	hThread = CreateThread(NULL,0,&TestThread2,"Hello Thread",0,&dwThreadId);
	if (!hThread)
	{
		fprintf(stderr,"Thread creation failed: %d\r\n",GetLastError());
		return ;
	}	
	hThread = CreateThread(NULL,0,&TestThread3,"Hello Thread",0,&dwThreadId);
	if (!hThread)
	{
		fprintf(stderr,"Thread creation failed: %d\r\n",GetLastError());
		return ;
	}	

#if 1
	while (1)
	{
		std::cout<<"shared_data:"<<shared_data<<" ";
		Sleep(100);
	}
#endif
	
	
	printf("%d:Created thread %x (ID %d)\r\n",GetCurrentThreadId(),hThread,dwThreadId);
	//等待线程退出并且输出线程的退出码;
	WaitForSingleObject(hThread,INFINITE);

	DWORD dwExitCode;//保存线程退出码;
	//TerminateThread(hThread,dwExitCode);//终止线程;
	GetExitCodeThread(hThread,&dwExitCode);
	printf("%d: Thread exited: %d\r\n",hThread,dwExitCode);
	CloseHandle(hThread);
	hThread = NULL;
}

#if 0
void main()
{
	thread_test();
	system("pause");
}
#endif

DWORD WINAPI TestThread2(LPVOID)
{
	while(1)
	{
		setdata(1);
		Sleep(100);
	}
	return 1;
}
DWORD WINAPI TestThread3(LPVOID)
{
	while(1)
	{
		setdata(-1);
		Sleep(100);
	}
	return 1;
}