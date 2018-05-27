
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
//����˵��
	LPDIRECTDRAW7 lpDD;//DD����ָ��
	LPDIRECTDRAWSURFACE7 DDS[DDSNum];//DD��ҳ��ָ��
	LPDIRECTDRAWSURFACE7 lpDDSBack; // ����DirectDraw������
	LPDIRECTDRAWCLIPPER lpClipper;
	HWND hWnd;
	RECT rect;
	RECT window_rect;
	HWND g_hWndDlg = NULL;
	HACCEL hAccel;
	INT_PTR CALLBACK SampleDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
//************************************************************
//������WinMain( )
//���ܣ�������ں��������������ڣ�������Ϣѭ��
//************************************************************
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{//���������� ������������ɹ��򷵻�FALSE��ͬʱ�˳�����
	if( !InitWindow(hInstance, nCmdShow,&hWnd,&hAccel) ) return FALSE;
	
		MSG msg;
		const double time_frame = 0.03125;//1����32֡;	
		TimeCount gGameFrameTime;
		gGameFrameTime.InitTime();
		double init_time = gGameFrameTime.GetNowTime();

		timeCount.InitTime(); //��ʱ����ʼ��ʱ��;
		graph.Init();//��Ϸ��ʼ��
		graph.InitClipper();
//		oNetWork.InitNetWork();
//		packetManage.SendPlayerMapPosition();
//		packetManage.RecvPacket();
		// Show the dialog immediately
		g_hWndDlg = CreateDialogW( hInstance,NULL,
			hWnd, (DLGPROC) SampleDlgProc );
		ShowWindow( g_hWndDlg, SW_SHOWNORMAL );

		while(1)//������Ϣѭ��
		{
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//��ѯ�������Ƿ�����Ϣ
			{			
				if(msg.message == WM_QUIT) break;
				//������Ϣ
				TranslateMessage(&msg); 
				DispatchMessage(&msg);
			}
			else
			{	
				if( gGameFrameTime.GetNowTime() - init_time > time_frame )
				{	//������Ϸ;
					graph.GameRefresh(hInstance,nCmdShow);

					init_time = gGameFrameTime.GetNowTime();// - (t - time_frame);
				}
				else
				{
					Sleep(0);//�ų�����Ȩ;
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
//������InitWindow( )
//���ܣ���������
//************************************************************
BOOL InitWindow( HINSTANCE hInstance, int nCmdShow  ,HWND *pHwnd,HACCEL*pHaccel)
{	//���崰�ڷ��
	WNDCLASS wc; 
	wc.style = NULL;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance,IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInstance,IDC_CROSS);
	wc.hbrBackground = NULL;//CreateSolidBrush (RGB(0, 10, 100)); //����ɫ
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"MiniTank";
	RegisterClass(&wc);//ע�ᴰ��
//�������������촰��
	//hWnd = CreateWindow( L"MiniTank",NULL,
	//					 //���ܸı��С�Ĵ���WS_OVERLAPPED|WS_CAPTION|WS_THICKFRAME|WS_MINIMIZEBOX//����ȫ�����ܵĴ���WS_OVERLAPPEDWINDOW,//ȫ��WS_POPUP
	//					 0,0,
	//					 XSCREEN, //�˺���������Ļ���
	//					 YSCREEN, //�˺���������Ļ�߶�
	//					 NULL,NULL,hInstance,NULL );

	//��ȥ�ؼ����߽磬�˵���ռ�õ�ʵ�ʳߴ�
	//DWORD dStyle = WS_OVERLAPPEDWINDOW;//���ڷ��
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
						    960 ,//XSCREEN,//		//��ϴ���ģʽ+���ڷ��+�޸��������ȫ���򴰿�;
							768 ,//YSCREEN,//
						    NULL,	  // handle to parent 
						    NULL,	  // handle to menu
						    hInstance,// instance of this application
						    NULL)))	// extra creation parms
	if( !hWnd ) return FALSE;
	ShowWindow(hWnd,nCmdShow);//��ʾ����SW_SHOWMAXIMIZED;
	UpdateWindow(hWnd);//ˢ�´���;
	*pHwnd   = hWnd;
	*pHaccel = hAccel;
//	cime.InitInstance(hInstance,nCmdShow,hWnd);
	return TRUE;
}

