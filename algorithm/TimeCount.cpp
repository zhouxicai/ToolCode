#include "TimeCount.h"

TimeCount timeCount ;

void TimeCount::InitTime()
{		
	HANDLE thread = GetCurrentThread(); //获取当前线程的一个伪句柄
    DWORD_PTR oldMask = SetThreadAffinityMask(thread, 1); 
	//得到CPU时钟计时器频率
	QueryPerformanceFrequency(&frequency);
	//得到CPU计时器时间
	QueryPerformanceCounter(&startTime);
	//cout <<	"\n高精度计时器开始计时...\n" ;
}

double TimeCount::GetNowTime()
{	//秒/毫秒/微秒/纳秒/皮秒/飞秒/
	//1s=10^3ms(毫秒)=10^6μs(微秒)=10^9ns(纳秒)=10^12ps(皮秒)=10^15fs(飞秒)
	//1毫秒是8百万左右，10毫秒是3千万 100毫秒是3亿，1秒是30亿
	//得到CPU计时器时间
	QueryPerformanceCounter(&lastTime);	
	nowTime = ( lastTime.QuadPart- startTime.QuadPart ) / (double)frequency.QuadPart ;
	//cout<<name <<",高精度计时器运行时间:"<< nowTime <<"秒,即"
	//									 << nowTime*1000 <<"毫秒，"
	//									 << nowTime*1000000 <<"微秒"<<endl ;
	return nowTime ; 
}

void TimeCount::ResetTime()
{
	//得到CPU计时器时间
	QueryPerformanceCounter(&startTime);
}

WORD TimeCount::GetSystemTime()
{	//最高精确到毫秒
	SYSTEMTIME st ;
	GetLocalTime(&st) ;	
	//printf("当前系统日期和时间: %d年%d月%d日，星期%d ，%d时%d分%d秒%d毫秒 \n" , 
	//		st.wYear , st.wMonth , st.wDay , st.wDayOfWeek ,
	//		st.wHour , st.wMinute ,st.wSecond , st.wMilliseconds
	//	   );
	return st.wMilliseconds ;
}

void TimeCount::TimeLapseTest()
{	

}

void TimeCount::SetSystemTime(int hour)
{
	SYSTEMTIME SetPCTime ;
	GetLocalTime(&SetPCTime) ;
	SetPCTime.wHour += (WORD)hour ;
	SetLocalTime(&SetPCTime);
}
