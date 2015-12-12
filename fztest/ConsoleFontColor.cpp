// ConsoleColor.h

#pragma once
#include <iostream>
#include <windows.h>

inline std::ostream& blue(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
		|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	return s;
}
inline std::ostream& red(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hStdout, 
		FOREGROUND_RED|FOREGROUND_INTENSITY);
	return s;
}
inline std::ostream& green(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hStdout, 
		FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	return s;
}
inline std::ostream& yellow(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hStdout, 
		FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
	return s;
}
inline std::ostream& white(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hStdout, 
		FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	return s;
}
struct color {
	color(WORD attribute):m_color(attribute){};
	WORD m_color;
};
template <class _Elem, class _Traits>
std::basic_ostream<_Elem,_Traits> &operator << ( std::basic_ostream<_Elem,_Traits>& i , color& c )
{
	HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hStdout,c.m_color);
	return i;
}
void SetFontcolor()
{
	for(int i=1;i<10;i++)  
	{  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i);  
		std::cout<<"i am color!"<<std::endl;  
	}   
}

void MCloseShutoffButton()
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

//
//void main()
//{
//
//	system("pause");
//}