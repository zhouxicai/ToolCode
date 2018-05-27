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

//��ֹ������˰�ddraw.lib��dxguid.lib���빤��

#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "Winmm.lib")
//	#include "netbase/NetManager.h"



//˵��
enum	eBitmap
{		
	SPrimary  ,	//��ҳ��
	SBuffer   ,	//����ҳ��
	���˵�	  ,	//���˵���ť
	GameBack  ,	//��Ϸ����ͼ
	SXbmp     ,	//mouseͼ��
	STile     ,	//��ͼ��Ƭ
	MapBtn    ,	//��ͼ�༭����ť
	MM2TankB  ,	//ս����Ƭ
	BaseBulle ,	//�����ӵ�
	����	  ,
	BackMap	  ,	//���ͼ
	MicroMap  , //С��ͼ
	MicroMapZoom  , //�����ž�ȷС��ͼ
	BigMap	  , //���ͼ
	DDSNum    , //ҳ������
};

	extern	HWND hWnd; //���ھ��
	extern	WNDCLASS wc;
	extern	LPDIRECTDRAW7 lpDD;//DD����ָ��
	extern	LPDIRECTDRAWSURFACE7 DDS[DDSNum];//DDҳ��ָ������
	extern  LPDIRECTDRAWSURFACE7 lpDDSBack; // ����DirectDraw������
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

//��������
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
BOOL InitWindow( HINSTANCE hInstance, int nCmdShow ,HWND *hWnd,HACCEL*hAccel);
LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
void MakeRect(int left,int top,int right,int bottom);

#endif