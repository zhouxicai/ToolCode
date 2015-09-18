#include <stdio.h>
#include <Windows.h>

DWORD WINAPI TestThread(LPVOID);
//�����������ȴ��windowsϵͳ���еĺ�����ͳ��Ϊcallback������ĳЩAPI����Ҫ����callback��Ϊ�����֮һ����SetTimer��LineDDA��EnumObjects;
VOID CALLBACK APCProc(LONG_PTR dwParam){  
	TCHAR* pStr = (TCHAR*)dwParam;   
	LoadLibraryW(pStr);//LoadLibraryA�ĵ�ַ��ô��ã��ҾͲ���˵��;
}
int main1()
{
	//*********************************************
	HANDLE hThread;
	DWORD dwThreadId;//�߳�ID
	hThread = CreateThread(NULL,0,&TestThread,"Hello Thread",0,&dwThreadId);
	if (!hThread)
	{
		fprintf(stderr,"Thread creation failed: %d\r\n",GetLastError());
		return -1;
	}
	printf("%d:Created thread %x (ID %D)\r\n",GetCurrentThreadId(),hThread,dwThreadId);
	//*********************************************
	//�ȴ��߳��˳���������̵߳��˳���;
	DWORD wr = WaitForSingleObject(hThread,INFINITE);//INFINITE��ʾһֱ�ȴ���0��ʾ�������أ���������
	switch(wr)
	{
	case WAIT_OBJECT_0://����ֵWAIT_OBJECT_0��ʾ�ȴ��Ķ��󱻴�����;
		break;
	case WAIT_TIMEOUT:
		break;
	case  WAIT_FAILED:
		{
			DWORD dsError = GetLastError();
			break;
		}
	case WAIT_ABANDONED://���������з���ֵ����ʾ֮ǰ�ڻ������ϵȴ��Ĵ���û����ȷ���ͷŻ����壬�����������ֵ����ȥ������󣬵�����ȴ�����ʵ���ǳɹ��ġ�������û����������Ȩ��;
		break;
	}
	//*********************************************
	//�ȴ����������;
	const int cHandles = 5;
	HANDLE wait_handles[cHandles];
	DWORD wm = WaitForMultipleObjects(cHandles,&wait_handles[0],false,INFINITE);
	if (wm>=WAIT_OBJECT_0&&wm<WAIT_OBJECT_0+cHandles)
	{	//signaled��ʾһ���Ѵ����Ķ���;
		HANDLE hSignaled = wait_handles[wm-WAIT_OBJECT_0];
	} 
	else if(wm>=WAIT_ABANDONED_0&&wm<WAIT_ABANDONED_0+cHandles)
	{	//hAbandonedָ��һ���������������ľ��;
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
	//Ϊ�˴��������ͷַ���Ϣ�������ʹ��MsgWaitForMultipleObjects/Ex()��������������ʹ�߳��ڵȴ�һ������ͬʱ�����Էַ���Ϣ;
	//����ڵȴ�����������֮ǰ����һ���µ���Ϣ�������̵߳���Ϣ���У���ô���API�����أ����������߿��Դ����������Ϣ��
	DWORD 
	mwm = MsgWaitForMultipleObjects(cHandles,&wait_handles[0],true,1000,QS_ALLINPUT);//QS_ALLINPUT��ʾ�κ���Ϣ�ĵ�������ʹ�̱߳����ѡ�;
	//��ĳЩ����£������ϣ��������Ҫ�������Ϣ���ͣ�Ϊ��ȷ������ȴ��Ǿ����ȴ�������ʹ��Ex��չ��������dwFlags����ΪMWMO_ALERTABLE;
	mwm = MsgWaitForMultipleObjectsEx(cHandles,&wait_handles[0],1000,QS_ALLINPUT,MWMO_ALERTABLE);
	mwm = CoWaitForMultipleHandles(COWAIT_WAITALL,1000,cHandles,&wait_handles[0],NULL);//����������Զ��ַ��ض����͵���Ϣ;
	//*********************************************
	//APC�����첽���ù��̡��̶߳��и�APC���У�QueueUserAPC�����̵߳�APC�����в���һ��APC���� ;
	//����pfnAPC��dwData��ʾ������ָ��/�������ԣ�hThread��ʾ���APCҪ������߳�;
	QueueUserAPC((PAPCFUNC)APCProc,hThread,(ULONG_PTR)("c:\\sysnap.dll"));

	//*********************************************
	DWORD dwExitCode;//�����߳��˳���;
	//TerminateThread(hThread,dwExitCode);//��ֹ�߳�;
	GetExitCodeThread(hThread,&dwExitCode);
	printf("%d: Thread exited: %d\r\n");
	CloseHandle(hThread);
	//*********************************************
	HANDLE h1 = GetCurrentThread();//��ȡα���;
	HANDLE h2;//���洢����;
	//��α���ת��Ϊһ�������ľ���Թ���;
	DuplicateHandle(GetCurrentProcess(),h1,GetCurrentProcess(),&h2,0,false,DUPLICATE_SAME_ACCESS);
	CloseHandle(h2);//�����������ر�;
	//*********************************************
	HANDLE h3 = OpenThread(0,true,dwThreadId);//������߳�ID�������ô˺�����ȡ�߳̾��;�ڶ���������ʾ�����ӽ���ʹ��;
		ResumeThread(hThread);//����ָ���߳�;
	return 0;
}


//***************************************************************************************
//MsgWaitForMultipleObjectsEx()��������;
DWORD DoWait(const HANDLE*pHandles,DWORD dHandles,DWORD dwMilleseconds,BOOL bAlertable)
{	
	DWORD dwRet;
	DWORD dwStart = GetTickCount();
	DWORD dwElapsed=0;
	while(TRUE)
	{//ִ��ʵ�ʵĵȴ�;
		dwRet = MsgWaitForMultipleObjectsEx(dHandles,pHandles,dwMilleseconds-dwElapsed,QS_ALLINPUT,bAlertable?MWMO_ALERTABLE:0);
		if (dwRet==WAIT_OBJECT_0+dHandles)
		{//������һ����Ϣ�Ѿ������ˡ���ȡ�����е�������Ϣ;
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
		{	//�������APC,��ô���ж�ִ�в��ҷ���dwRet;
			break;
		}
		//��Ҫ���µ���ʱ�䣬ȷ�ϻ�û�г�ʱ.Ȼ��ѭ����ȥ�����ٴεȴ�;
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

static int g_dwMyTlsIndex;//ͨ��������������ȫ�ֻ�̬������;
void ThreadLocalStorage()
{	//��̬����TLS�ۣ��۵�������һ��Dword��ֵ���������û���ȡ������ÿ���߳��е�LPVOIDֵ��
	DWORD dIndex = TlsAlloc();
	//TlsAlloc��ʼֵ��0�����TlsAlloc����ֵ��TLS_OUT_OF_INDEXES,��ô��ʾ����TLSʧ�ܣ�TLS���������ޣ�win98��80��win2000�����1088.
	//���������������������Ҫ���������Ĳۣ���ô�Ϳ��ܻ�����������;

	//�ڷ�����һ��TLS�ۺ󣬾Ϳ���ͨ��TlsSetValue();��TlsGetValue();�ֱ�Ӳ���������ȡ����;
	TlsSetValue(1,NULL);//dwTlsIndexֵwin98��0-80��win2000�����0-1088.
	TlsGetValue(1);
	//ʹ����ۣ������ͷŲ�,������д洢����ָ��ĳ���ڴ��ָ�룬��ô�������ͷ�ָ��;
	TlsFree(dIndex);
	//������Щ�ۺ���ͨ������DLLMain�е�DLL�¼��зֱ����.���Windows�������ָ��P70;

	//��̬TLS��,ͨ��_declspec(thread)���η�����̬��ȫ�ֱ���ת����һ��TLS����;	
//	_declspec(thread)int* g_dwMyTlsIndex;
	//������Ҫ��ÿ���߳��г�ʼ�����ͷŲۣ�������DLLMain�д���;
	//��̬TLS��ִ���ٶȱȶ�̬TLS��ܶ࣬����ֻ���ھ�̬DLL��ʹ�á���ͨ��LoadLibrary��̬����ʱ��ʹ�þ�̬TLS���ǲ��ɿ���;
}

/*
GetCurrentThreadId();��õ�ǰִ���߳�ID;
GetExitCodeThread(hThread,&dwExitCode);���ָ���̵߳��˳���;�������ͨ���˳������˽������ֹ��ԭ��;
����������ֹ�̵߳�API�������ڽ����߳�ʱָ��һ��������,ͨ��������̵߳��˳��벻Ϊ0����ô�ͱ�ʾ�߳������ڷ������쳣�������˳�����0��ʾ�����˳�;
ExitThread();�˳��߳�,�������˳���;
TerminateThread();//��ֹ�߳�;��������ǳ�Σ�գ�Ӧ����Զ��ʹ����������ֹ���߳̿�����һЩ���������ڷ����ڴ棬��������˴˺��������������ֹ����
ExitProcess();
TerminateProcess();
C������Ե���exit/_exit��abort��CRT�⺯��;
ǿ����ֹ�̵߳ķ��������п��ܻ�������⣬��Դй¶��������֮������⡣ͨ�������Ǳ���ͨ���߲��Э���������ر��̣߳����������û����ݽ����ܱ��ƻ�;
ǿ����ֹ�߳̽�������Դй¶����Щй¶��Դ��������С�����ǿ����ںܳ�ʱ���ڶ���������ע�⣬��������Щ��ʱ�����еĳ�����˵�϶�������������⡣
���̺߳����з��أ���ô�߳̽��Զ��˳������ǵ�ĿǰΪֹ��ɾ����߳��˳���ʽ��;

��õ�ǰ�̵߳�(α)���:GetCurrentThread();
//������һ��α���(Pseudo-Handle)���ֵ��һ��������-2������Ҫ����CloseHandle����GetCurrentProcess�Ĺ���ԭ�����ƣ������أ�-1��;
Windowsͨ����α�������Ϊ����ǰ�̡߳�����㲻�ܽ����α�������������̣߳������߳̽������������Ϊ�����Լ�����
�����Ҫ��α���ת��Ϊһ�������ľ���Թ�����ô���Ե���DuplicateHandle();�������������һ���ɹ���ľ��������ʹ��������������ر�����
*/