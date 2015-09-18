
#if defined(WIN32)
//	#include "WindowsIncludes.h"
	#include <iostream>
	#include <Windows.h>
#else
	#include <pthread.h>
	#include <sys/types.h>
#endif
/******************************************/
//�ٽ���������;
#ifdef WIN32
CRITICAL_SECTION critical_region;
#else
pthread_mutex_t critical_region;
#endif
/******************************************/
//�ٽ�����ʼ��;
void InitMutex()
{//��������У����Էŵ����캯����;
#ifdef WIN32
	InitializeCriticalSection(&critical_region);
#else
	pthread_mutex_init(&critical_region,0);//�ڶ���������ʾָ�����Խṹ��ָ�룬ʵ���ǲ���Ҫ�ģ���������0����˼�ǲ���Ĭ������;
#endif
}
//�����ٽ���;
void DeleteMutex()
{//��������У����Էŵ�����������;
#ifdef WIN32
	DeleteCriticalSection(&critical_region);
#else
	pthread_mutex_destroy(&critical_region);
#endif
}
/******************************************/
/*��ȡ����ʱ����������ʱ���ý�������;*/
void LockMutex()
{//�����ٽ���;
#ifdef WIN32
	EnterCriticalSection(&critical_region);
#else
	pthread_mutex_lock(&critical_region);
#endif
}
void UnlockMutex()
{//����ٽ���������;
#ifdef WIN32
	LeaveCriticalSection(&critical_region);
#else
	pthread_mutex_unlock(&critical_region);
#endif
}
/******************************************/
//����;
	HANDLE m_hMutex = CreateMutexW(NULL,FALSE,NULL);
//����;
	HANDLE sema_ = CreateSemaphoreA (NULL, 1, 10, NULL);
//#include <pthread.h>
//#include <semaphore.h>
	/*
�ź����뻥��������;
�����ź����Ȼ�����������ʵ������ȴû�л���������;���뻥�����������ʹ�ã��ź������ܷ����������;
�ڴ�����£����Դ���һ��ϵͳ���������̶߳�һ�����󣬵�ֻ������û���̶߳��˶���ʱ���޶�һ���̶߳Դ˶������д������;

******************************************
LINUX���������ĺ���;
����;					��غ���˵��;
��ʼ��������;			pthread_mutex_init
ʹ����������һ��;		pthread_mutex_consistent_np
����������;				pthread_mutex_lock
�������������;			pthread_mutex_unlock
ʹ�÷���������������;	pthread_mutex_trylock 
���ٻ�����;				pthread_mutex_destroy 

******************************************
Mutex���Ա�����Ϊ�ĸ�������;
- ����; Create  
- ����; Lock  
- ����; Unlock  
- ����; Destroy  
��ͬ����ϵͳ���ṩ��Mutex����: ����\ϵͳ;
����;		Win32					Linux					Solaris;
����;		CreateMutex				pthread_mutex_init		mutex_init
����;		WaitForSingleObject		pthread_mutex_lock		mutex_lock
����;		ReleaseMutex			pthread_mutex_unlock	mutex_unlock
����;		CloseHandle				pthread_mutex_destroy	mutex_destroy
******************************************
Semaphore���Ա�����Ϊ��������� ; 
- ����; Create  
- �ȴ�; Wait��  
�̵߳ȴ��ź��������ֵ����0�����ã�ֵ��һ�����ֻ����0����һֱ�߳̽���˯��״̬��֪���ź���ֵ����0���߳�ʱ��  ;
-�ͷ�; Post  
ִ���ͷ��ź�������ֵ��һ�������ʱ�����ڵȴ����̣߳����Ѹ��̡߳�  ;
-��ͼ�ȴ�; TryWait  
�������TryWait���̲߳���������ȥ����ź��������Ǽ���ź����Ƿ��ܹ�����ã�����ź���ֵ����0����TryWait���سɹ������򷵻�ʧ�ܡ�  ;
-����; Destroy  
POSIX�߳���C�����д����̵߳�һ����׼�ӿ�,�ڴ����Unixϵͳ�϶�����Pthreads��Լ������60��������;
����;		Win32					POSIX
����;		CreateSemaphore			sem_init
�ȴ�;		WaitForSingleObject		sem _wait
�ͷ�;		ReleaseMutex			sem _post
��ͼ�ȴ�;	WaitForSingleObject		sem _trywait
����;		CloseHandle				sem_destroy 
#include <process.h>//�߳�C����ʱ��;
*/