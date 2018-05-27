#ifndef _IME_H_
#define _IME_H_
// Windows Header Files:
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "stdlib.h"
#include "stdio.h"
#pragma comment(lib, "imm32.lib")

class CIME
{
	public:
		// Foward declarations of functions included in this code module:
		ATOM	MyRegisterClass(HINSTANCE hInstance);
		BOOL	InitInstance(HINSTANCE hInstance, int nCmdShow , HWND hwnd);
		void	WndProc(HWND, UINT, WPARAM, LPARAM);
		//LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
		void	ShowIME(int nCmdShow){    ShowWindow(g_hText, nCmdShow); UpdateWindow(g_hText);::SetFocus(g_hText);};
		DWORD HandleCandidate(HWND hWnd);//取出候选文字列表
		BOOL  HandleConversion(HWND hWnd, LPDWORD lpfdwConversion, LPDWORD lpfdwSentence);//输入模式切换
		BOOL  HandleGetOpenStatus(HWND hWnd);
		LONG  HandleComposition(HWND hWnd);//取得组字字符串
		int   HandleChangeLanguage(char* lpszIMENameBuf, long lBufSize);//重置输入法，

	private:
		#define MAX_LOADSTRING 100

		// Global Variables:
		TCHAR szTitle[MAX_LOADSTRING];			// The title bar text
		TCHAR szWindowClass[MAX_LOADSTRING];	// The title bar text
		
		HINSTANCE   g_hInstance;
		HWND        g_hWnd;
		HWND        g_hWndComposition;
		HWND        g_hWndCandidate;
		HWND        g_hWndStatus;
		HWND        g_hText;
		char        g_szLanguageName[200];
		wchar_t     g_szBuf[1024];

};
extern CIME cime;

#endif