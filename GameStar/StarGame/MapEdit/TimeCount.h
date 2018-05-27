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
		/*��ý���ʱ��*/
		void InitTime();	  //��ʼʱ��
		double GetNowTime();	  //
		void ResetTime();
		/*ϵͳʱ��*/
		WORD GetSystemTime();
		void SetSystemTime(int);

		void TimeLapseTest(); //��ʱ����

//		list<double>dTimeLapseList;
};
extern  TimeCount timeCount ;
#endif