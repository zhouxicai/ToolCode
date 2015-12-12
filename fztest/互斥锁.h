//#if 0
//#ifdef __cplusplus
// extern "C" {
//#endif
//
//#ifdef _POSIX_THREAD
//
//#include <pthread.h>
//#include <sys/time.h>
//
//typedef pthread_mutex_t mutex_t;
//typedef pthread_mutexattr_t mutexattr_t;
//typedef void SECURITY_ATTRIBUTES;
//
//#elif defined(_WIN32_THREAD)
//#ifndef _WIN32_WINNT
//# define _WIN32_WINNT 0x0501
//#endif
//#include <winsock2.h>
//
//typedef struct 
// {
//    int type_;
//    union
//     {
//        HANDLE proc_lock_;
//        CRITICAL_SECTION thr_lock_;
//    };
//}mutex_t;
//typedef void mutexattr_t;
//
//#else
////#error std::cout<<"Currently only support win32 and posix thread models"<<std::endl;
//#endif
//
//#define MUTEX_THREAD_SHARED  1
//#define MUTEX_PROCESS_SHARED 2
//
//int mutex_init(mutex_t*m,int scope,int type,const char* name,mutexattr_t* attr,SECURITY_ATTRIBUTES* sa);
//
//int mutex_lock(mutex_t* m);
//
//int mutex_timedlock(mutex_t* m,const struct timeval* val);
//
//int mutex_trylock(mutex_t* m);
//
//int mutex_unlock(mutex_t* m);
//
//int mutex_destroy(mutex_t* m);
//
//#ifdef __cplusplus
//}
//#endif
//
////实现 ;
//int mutex_init(mutex_t* m,int scope,int type,const char* name,mutexattr_t* attr,SECURITY_ATTRIBUTES* sa)
//{
//ifdef _POSIX_THREAD
//   int ret, init = 0;
//   pthread_mutexattr_t tmp;
//   if(0==attr) attr = &tmp;
//   if(attr==&tmp)
//    {
//       ret = pthread_mutexattr_init(attr);
//        if (0==ret) init = 1;
//    }
//    if(0==ret && 0 != scope)
//     {
//#ifdef  _POSIX_THREAD_PROCESS_SHARED
//        ret = pthread_mutexattr_setpshared(attr,lock_scope);
//#endif
//    }
//    if(0==ret && 0 != type)
//     {
//#ifdef __USE_UNIX98
//        ret = pthread_mutexattr_settype(attr,lock_type);
//#endif
//    }
//    if (0==ret)
//        ret = pthread_mutex_init(m,attr);
//    if (1==init && attr==&tmp)
//        pthread_mutexattr_destroy(attr);
//    return ret;
//#else
//    m->type_ = scope;
//    switch (m->type_)
//     {
//    case MUTEX_THREAD_SHARED:
//        __try
//         {
//            InitializeCriticalSection(&m->thr_lock_);
//        }
//        __except(EXCEPTION_EXECUTE_HANDLER)
//         {
//            return -1;
//        }
//        return 0;
//
//    case MUTEX_PROCESS_SHARED:
//        m->proc_lock_ = CreateMutexA(sa,FALSE,name);
//        if (0==m->proc_lock_&&ERROR_ACCESS_DENIED==GetLastError())
//            m->proc_lock_ = OpenMutexA(MUTEX_ALL_ACCESS,FALSE,name);
//        if (0==m->proc_lock_)
//            return -1;       
//        return 0;
//
//    default: return -1;
//    }
//#endif
//}
//
//int mutex_lock(mutex_t* m)
// {
//#ifdef _POSIX_THREAD
//    return pthread_mutex_lock(m);
//#else
//    switch(m->type_)
//     {
//    case MUTEX_THREAD_SHARED:
//        EnterCriticalSection(&m->thr_lock_);
//        return 0;
//   
//    case MUTEX_PROCESS_SHARED:
//        switch (WaitForSingleObject (m->proc_lock_, INFINITE))
//         {
//        case WAIT_OBJECT_0:  return 0;
//        case WAIT_ABANDONED: return 1;
//        default: return -1;
//        }
//        break;
//
//    default: return -1;
//    }
//#endif
//}
//
//int mutex_timedlock(mutex_t* m,const struct timeval* val)
// {
//    //val should be an absolute time.
//#ifdef _POSIX_THREAD
//     struct timespec ts = {.tv_sec = val->tv_sec,.tv_nsec=val->tv_usec*1000};
//    return pthread_mutex_timedlock(m,&ts);
//#else
//    switch(m->type_)
//     {
//    // not support CriticalSection,so simply return -1.
//    case MUTEX_THREAD_SHARED:
//        return -1;
//
//    case MUTEX_PROCESS_SHARED:
//         {
//            FILETIME ft;
//            struct timeval cur,diff;
//       
//             GetSystemTimeAsFileTime(&ft);
//             cur = FileTime2TimeVal(&ft);
//             diff = timeval_sub(val,&cur);
//
//             switch (WaitForSingleObject (m->proc_lock_, timeval_millsec(&diff)))
//              {
//             case WAIT_OBJECT_0:  return 0;
//             case WAIT_ABANDONED: return 1;
//             case WAIT_TIMEOUT:      return 2;
//             default: return -1;
//             }
//         }
//         break;
//
//     default: return -1;
//     }
// #endif
// }
//
// int mutex_trylock(mutex_t* m)
//  {
// #ifdef _POSIX_THREAD
//     return pthread_mutex_trylock(m);
// #else
//     switch(m->type_)
//      {
//     case MUTEX_THREAD_SHARED:
//         if (!TryEnterCriticalSection(&m->thr_lock_))
//             return -1;
//         return 0;
//        
//     case MUTEX_PROCESS_SHARED:
//         switch (WaitForSingleObject (m->proc_lock_, 0))
//          {
//         case WAIT_OBJECT_0:  return 0;
//         case WAIT_ABANDONED: return 1;
//         case WAIT_TIMEOUT:   return 2;
//         default: return -1;
//         }
//         break;
//
//     default: return -1;
//     }
// #endif
// }
//
// int mutex_unlock(mutex_t* m)
//  {
// #ifdef _POSIX_THREAD
//     return pthread_mutex_unlock(m);
// #else
//     switch(m->type_)
//      {
//     case MUTEX_THREAD_SHARED:
//         LeaveCriticalSection(&m->thr_lock_);
//         return 0;
//
//     case MUTEX_PROCESS_SHARED:
//         if (!ReleaseMutex(m->proc_lock_))
//             return -1;
//         return 0;
//
//     default: return -1;
//     }
// #endif
// }
//
// int mutex_destroy(mutex_t* m)
//  {
// #ifdef _POSIX_THREAD
//     return pthread_mutex_destroy(m);
// #else
//     switch(m->type_)
//      {
//     case MUTEX_THREAD_SHARED:
//         DeleteCriticalSection(&m->thr_lock_);
//         return 0;
//
//     case MUTEX_PROCESS_SHARED:
//         if (!CloseHandle(m->proc_lock_))
//             return -1;
//         return 0;
//
//     default: return -1;
//     }
// #endif
// }
//
//#endif
//