//************************************************************
//������WinProc( )
//���ܣ���������Ϣ
//************************************************************
LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	POINT	mouse;
	GetCursorPos(&mouse);//��ȡmouse��ָ�������ֵ	
//	HIMC        hIMC;
	
	//WS_MOVE
//	RECT r ;//={0,0,XSCREEN,YSCREEN}
	DWORD dStyle = WS_OVERLAPPEDWINDOW;//���ڷ��

	RECT rc ; GetWindowRect(hWnd,&rc);
	double bx = rc.right-rc.left;
	double by = ( rc.bottom-rc.top )+rc.top;
	const long btn_bmp_x_size = 540;
	//double ���� = ;
	double ��ͼ��ť���ŵ�ʵ�ʳߴ� = btn_bmp_x_size/(XSCREEN/bx);

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
		case WM_KEYDOWN://������Ϣ
			switch( wParam )
			{
				case VK_ESCAPE:
					if( graph.��ùؿ���() == GAME_MAP )
					{
						graph.���ùؿ�(1); break;
					}else
					if( graph.��ùؿ���() == MAIN_BTN )
					{
						if( MessageBoxW(hWnd,L"�Ƿ��˳���Ϸ��",L"windows msg",MB_OKCANCEL)!=2 )
						PostMessage(hWnd, WM_CLOSE, 0, 0);//�����ڷ���WM_CLOSE��Ϣ
					}
				break;
				case VK_UP : //ֻ����Ҫ��ͼʱ ��ʱʹ�ñ�ϵ����Ϣ
							oPlayer.SetTankFace ( 1 ) ; //̹�������ƶ�
							oMapedit.SetRollScreenFace( 1 ) ; //��ͼ���¹���
				break;
				case VK_DOWN:
							oPlayer.SetTankFace ( 2 ) ; //̹�������ƶ�
							oMapedit.SetRollScreenFace( 2 ) ; //��ͼ���Ϲ���
				break;
				case VK_LEFT:
							oPlayer.SetTankFace ( 3 ) ; //̹�������ƶ�
							oMapedit.SetRollScreenFace( 3 ) ; //��ͼ���ҹ���
				break;
				case VK_RIGHT:
							oPlayer.SetTankFace ( 4 ) ; //̹�������ƶ�
							oMapedit.SetRollScreenFace( 4 ) ; //��ͼ���ҹ���
				break;
				case '7':
					graph.���ý�ͼ(false);
					dxinput.DXInputInit(); //�û������ʼ��
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
			return 0; //������һ����Ϣ�󷵻�0
		case WM_LBUTTONDOWN : //mouse���
			{	short res = gameGUI.SetMainBtn();
				if (res==MAP_EDIT )
				{
					graph.���ùؿ�( MAP_EDIT ) ;
					//����һЩ��ͼ�༭������;
					oMapedit.ResetMapEdit();
					oMp3.Play();
					Sleep(100);//��ֹ�����ɾ��ͼ;	
					break;
				}else
				if (res==GAME_MAP)
				{
					graph.���ùؿ�( GAME_MAP ) ;
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
				if(graph.��ùؿ���()==MAP_EDIT)
				{	//��ͼ�༭����ť;
					//�û�����ˡ���ȡ��ͼ����ť���ź�;
					if( mouse.x > rc.left + ��ͼ��ť���ŵ�ʵ�ʳߴ� / 4 && 
						mouse.x < rc.left + ��ͼ��ť���ŵ�ʵ�ʳߴ� / 2 && 
						mouse.y > by - 43  && mouse.y < YSCREEN	)  oMapedit.ReadMapFile() ; 

					//�û�����ˡ��洢��ͼ����ť���ź�;
					if ( mouse.x > rc.left + ��ͼ��ť���ŵ�ʵ�ʳߴ� / 2 && 
						mouse.x < rc.left + ��ͼ��ť���ŵ�ʵ�ʳߴ� - ��ͼ��ť���ŵ�ʵ�ʳߴ� / 4	  && 
						mouse.y > by - 43  && mouse.y < YSCREEN	) oMapedit.SaveMapFile() ; 

					//�û�����ˡ������˵�����ť���ź�;
					if ( mouse.x > rc.left + ��ͼ��ť���ŵ�ʵ�ʳߴ� - ��ͼ��ť���ŵ�ʵ�ʳߴ� / 4 && 
						mouse.x < rc.left + ��ͼ��ť���ŵ�ʵ�ʳߴ�		 && 
						mouse.y > by - 43 &&  mouse.y < YSCREEN	)
					{						 
						graph.���ùؿ�( MAIN_BTN ) ; 
						dxinput.DXInputInit(); //�û������ʼ��;
					}
				}
			return 0;
			}
		case WM_LBUTTONUP :
		//	mapEdt.SetbMouseLeftHitMap( false ) ; //�ڵ�ͼ�༭������mouse�ɿ�����ֹͣ��ͼˢ�ӹ���
		//	mapEdt.�ɿ���ͼ ();
			oMapedit.LeftHitTileAreaUp() ;
			oMapedit.LeftHitMapUp();
			if(oMapedit.GetEditSave())
			oMapedit.SaveMouseSelectRectangleToFile();
			return 0;

		case WM_MBUTTONDOWN : //mouse�м�
			//ȡ��ѡ�е���
		//	mapEdt.SetMouseTileToEmpty();
			return 0;

		case WM_RBUTTONDOWN: //mouse�Ҽ�����		
			
		//	mapEdt.����ز��� () ;
		//	mapEdt.ClickMap () ;
			oMapedit.RightHitMapDown ( );
			break;
		case WM_RBUTTONUP: //mouse�Ҽ��ɿ�
			
		//	mapEdt.�ɿ��ز���() ;
		//	mapEdt.�ɿ���ͼ ();
			oMapedit.RightHitMapUp ( );
			oMapedit.RightHitTileArea ();
			break;
		case WM_MOUSEMOVE :
			if( oMapedit.GetbMouseLeftHitMap() )  //�ڵ�ͼ�༭���������mouse�ǰ���״̬��
			{
				oMapedit.LeftHitMapDown() ; 			//�����mouse�켣ˢ��ͼ��
			}
				
			return 0;

		case WM_SIZE :

			return 0;
		case WM_MOVE :
					
			//GetWindowRectʵ���ϻ�õ����������ڣ������ؼ��ͱ߿򣩵����ꡣ�ŵ���Ϸѭ������WM_MOVE��Ϣ��ˢ�´���״̬
			GetWindowRect(hWnd,&window_rect);//��hWnd���ڵ����꿽����r�ṹ��		
			//AdjustWindowRectEx�������㲻ͬ��ʽ���ڵĳߴ磬�ô���������ʱ�ù��Ĳ�������䱾����
		//	AdjustWindowRectEx(&r,dStyle,GetMenu(hWnd)!=NULL,NULL/*GetWindowExStyle(hWnd)*/);
		//	MoveWindow(hWnd,0,0,r.right-r.left,r.bottom-r.top,false);
			return 0;

		case WM_IME_STARTCOMPOSITION://���뷨��Ϣ������ʼ����
			//HIMC hIMC = ::ImmGetContext(hWnd);
			//LONG lSize = ::ImmGetCompositionStringW(hIMC,GCS_COMPSTR,0,0);
			//if(lSize == 0)return 0;
			//char * pString = new char[lSize+1];
			//::ImmGetCompositionStringW(hIMC,GCS_COMPSTR,pString,lSize);
			//pString[lSize] ='\0';
			////�����ַ���...
			//delete []pString;
			//::ImmReleaseContext(hWnd,hIMC);
			//return lSize;
			return 0;
		case WM_IME_ENDCOMPOSITION://���뷨��Ϣ������������

			return 0;
		case WM_IME_COMPOSITION://���뷨��Ϣ�����ı�����״̬
			//switch(message) 
			//{

			//}
			return 0;
		case WM_CLOSE: //׼���˳�
			DestroyWindow( hWnd ); //�ͷŴ���
			return 0;
		case WM_DESTROY: //������ڱ����ͷš�
			//hIMC = (HIMC)GetWindowLong(hWnd,0);
			//hIMC = ImmAssociateContext(hWnd,hIMC);
			//ImmDestroyContext(hIMC);
			PostQuitMessage( 0 ); //�����ڷ���WM_QUIT��Ϣ
			return 0;

	}
//	cime.WndProc(hWnd,message,wParam,lParam);
//����ȱʡ��Ϣ�������
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