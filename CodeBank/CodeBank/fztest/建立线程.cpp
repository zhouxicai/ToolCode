#include <stdio.h>
#include <Windows.h>

DWORD WINAPI TestThread(LPVOID);
//凡是由你设计却由windows系统呼叫的函数，统称为callback函数。某些API函数要求以callback作为你参数之一。如SetTimer，LineDDA，EnumObjects;
VOID CALLBACK APCProc(LONG_PTR dwParam){  
	TCHAR* pStr = (TCHAR*)dwParam;   
	LoadLibraryW(pStr);//LoadLibraryA的地址怎么获得，我就不再说了;
}
int main1()
{
	//*********************************************
	HANDLE hThread;
	DWORD dwThreadId;//线程ID
	hThread = CreateThread(NULL,0,&TestThread,"Hello Thread",0,&dwThreadId);
	if (!hThread)
	{
		fprintf(stderr,"Thread creation failed: %d\r\n",GetLastError());
		return -1;
	}
	printf("%d:Created thread %x (ID %D)\r\n",GetCurrentThreadId(),hThread,dwThreadId);
	//*********************************************
	//等待线程退出并且输出线程的退出码;
	DWORD wr = WaitForSingleObject(hThread,INFINITE);//INFINITE表示一直等待，0表示立即返回，非阻塞。
	switch(wr)
	{
	case WAIT_OBJECT_0://返回值WAIT_OBJECT_0表示等待的对象被触发。;
		break;
	case WAIT_TIMEOUT:
		break;
	case  WAIT_FAILED:
		{
			DWORD dsError = GetLastError();
			break;
		}
	case WAIT_ABANDONED://互斥体特有返回值，表示之前在互斥体上等待的代码没有正确的释放互斥体，尽管这个返回值看上去像个错误，但这个等待操作实际是成功的。即将获得互斥体的所有权。;
		break;
	}
	//*********************************************
	//等待多个对象处理;
	const int cHandles = 5;
	HANDLE wait_handles[cHandles];
	DWORD wm = WaitForMultipleObjects(cHandles,&wait_handles[0],false,INFINITE);
	if (wm>=WAIT_OBJECT_0&&wm<WAIT_OBJECT_0+cHandles)
	{	//signaled表示一个已触发的对象;
		HANDLE hSignaled = wait_handles[wm-WAIT_OBJECT_0];
	} 
	else if(wm>=WAIT_ABANDONED_0&&wm<WAIT_ABANDONED_0+cHandles)
	{	//hAbandoned指向一个废弃互斥体对象的句柄;
		HANDLE hAbandoned = wait_handles[wm-WAIT_ABANDONED_0];
	}
	else if(WAIT_TIMEOUT == wm)
	{
	} 
	else if(WAIT_FAILED == wm)
	{
		DWORD dmError = GetLastError();
	}
	//*********************************************
	//为了处理阻塞和分发消息情况可以使用MsgWaitForMultipleObjects/Ex()这两个函数可以使线程在等待一组句柄的同时还可以分发消息;
	//如果在等待条件被满足之前，有一个新的消息到达了线程的消息队列，那么这个API将返回，这样调用者可以处理这个新消息。
	DWORD 
	mwm = MsgWaitForMultipleObjects(cHandles,&wait_handles[0],true,1000,QS_ALLINPUT);//QS_ALLINPUT表示任何消息的到来都会使线程被唤醒。;
	//在某些情况下，你可能希望限制需要处理的消息类型，为了确保这个等待是警觉等待，可以使用Ex扩展函数，将dwFlags设置为MWMO_ALERTABLE;
	mwm = MsgWaitForMultipleObjectsEx(cHandles,&wait_handles[0],1000,QS_ALLINPUT,MWMO_ALERTABLE);
	mwm = CoWaitForMultipleHandles(COWAIT_WAITALL,1000,cHandles,&wait_handles[0],NULL);//这个函数将自动分发特定类型的消息;
	//*********************************************
	//APC就是异步调用过程。线程都有个APC队列，QueueUserAPC是向线程的APC队列中插入一个APC过程 ;
	//参数pfnAPC和dwData表示“函数指针/参数”对，hThread表示这个APC要放入的线程;
	QueueUserAPC((PAPCFUNC)APCProc,hThread,(ULONG_PTR)("c:\\sysnap.dll"));

	//*********************************************
	DWORD dwExitCode;//保存线程退出码;
	//TerminateThread(hThread,dwExitCode);//终止线程;
	GetExitCodeThread(hThread,&dwExitCode);
	printf("%d: Thread exited: %d\r\n");
	CloseHandle(hThread);
	//*********************************************
	HANDLE h1 = GetCurrentThread();//获取伪句柄;
	HANDLE h2;//将存储真句柄;
	//将伪句柄转换为一个真正的句柄以共享;
	DuplicateHandle(GetCurrentProcess(),h1,GetCurrentProcess(),&h2,0,false,DUPLICATE_SAME_ACCESS);
	CloseHandle(h2);//真句柄用完必须关闭;
	//*********************************************
	HANDLE h3 = OpenThread(0,true,dwThreadId);//如果有线程ID，可以用此函数获取线程句柄;第二个参数表示可由子进程使用;
		ResumeThread(hThread);//启用指定线程;
	return 0;
}


