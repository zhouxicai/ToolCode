
#include "main.h"
#include "SpecialEfficiency.h"
#include"IME.h"
//#include "netbase/NetManager.h"
#include "TimeCount.h"
#include "DXInput.h"
#include "Player.h"
#include "DirectXAudio.h"
#include "Core_Sound.h"
#include "NetWork.h"
#include "NetWork\PacketManage.h"
//变量说明
	LPDIRECTDRAW7 lpDD;//DD对象指针
	LPDIRECTDRAWSURFACE7 DDS[DDSNum];//DD主页面指针
	LPDIRECTDRAWSURFACE7 lpDDSBack; // 窗口DirectDraw缓冲区
	LPDIRECTDRAWCLIPPER lpClipper;
	HWND hWnd;
	RECT rect;
	RECT window_rect;
	HWND g_hWndDlg = NULL;
	HACCEL hAccel;
	INT_PTR CALLBACK SampleDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
//************************************************************
//函数：WinMain( )
//功能：程序入口函数。创建主窗口，处理消息循环
//************************************************************
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{//创建主窗口 ，如果创建不成功则返回FALSE并同时退出程序
	if( !InitWindow(hInstance, nCmdShow,&hWnd,&hAccel) ) return FALSE;
	
		MSG msg;
		const double time_frame = 0.03125;//1秒钟32帧;	
		TimeCount gGameFrameTime;
		gGameFrameTime.InitTime();
		double init_time = gGameFrameTime.GetNowTime();

		timeCount.InitTime(); //计时器初始化时间;
		graph.Init();//游戏初始化
		graph.InitClipper();
//		oNetWork.InitNetWork();
//		packetManage.SendPlayerMapPosition();
//		packetManage.RecvPacket();
		// Show the dialog immediately
		g_hWndDlg = CreateDialogW( hInstance,NULL,
			hWnd, (DLGPROC) SampleDlgProc );
		ShowWindow( g_hWndDlg, SW_SHOWNORMAL );

		while(1)//进入消息循环
		{
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//查询队列中是否有消息
			{			
				if(msg.message == WM_QUIT) break;
				//处理消息
				TranslateMessage(&msg); 
				DispatchMessage(&msg);
			}
			else
			{	
				if( gGameFrameTime.GetNowTime() - init_time > time_frame )
				{	//更新游戏;
					graph.GameRefresh(hInstance,nCmdShow);

					init_time = gGameFrameTime.GetNowTime();// - (t - time_frame);
				}
				else
				{
					Sleep(0);//放出控制权;
				}
				
				if( g_hWndDlg == NULL || !IsDialogMessage( g_hWndDlg, &msg ) )
				{
					if( 0 == TranslateAccelerator( hWnd, hAccel, &msg ) )
					{
						TranslateMessage( &msg ); 
						DispatchMessage( &msg );
					}
				}
			}
		}
	return msg.wParam;
}

//************************************************************
//函数：InitWindow( )
//功能：创建窗口
//************************************************************
BOOL InitWindow( HINSTANCE hInstance, int nCmdShow  ,HWND *pHwnd,HACCEL*pHaccel)
{	//定义窗口风格：
	WNDCLASS wc; 
	wc.style = NULL;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance,IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInstance,IDC_CROSS);
	wc.hbrBackground = NULL;//CreateSolidBrush (RGB(0, 10, 100)); //背景色
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"MiniTank";
	RegisterClass(&wc);//注册窗口
//按所给参数创造窗口
	//hWnd = CreateWindow( L"MiniTank",NULL,
	//					 //不能改变大小的窗口WS_OVERLAPPED|WS_CAPTION|WS_THICKFRAME|WS_MINIMIZEBOX//带有全部功能的窗口WS_OVERLAPPEDWINDOW,//全屏WS_POPUP
	//					 0,0,
	//					 XSCREEN, //此函数返回屏幕宽度
	//					 YSCREEN, //此函数返回屏幕高度
	//					 NULL,NULL,hInstance,NULL );

	//减去控件，边界，菜单所占用的实际尺寸
	//DWORD dStyle = WS_OVERLAPPEDWINDOW;//窗口风格
	//RECT rect ={0,0,XSCREEN,YSCREEN};
	//SetRect(&rect,0,0,900,563);

	//window_rect.left    = 250;
	//window_rect.top     = 100;
	//window_rect.right   = 900;
	//window_rect.bottom  = 600;
	//::AdjustWindowRectEx(&rect,dStyle ,/*GetMenu(hWnd)!=*/NULL,NULL);
	//::MoveWindow(hWnd,CW_USEDEFAULT,CW_USEDEFAULT,
	//				rect.right - rect.left,
	//				rect.bottom - rect.top,false);