#ifndef LimitSingleInstance_H
#define LimitSingleInstance_H

#include <windows.h> 

 //This code is from Q243953 in case you lose the article and wonder
 //where this code came from.
 class CLimitSingleInstance
 {
 protected:
	 DWORD  m_dwLastError;
	 HANDLE m_hMutex;

 public:
	 CLimitSingleInstance(TCHAR *strMutexName)
	 {
		 //Make sure that you use a name that is unique for this application otherwise;
		 //two apps may think they are the same if they are using same name for;
		 //3rd parm to CreateMutex;
		 m_hMutex = CreateMutex(NULL, FALSE, strMutexName); //do early
		 m_dwLastError = GetLastError(); //save for use later...
	 }

	 ~CLimitSingleInstance() 
	 {
		 if (m_hMutex)  //Do not forget to close handles.
		 {
			 CloseHandle(m_hMutex); //Do as late as possible.
			 m_hMutex = NULL; //Good habit to be in.
		 }
	 }

	 //确保拥有互斥对象的线程对被保护资源的独自访问 ;  
	DWORD Lock(void) const  
	{  
	    DWORD lk = WaitForSingleObject(m_hMutex, INFINITE);  
		return lk;
	}  
	  
	//释放当前线程拥有的互斥对象，以使其它线程可以拥有互斥对象，对被保护资源进行访问   ;
	BOOL Unlock(void) const  
	{  
		return ::ReleaseMutex(m_hMutex);  
	}  


	BOOL IsAnotherInstanceRunning() 
	{
		 return (ERROR_ALREADY_EXISTS == m_dwLastError);
	}
 };
#endif
