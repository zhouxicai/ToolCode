
#if defined(WIN32)
//	#include "WindowsIncludes.h"
	#include <iostream>
	#include <Windows.h>
#else
	#include <pthread.h>
	#include <sys/types.h>
#endif
/******************************************/
//临界区锁定义;
#ifdef WIN32
CRITICAL_SECTION critical_region;
#else
pthread_mutex_t critical_region;
#endif
/******************************************/
//临界区初始化;
void InitMutex()
{//如果是类中，可以放到构造函数中;
#ifdef WIN32
	InitializeCriticalSection(&critical_region);
#else
	pthread_mutex_init(&critical_region,0);//第二个参数表示指向属性结构的指针，实际是不需要的，所以设置0，意思是采用默认属性;
#endif
}
//销毁临界区;
void DeleteMutex()
{//如果是类中，可以放到析构函数中;
#ifdef WIN32
	DeleteCriticalSection(&critical_region);
#else
	pthread_mutex_destroy(&critical_region);
#endif
}
/******************************************/
/*存取数据时锁定，结束时调用解锁函数;*/
void LockMutex()
{//锁定临界区;
#ifdef WIN32
	EnterCriticalSection(&critical_region);
#else
	pthread_mutex_lock(&critical_region);
#endif
}
void UnlockMutex()
{//解除临界区的锁定;
#ifdef WIN32
	LeaveCriticalSection(&critical_region);
#else
	pthread_mutex_unlock(&critical_region);
#endif
}
/******************************************/
//互斥;
	HANDLE m_hMutex = CreateMutexW(NULL,FALSE,NULL);
//条件;
	HANDLE sema_ = CreateSemaphoreA (NULL, 1, 10, NULL);
//#include <pthread.h>
//#include <semaphore.h>
	/*
信号量与互斥锁合作;
尽管信号量比互斥锁更灵活，但实际上它却没有互斥锁的用途大。与互斥锁结合起来使用，信号量才能发挥最大作用;
在此情况下，可以创建一个系统，允许多个线程读一个对象，但只允许在没有线程读此对象时，限定一个线程对此对象进行写操作。;

******************************************
LINUX处理互斥锁的函数;
操作;					相关函数说明;
初始化互斥锁;			pthread_mutex_init
使互斥锁保持一致;		pthread_mutex_consistent_np
锁定互斥锁;				pthread_mutex_lock
解除锁定互斥锁;			pthread_mutex_unlock
使用非阻塞互斥锁锁定;	pthread_mutex_trylock 
销毁互斥锁;				pthread_mutex_destroy 

******************************************
Mutex可以被抽象为四个操作：;
- 创建; Create  
- 加锁; Lock  
- 解锁; Unlock  
- 销毁; Destroy  
不同操作系统中提供的Mutex函数: 动作\系统;
操作;		Win32					Linux					Solaris;
创建;		CreateMutex				pthread_mutex_init		mutex_init
加锁;		WaitForSingleObject		pthread_mutex_lock		mutex_lock
解锁;		ReleaseMutex			pthread_mutex_unlock	mutex_unlock
销毁;		CloseHandle				pthread_mutex_destroy	mutex_destroy
******************************************
Semaphore可以被抽象为五个操作： ; 
- 创建; Create  
- 等待; Wait：  
线程等待信号量，如果值大于0，则获得，值减一；如果只等于0，则一直线程进入睡眠状态，知道信号量值大于0或者超时。  ;
-释放; Post  
执行释放信号量，则值加一；如果此时有正在等待的线程，则唤醒该线程。  ;
-试图等待; TryWait  
如果调用TryWait，线程并不真正的去获得信号量，还是检查信号量是否能够被获得，如果信号量值大于0，则TryWait返回成功；否则返回失败。  ;
-销毁; Destroy  
POSIX线程是C程序中处理线程的一个标准接口,在大多数Unix系统上都可用Pthreads大约定义了60个函数。;
操作;		Win32					POSIX
创建;		CreateSemaphore			sem_init
等待;		WaitForSingleObject		sem _wait
释放;		ReleaseMutex			sem _post
试图等待;	WaitForSingleObject		sem _trywait
销毁;		CloseHandle				sem_destroy 
#include <process.h>//线程C运行时库;
*/