HACCEL hAccel = LoadAccelerators( hInstance, MAKEINTRESOURCE(IDR_MAIN_ACCEL) );
	// create the window
if (!(hWnd = CreateWindowExW(WS_EX_LEFT ,                // extended style
                            L"MiniTank",          // class
						    L"Star home - beta 2.16", // title
							WS_OVERLAPPEDWINDOW,// WS_POPUP,//
					 	    0  ,0   ,	// initial x,y							  
						    960 ,//XSCREEN,//		//配合窗口模式+窗口风格+修改这里，控制全屏或窗口;
							768 ,//YSCREEN,//
						    NULL,	  // handle to parent 
						    NULL,	  // handle to menu
						    hInstance,// instance of this application
						    NULL)))	// extra creation parms
	if( !hWnd ) return FALSE;
	ShowWindow(hWnd,nCmdShow);//显示窗口SW_SHOWMAXIMIZED;
	UpdateWindow(hWnd);//刷新窗口;
	*pHwnd   = hWnd;
	*pHaccel = hAccel;
//	cime.InitInstance(hInstance,nCmdShow,hWnd);
	return TRUE;
}

//************************************************************
//函数：WinProc( )
//功能：处理窗口消息
//************************************************************
LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	POINT	mouse;
	GetCursorPos(&mouse);//获取mouse所指向的坐标值	
//	HIMC        hIMC;
	
	//WS_MOVE
