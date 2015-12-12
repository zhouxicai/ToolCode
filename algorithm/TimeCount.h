#ifndef TIME_COUNT_H
#define TIME_COUNT_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
class TimeCount 
{ 
	private:
		LARGE_INTEGER  startTime, lastTime, frequency;
		double nowTime;
		
		
	public:	
		/*多媒体计时器*/
		void InitTime();	  //开始时间
		double GetNowTime();	  //
		void ResetTime();
		/*系统时间*/
		WORD GetSystemTime();
		void SetSystemTime(int);

		void TimeLapseTest(); //延时测试

//		list<double>dTimeLapseList;
};
extern  TimeCount timeCount ;
#endif