//***************************************************************************************
//MsgWaitForMultipleObjectsEx()处理流程;
DWORD DoWait(const HANDLE*pHandles,DWORD dHandles,DWORD dwMilleseconds,BOOL bAlertable)
{	
	DWORD dwRet;
	DWORD dwStart = GetTickCount();
	DWORD dwElapsed=0;
	while(TRUE)
	{//执行实际的等待;
		dwRet = MsgWaitForMultipleObjectsEx(dHandles,pHandles,dwMilleseconds-dwElapsed,QS_ALLINPUT,bAlertable?MWMO_ALERTABLE:0);
		if (dwRet==WAIT_OBJECT_0+dHandles)
		{//至少有一个消息已经来到了。提取队列中的所有消息;
			MSG msg;
			while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{
				if (msg.message==WM_QUIT)
				{
					PostQuitMessage((int)msg.wParam);
					dwRet=WM_QUIT;
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if(dwRet==WAIT_TIMEOUT)
				break;
		} 
		else if(dwRet!=WAIT_IO_COMPLETION)
		{	//如果不是APC,那么将中断执行并且返回dwRet;
			break;
		}
		//需要重新调整时间，确认还没有超时.然后循环回去并且再次等待;
		dwElapsed=GetTickCount()-dwStart;
		if (dwMilleseconds<dwElapsed)
		{
			dwRet=WAIT_TIMEOUT;
			break;
		}
	}
	return dwRet;
}
//***************************************************************************************
DWORD WINAPI TestThread(LPVOID lpParameter)
{
	printf("%d: Running: %s\r\n",GetCurrentThreadId(),reinterpret_cast<char*>(lpParameter));

	return 0;
}

static int g_dwMyTlsIndex;//通常将索引保存在全局或静态变量中;
void ThreadLocalStorage()
{	//动态建立TLS槽，槽的索引是一个Dword数值，用于设置或提取保存在每个线程中的LPVOID值。
	DWORD dIndex = TlsAlloc();
	//TlsAlloc初始值是0，如果TlsAlloc返回值是TLS_OUT_OF_INDEXES,那么表示分配TLS失败，TLS槽数量有限，win98是80，win2000后的是1088.
	//如果进程中有许多组件都需要创建大量的槽，那么就可能会出现这个错误;

	//在分配了一个TLS槽后，就可以通过TlsSetValue();和TlsGetValue();分别从槽中设置提取数据;
	TlsSetValue(1,NULL);//dwTlsIndex值win98是0-80，win2000后的是0-1088.
	TlsGetValue(1);
	//使用完槽，必须释放槽,如果槽中存储的是指向某块内存的指针，那么必须先释放指针;
	TlsFree(dIndex);
	//上述这些槽函数通常用在DLLMain中的DLL事件中分别调用.详见Windows并发编程指南P70;

	//静态TLS槽,通过_declspec(thread)修饰符将静态或全局变量转换成一个TLS变量;	
//	_declspec(thread)int* g_dwMyTlsIndex;
	//你仍需要在每个线程中初始化和释放槽，可以在DLLMain中处理。;
	//静态TLS的执行速度比动态TLS块很多，但是只能在静态DLL中使用。当通过LoadLibrary动态加载时，使用静态TLS将是不可靠的;
}

/*
GetCurrentThreadId();获得当前执行线程ID;
GetExitCodeThread(hThread,&dwExitCode);获得指定线程的退出码;程序可以通过退出码来了解程序终止的原因;
下面两个终止线程的API都可以在结束线程时指定一个返回码,通常，如果线程的退出码不为0，那么就表示线程是由于发生了异常操作而退出，而0表示正常退出;
ExitThread();退出线程,并设置退出码;
TerminateThread();//终止线程;这个函数非常危险，应该永远不使用它，被终止的线程可能有一些锁，或正在分配内存，如果调用了此函数，最好立即终止进程
ExitProcess();
TerminateProcess();
C程序可以调用exit/_exit或abort等CRT库函数;
强行终止线程的方法，很有可能会产生问题，资源泄露，孤立锁之类的问题。通常，我们必须通过高层的协调操作来关闭线程，否则程序或用户数据将可能被破坏;
强行终止线程将导致资源泄露。这些泄露资源的数量很小，它们可能在很长时间内都不会引起注意，但对于那些长时间运行的程序来说肯定会造成严重问题。
从线程函数中返回，那么线程将自动退出。这是到目前为止最干净的线程退出方式。;

获得当前线程的(伪)句柄:GetCurrentThread();
//将返回一个伪句柄(Pseudo-Handle)这个值是一个常量（-2）不需要调用CloseHandle，于GetCurrentProcess的工作原理相似，它返回（-1）;
Windows通常将伪句柄解释为“当前线程”因此你不能将这个伪句柄共享给其他线程（其他线程将把这个句柄理解为他们自己），
如果需要将伪句柄转换为一个真正的句柄以共享，那么可以调用DuplicateHandle();这个函数将返回一个可共享的句柄，并且使用完这个句柄必须关闭它。
*/