//	RECT r ;//={0,0,XSCREEN,YSCREEN}
	DWORD dStyle = WS_OVERLAPPEDWINDOW;//窗口风格

	RECT rc ; GetWindowRect(hWnd,&rc);
	double bx = rc.right-rc.left;
	double by = ( rc.bottom-rc.top )+rc.top;
	const long btn_bmp_x_size = 540;
	//double 比率 = ;
	double 地图按钮缩放的实际尺寸 = btn_bmp_x_size/(XSCREEN/bx);

	switch( message )
	{
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDM_EXIT:
			// Received key/menu command to exit app
			PostMessage( hWnd, WM_CLOSE, 0, 0 );
			return 0L;

		case IDM_SHOW_DIALOG:
			{
				HINSTANCE hInst;
#ifdef _WIN64
				hInst = (HINSTANCE) GetWindowLongPtr( hWnd, GWLP_HINSTANCE );
#else
				hInst = (HINSTANCE) GetWindowLong( hWnd, GWL_HINSTANCE );
#endif
				g_hWndDlg = CreateDialog( hInst, MAKEINTRESOURCE(IDD_DIALOG_SAMPLE),
					hWnd, (DLGPROC) SampleDlgProc );
				ShowWindow( g_hWndDlg, SW_SHOWNORMAL );
			}
			break;
		}
		break; // Continue with default processing
		case WM_KEYDOWN://击键消息
			switch( wParam )
			{
				case VK_ESCAPE:
					if( graph.获得关卡数() == GAME_MAP )
					{
						graph.设置关卡(1); break;
					}else
					if( graph.获得关卡数() == MAIN_BTN )
					{
						if( MessageBoxW(hWnd,L"是否退出游戏？",L"windows msg",MB_OKCANCEL)!=2 )
						PostMessage(hWnd, WM_CLOSE, 0, 0);//给窗口发送WM_CLOSE消息
					}
				break;
				case VK_UP : //只在需要截图时 临时使用本系列消息
							oPlayer.SetTankFace ( 1 ) ; //坦克向上移动
							oMapedit.SetRollScreenFace( 1 ) ; //地图向下滚动
				break;
				case VK_DOWN:
							oPlayer.SetTankFace ( 2 ) ; //坦克向下移动
							oMapedit.SetRollScreenFace( 2 ) ; //地图向上滚动
				break;
				case VK_LEFT:
							oPlayer.SetTankFace ( 3 ) ; //坦克向左移动
							oMapedit.SetRollScreenFace( 3 ) ; //地图向右滚动
				break;
				case VK_RIGHT:
							oPlayer.SetTankFace ( 4 ) ; //坦克向左移动
							oMapedit.SetRollScreenFace( 4 ) ; //地图向右滚动
				break;
				case '7':
					graph.设置截图(false);
					dxinput.DXInputInit(); //用户输入初始化
				break;
				case VK_SPACE:
					oPlayer.BeginShoot();	
				break;
				case 'R':
					if( cse.GetRainBool() == true)
						cse.RainSwitch(false);
					else
						cse.RainSwitch(true);
				break;
				case 'S':
					if( cse.GetSnowBool() == true)
						cse.SnowSwitch(false);
					else
						cse.SnowSwitch(true);
				break;
			}
			return 0; //处理完一个消息后返回0
		case WM_LBUTTONDOWN : //mouse左键
			{	short res = gameGUI.SetMainBtn();
				if (res==MAP_EDIT )
				{
					graph.设置关卡( MAP_EDIT ) ;
					//重置一些地图编辑器设置;
					oMapedit.ResetMapEdit();
					oMp3.Play();
					Sleep(100);//防止鼠标误删地图;	
					break;
				}else
				if (res==GAME_MAP)
				{
					graph.设置关卡( GAME_MAP ) ;
					oMapedit.LoadDefaultMap();
					oMapedit.InitBigMap();
					oMapedit.SetMicroMap();
					oMusicChannel.Load("audios\\rain03.wav");
					oDirectXAudio.PlayMicMidiWav();
					break;
				}
				oMapedit.LeftHitTileArea () ;  
			//	mapEdt.ClickMap () ;
				oMapedit.LeftHitMapDown();
				if(graph.获得关卡数()==MAP_EDIT)
				{	//地图编辑器按钮;
					//用户点击了“读取地图”按钮的信号;
					if( mouse.x > rc.left + 地图按钮缩放的实际尺寸 / 4 && 
						mouse.x < rc.left + 地图按钮缩放的实际尺寸 / 2 && 
						mouse.y > by - 43  && mouse.y < YSCREEN	)  oMapedit.ReadMapFile() ; 

					//用户点击了“存储地图”按钮的信号;
					if ( mouse.x > rc.left + 地图按钮缩放的实际尺寸 / 2 && 
						mouse.x < rc.left + 地图按钮缩放的实际尺寸 - 地图按钮缩放的实际尺寸 / 4	  && 
						mouse.y > by - 43  && mouse.y < YSCREEN	) oMapedit.SaveMapFile() ; 

					//用户点击了“回主菜单”按钮的信号;
					if ( mouse.x > rc.left + 地图按钮缩放的实际尺寸 - 地图按钮缩放的实际尺寸 / 4 && 
						mouse.x < rc.left + 地图按钮缩放的实际尺寸		 && 
						mouse.y > by - 43 &&  mouse.y < YSCREEN	)
					{						 
						graph.设置关卡( MAIN_BTN ) ; 
						dxinput.DXInputInit(); //用户输入初始化;
					}
				}
			return 0;
			}
		case WM_LBUTTONUP :
		//	mapEdt.SetbMouseLeftHitMap( false ) ; //在地图编辑器区，mouse松开，则停止地图刷子功能
		//	mapEdt.松开地图 ();
			oMapedit.LeftHitTileAreaUp() ;
			oMapedit.LeftHitMapUp();
			if(oMapedit.GetEditSave())
			oMapedit.SaveMouseSelectRectangleToFile();
			return 0;

		case WM_MBUTTONDOWN : //mouse中间
			//取消选中的帖
		//	mapEdt.SetMouseTileToEmpty();
			return 0;

		case WM_RBUTTONDOWN: //mouse右键按下		
			
		//	mapEdt.点击素材区 () ;
		//	mapEdt.ClickMap () ;
			oMapedit.RightHitMapDown ( );
			break;
		case WM_RBUTTONUP: //mouse右键松开
			
		//	mapEdt.松开素材区() ;
		//	mapEdt.松开地图 ();
			oMapedit.RightHitMapUp ( );
			oMapedit.RightHitTileArea ();
			break;
		case WM_MOUSEMOVE :
			if( oMapedit.GetbMouseLeftHitMap() )  //在地图编辑器区，如果mouse是按下状态，
			{
				oMapedit.LeftHitMapDown() ; 			//则根据mouse轨迹刷地图。
			}
				
			return 0;

		case WM_SIZE :

			return 0;
		case WM_MOVE :
					
			//GetWindowRect实际上获得的是整个窗口（包括控件和边框）的坐标。放到游戏循环或者WM_MOVE消息中刷新窗口状态
			GetWindowRect(hWnd,&window_rect);//把hWnd窗口的坐标拷贝到r结构中		
			//AdjustWindowRectEx函数计算不同样式窗口的尺寸，用创建主窗口时用过的参数，填充本函数
		//	AdjustWindowRectEx(&r,dStyle,GetMenu(hWnd)!=NULL,NULL/*GetWindowExStyle(hWnd)*/);
		//	MoveWindow(hWnd,0,0,r.right-r.left,r.bottom-r.top,false);
			return 0;

		case WM_IME_STARTCOMPOSITION://输入法消息处理，开始组字
			//HIMC hIMC = ::ImmGetContext(hWnd);
			//LONG lSize = ::ImmGetCompositionStringW(hIMC,GCS_COMPSTR,0,0);
			//if(lSize == 0)return 0;
			//char * pString = new char[lSize+1];
			//::ImmGetCompositionStringW(hIMC,GCS_COMPSTR,pString,lSize);
			//pString[lSize] ='\0';
			////处理字符串...
			//delete []pString;
			//::ImmReleaseContext(hWnd,hIMC);
			//return lSize;
			return 0;
		case WM_IME_ENDCOMPOSITION://输入法消息处理，结束组字

			return 0;
		case WM_IME_COMPOSITION://输入法消息处理，改变组字状态
			//switch(message) 
			//{

			//}
			return 0;
		case WM_CLOSE: //准备退出
			DestroyWindow( hWnd ); //释放窗口
			return 0;
		case WM_DESTROY: //如果窗口被人释放…
			//hIMC = (HIMC)GetWindowLong(hWnd,0);
			//hIMC = ImmAssociateContext(hWnd,hIMC);
			//ImmDestroyContext(hIMC);
			PostQuitMessage( 0 ); //给窗口发送WM_QUIT消息
			return 0;

	}
