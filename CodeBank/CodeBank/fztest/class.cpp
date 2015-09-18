#include<Windows.h>
#include <iostream>
#include <assert.h>
using namespace std;

#pragma pack(push,1)
class A
{
public:
	int a;
	int aa;
	char ca;
};  

class B : public A
{
public:
	int b;
//	double bb;
};
#pragma pack(pop)

A* GetPtrA()
{
	A oa;
	return &oa; 
}
A GetObjectA()
{
	A oa;
	return oa; 
}
void CloseShutoffButton()
{
	wchar_t  buf[100]; 
	GetConsoleTitleW( buf , sizeof(wchar_t)*100 );		//得到控制台窗口的标题
	HWND   hwnd   = ::FindWindowW( NULL , buf );		//根据标题查找窗口句柄
	HMENU  hmenu  = ::GetSystemMenu( hwnd , FALSE );   //得到这个窗口的菜单
	::RemoveMenu( hmenu , SC_CLOSE,MF_BYCOMMAND );		//移除ClOSE菜单
	::RemoveMenu( hmenu , SC_MINIMIZE,MF_BYCOMMAND );	
	::RemoveMenu( hmenu , SC_MAXIMIZE,MF_BYCOMMAND );	
	::RemoveMenu( hmenu , SC_MOUSEMENU,MF_BYCOMMAND );	
	::RemoveMenu( hmenu , SC_SIZE,MF_BYCOMMAND );	
};
int thread[100]={0};
void WINAPI CallWavedevThread1 ()
{	
	for (int i = 0 ;i<100;i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()); 
		thread[i] = i;
		std::cout<<"thread[]:"<<thread[i]<<std::endl;
	}
	//CloseShutoffButton();
};
void WINAPI CallWavedevThread2 ()
{
	for (int i = 0 ;i<100;i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()); 
		thread[i] = i;
		std::cout<<"thread[]:"<<thread[i]<<std::endl;
	}
	//CloseShutoffButton();
};
//void main()
//{
//	//Processor
//	
//
//	HANDLE ct1 = CreateThread( NULL, 0,  (LPTHREAD_START_ROUTINE)CallWavedevThread1, NULL, 0, NULL);
//	HANDLE ct2 = CreateThread( NULL, 0,  (LPTHREAD_START_ROUTINE)CallWavedevThread2, NULL, 0, NULL);
//	GetProcessWorkingSetSize(ct1,(PSIZE_T)1,(PSIZE_T)8);
//
//	std::cout<<"GetProcessWorkingSetSize(ct1,(PSIZE_T)1,(PSIZE_T)8):"<<GetProcessWorkingSetSize(ct1,(PSIZE_T)1,(PSIZE_T)8)<<std::endl;
//
//	A oca;
//	A * pca;
//
//	A  anum[10];
//	A *pnum[10]={0};
//
//	for(int i = 0 ; i < 10 ; i++ )
//	{
//		pnum[i] = GetPtrA();
//		anum[i] .a = i;
//		pnum[i]->a = i;
//		pnum[i]->aa = i+10;
//		cout<<"pnum["<<i<<"]->a="<<pnum[i]->a<<" pnum["<<i<<"]->aa="<<pnum[i]->aa<<endl;
//	}
//
//	//设置全局字体颜色
////	system("color 02"); 
//	cout<<"sizeof oca:"<<sizeof(oca)<<endl;
//	cout<<"sizeof pca:"<<sizeof(pca)<<endl; 
//	cout<<"sizeof A:"<<sizeof(A)<<endl;
//
//	cout<<"sizeof anum:"<<sizeof(anum)<<endl;
//	cout<<"sizeof pnum:"<<sizeof(pnum)<<endl;
//
//	B b;
////	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_BLUE);
//	cout<<"B:"<<sizeof(B)<<endl;
//	cout<<"b:"<<sizeof(b)<<endl;
//
//	for(int i = 0 ; i < 10 ; i++ )
//	{
//		cout<<"anum["<<i<<"].a="<<anum[i].a<<endl;
//	}
//	cout<<endl;
//	memset(anum, 0, sizeof(anum));
//	for(int i = 0 ; i < 10 ; i++ )
//	{
//		cout<<"anum["<<i<<"].a="<<anum[i].a<<endl;
//	}
//
//
//	system("pause");
//};