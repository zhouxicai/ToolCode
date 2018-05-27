#include "TimeCount.h"

TimeCount timeCount ;

void TimeCount::InitTime()
{		
	HANDLE thread = GetCurrentThread(); //��ȡ��ǰ�̵߳�һ��α���
    DWORD_PTR oldMask = SetThreadAffinityMask(thread, 1); 
	//�õ�CPUʱ�Ӽ�ʱ��Ƶ��
	QueryPerformanceFrequency(&frequency);
	//�õ�CPU��ʱ��ʱ��
	QueryPerformanceCounter(&startTime);
	//cout <<	"\n�߾��ȼ�ʱ����ʼ��ʱ...\n" ;
}

double TimeCount::GetNowTime()
{	//��/����/΢��/����/Ƥ��/����/
	//1s=10^3ms(����)=10^6��s(΢��)=10^9ns(����)=10^12ps(Ƥ��)=10^15fs(����)
	//1������8�������ң�10������3ǧ�� 100������3�ڣ�1����30��
	//�õ�CPU��ʱ��ʱ��
	QueryPerformanceCounter(&lastTime);	
	nowTime = ( lastTime.QuadPart- startTime.QuadPart ) / (double)frequency.QuadPart ;
	//cout<<name <<",�߾��ȼ�ʱ������ʱ��:"<< nowTime <<"��,��"
	//									 << nowTime*1000 <<"���룬"
	//									 << nowTime*1000000 <<"΢��"<<endl ;
	return nowTime ; 
}

void TimeCount::ResetTime()
{
	//�õ�CPU��ʱ��ʱ��
	QueryPerformanceCounter(&startTime);
}

WORD TimeCount::GetSystemTime()
{	//��߾�ȷ������
	SYSTEMTIME st ;
	GetLocalTime(&st) ;	
	//printf("��ǰϵͳ���ں�ʱ��: %d��%d��%d�գ�����%d ��%dʱ%d��%d��%d���� \n" , 
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