//	cime.WndProc(hWnd,message,wParam,lParam);
//调用缺省消息处理过程
	return DefWindowProc(hWnd, message, wParam, lParam); 
}

void MakeRect( int left , int top , int right , int bottom )
{
	rect.left    =  left   ;
	rect.right   =  right  ;
	rect.top     =  top    ;
	rect.bottom  =  bottom ; 
}


INT_PTR CALLBACK SampleDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static WCHAR* pszCombo[] = {L"One",L"Two",L"Three",L"Four",L"Five",L"Six"};

	switch (msg)
	{
	case WM_INITDIALOG:
		{
			for( int i = 0; i < 6; i++ )
				SendDlgItemMessageW( hDlg, IDC_COMBO1, CB_ADDSTRING, 
				0, (LPARAM) pszCombo[i] );

			SendDlgItemMessageW( hDlg, IDC_COMBO1, CB_SETCURSEL, 0, 0 );
			CheckDlgButton( hDlg, IDC_RADIO1, BST_CHECKED );
		}
		return TRUE;

	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDCANCEL:
		case IDOK:
			EndDialog( hDlg, TRUE );
			return TRUE;
		}
		break;

	case WM_MOVE:
		// The window is moving around, so re-draw the backbuffer
	//	DisplayFrame();
		break;

	case WM_DESTROY:
		g_hWndDlg = NULL;
		break;
	}

	return FALSE;
}