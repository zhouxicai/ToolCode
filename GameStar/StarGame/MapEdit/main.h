#ifndef _MAIN_H
#define _MAIN_H



#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

	#include"stdafx.h"
	#include <fstream>
	#include <vector>

	#include <dshow.h>
	#include <ddraw.h>

	#include "ddutil.h"
	#include "graph.h"
	#include "MapEdt.h"
//	#include "Player.h"
//	#include "DXInput.h"
//	#include "SetGame.h"
	#include "GameGUI.h"
//	#include "TimeCount.h"

//防止大家忘了把ddraw.lib及dxguid.lib加入工程

#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "Winmm.lib")
//	#include "netbase/NetManager.h"



//说明
enum	eBitmap
{		
	SPrimary  ,	//主页面
	SBuffer   ,	//缓冲页面
	主菜单	  ,	//主菜单按钮
	GameBack  ,	//游戏背景图
	SXbmp     ,	//mouse图标
	STile     ,	//地图贴片
	MapBtn    ,	//地图编辑器按钮
	MM2TankB  ,	//战车贴片
	BaseBulle ,	//基本子弹
	机甲	  ,
	BackMap	  ,	//大地图
	MicroMap  , //小地图
	MicroMapZoom  , //可缩放精确小地图
	BigMap	  , //大地图
	DDSNum    , //页面总数
};

	extern	HWND hWnd; //窗口句柄
	extern	WNDCLASS wc;
	extern	LPDIRECTDRAW7 lpDD;//DD对象指针
	extern	LPDIRECTDRAWSURFACE7 DDS[DDSNum];//DD页面指针数组
	extern  LPDIRECTDRAWSURFACE7 lpDDSBack; // 窗口DirectDraw缓冲区
	extern	LPDIRECTDRAWCLIPPER lpClipper;
	
	//extern	LPDIRECTINPUT8 pInput;
	//extern	LPDIRECTINPUTDEVICE8 pDev;
	//extern	char buffer[256];

	extern  Graph graph;
	extern  Mapedit oMapedit;
	
//	extern  DxInput dxinput;
//	extern  SetGame setGame ;
	extern  GameGUI gameGUI ;
	
	extern int SW[DDSNum];
	extern int SH[DDSNum];
	extern	RECT rect;
	
#define IDI_MAIN                        101
#define IDR_MAIN_ACCEL                  103
#define IDD_DIALOG_SAMPLE               106
#define IDB_DIRECTX                     107
#define IDM_EXIT                        1001
#define IDC_RADIO1                      1003
#define IDC_RADIO2                      1004
#define IDC_RADIO3                      1005
#define IDC_EDIT1                       1006
#define IDC_COMBO1                      1007
#define IDM_SHOW_DIALOG                 40001

//函数声明
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
BOOL InitWindow( HINSTANCE hInstance, int nCmdShow ,HWND *hWnd,HACCEL*hAccel);
LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
void MakeRect(int left,int top,int right,int bottom);

#endif