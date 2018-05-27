#include "main.h"
#include "IME.h"
#include "ObjectPool.h"
#include "DirectXAudio.h"
#include "DXInput.h"
#include "Core_Sound.h"
Graph graph;
int SW[DDSNum];
int SH[DDSNum];
Graph::Graph()
{
	�ؿ� = 1 ;
	��ͼ = true;
	IsWindowed = false;
	//��ʼ10���ӵ�
	//CGun * bulle = new CGun[10];
}
void Graph::���ùؿ�(int �ؿ���)
{
	�ؿ�=�ؿ���;
	/*  if �ؿ�=1 ��Ϸ���˵�
		if �ؿ�=2 ��ͼ�༭��
		if �ؿ�=3 ��ʼ��Ϸ   */
}

bool Graph::Init()
{
	DDGameInitWindowed(hWnd);
	//CreateFullScreenSurfaces( ) ;


	AddPictrue();
	dxinput.DXInputInit(); //�û������ʼ��

	oDirectXAudio.LoadMicMidiWav(L"audios/TMEMO01.mid",0);
	oMp3.Init();
	oMp3.Render("audios/TheDawn.mp3");

	return TRUE;
}

inline bool Graph::AddPictrue()
{	//�����󻺳�ҳ

	//����X��־,ddsd��DDҳ������
	memset( &ddsd, 0, sizeof(ddsd) );
	ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;//����ҳ��,�ѳ�����ҳ���������ҳ������ڴ���;

	DDSetColorKey(DDS[MicroMap],RGB(0,0,0));//���ú�ɫΪ͸��ɫ
	DDSetColorKey(DDS[MicroMapZoom],RGB(0,0,0));//���ú�ɫΪ͸��ɫ
//	DDSetColorKey(DDS[BigMap],RGB(255,0,255));//������ɫΪ͸��ɫ
	ddsd.dwHeight = YSCREEN+TILE_HIGH+TILE_HIGH ;//��һȦ�����ڹ����Ż�;
	ddsd.dwWidth  = XSCREEN+TILE_WIDE+TILE_WIDE ;
	if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[BigMap],NULL))return FALSE;//����ҳ��

	ddsd.dwHeight = 30 ;
	ddsd.dwWidth  = 30 ;
	if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[SXbmp],NULL))return FALSE;//����ҳ��
	DDReLoadBitmap(DDS[SXbmp],L"bmp/SXbmp.bmp");
	DDSetColorKey(DDS[SXbmp],RGB(0,255,0));//������ɫΪ͸��ɫ
		//���ر���ͼ
		ddsd.dwHeight = YSCREEN ;
		ddsd.dwWidth  = XSCREEN ;
		if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[GameBack],NULL))return FALSE;//����ҳ��
		DDReLoadBitmap(DDS[GameBack],L"bmp/star.bmp");	
	//���ؿ�ʼҳ�水ť
	ddsd.dwHeight = 100 ;
	ddsd.dwWidth  = 180 ;
	if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[���˵�],NULL))return FALSE;//����ҳ��
	DDReLoadBitmap(DDS[���˵�],L"bmp/starbtn.bmp");
	DDSetColorKey(DDS[���˵�],RGB(0,0,0));//���ú�ɫΪ͸��ɫ
		//���ص�ͼ��Ƭ
		ddsd.dwHeight = 704 ;
		ddsd.dwWidth  = 256 ;
		if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[STile],NULL))return FALSE;//����ҳ��
		DDReLoadBitmap(DDS[STile],L"bmp/MapT2.bmp");//14��,8�У�32*32��256*448	
		DDSetColorKey(DDS[STile],RGB(255,0,255));//������ɫΪ͸��ɫ
	//���ص�ͼ�༭����ť
	ddsd.dwHeight = 86  ;
	ddsd.dwWidth  = 540 ;
	if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[MapBtn],NULL))return FALSE;//����ҳ��
	DDReLoadBitmap(DDS[MapBtn],L"bmp/MapBtn.bmp");
		//����ս����Ƭ
		ddsd.dwHeight = 128 ;
		ddsd.dwWidth  = 64 ;
		if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[MM2TankB],NULL))return FALSE;//����ҳ��
		DDReLoadBitmap(DDS[MM2TankB],L"bmp/Tank01.bmp");
		DDSetColorKey(DDS[MM2TankB],RGB(255,0,255));//������ɫΪ͸��ɫ
	//�����ӵ�λͼ
	ddsd.dwHeight = 16 ;
	ddsd.dwWidth  = 16 ;
	if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[BaseBulle],NULL))return FALSE;//����ҳ��
	DDReLoadBitmap(DDS[BaseBulle],L"bmp/Bulle.bmp");
	DDSetColorKey(DDS[BaseBulle],RGB(0,0,255));//����͸��ɫ
	//�����������ҳ����ڴ˼�������	
		//���ػ�����Ƭ
		ddsd.dwHeight = 256 ;
		ddsd.dwWidth  = 256 ;
		if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[����],NULL))return FALSE;//����ҳ��
		DDReLoadBitmap(DDS[����],L"bmp/����.bmp");
		DDSetColorKey(DDS[����],RGB(255,0,255));//������ɫΪ͸��ɫ
	
	//��ʼ��������ͼ
	//SW[BackMap] = 100*32;	SH[BackMap] = 100*32;
	//ddsd.dwHeight = SW[BackMap] ;
	//ddsd.dwWidth  = SH[BackMap] ;
	//if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[BackMap],NULL))return FALSE;//����ҳ��
	//mapEdt.SetShowAllMapLayer(true);
	//mapEdt.ReadMapFile ( ) ;
	//mapEdt.ShowMap ( 32 , 32 , 0 , 0 ) ;
	return TRUE;
}

 BOOL Graph::CreateFullScreenSurfaces()
 {	//��ʼ��DirectDraw---------------------------------------------------
		//����DD���� 
	if(DirectDrawCreateEx(NULL,(void **)&lpDD,IID_IDirectDraw7,NULL)!=DD_OK)return FALSE;
		//���ÿ��Ƽ���ȡ�ö�ռ��ȫ��ģʽ
	if(lpDD->SetCooperativeLevel(hWnd,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN)!=DD_OK )return FALSE;
		//������ʾģʽ
	if(lpDD->SetDisplayMode (XSCREEN,YSCREEN,32,0,DDSDM_STANDARDVGAMODE)!=DD_OK)return FALSE;
	//��ʼ����ҳ��-------------------------------------------------------
		//������ҳ��
		memset(&ddsd,0,sizeof(DDSURFACEDESC2));//�����ҳ������
		//�����ҳ������
		ddsd.dwSize =sizeof(ddsd);
		ddsd.dwFlags =DDSD_CAPS|DDSD_BACKBUFFERCOUNT;//�к�̨����
		ddsd.ddsCaps .dwCaps =DDSCAPS_PRIMARYSURFACE|DDSCAPS_FLIP|DDSCAPS_COMPLEX;//��ҳ�棬�л�ҳ�����к�̨����
		ddsd.dwBackBufferCount=1;//һ����̨����
		//������ҳ��
	if(lpDD->CreateSurface(&ddsd,&DDS[SPrimary],NULL)!=DD_OK)return FALSE;
		ddsd.ddsCaps .dwCaps =DDSCAPS_BACKBUFFER;//���Ǻ�̨����
		//��ȡ��̨�������ָ�룬GetAttachedSurface�õ�һ��ָ�򻺳��ָ��
	if(DD_OK!=DDS[SPrimary]->GetAttachedSurface (&ddsd.ddsCaps ,&DDS[SBuffer]))return FALSE;
	

	// ���������󻺳�ҳ��С��ͼ����ҳ��
	HRESULT
	ddrval = lpDD->CreateSurface( &ddsd, &DDS[SBuffer], NULL );
	if( ddrval != DD_OK )
	{
		lpClipper-> Release();
		DDS[SPrimary]->Release();
		lpDD->Release();
		return(false);
	}
	ddrval = lpDD->CreateSurface( &ddsd, &DDS[MicroMap], NULL );
	if( ddrval != DD_OK )
	{
		lpClipper-> Release();
		DDS[SPrimary]->Release();
		lpDD->Release();
		return(false);
	}
	RECT client; 
	GetWindowRect(hWnd, &client);
	if (lpDD->CreateClipper(0, &lpClipper, NULL) == DD_OK)
		lpClipper->SetHWnd(0, hWnd);
	lpDD->FlipToGDISurface();

	
		//��䱳��
		DDBLTFX ddBltFx;
		ddBltFx.dwSize =sizeof(DDBLTFX);//ddBltFx.dwFillPixel=0;
		ddBltFx.dwFillColor =RGB(0,0,0);//��ɫ����
	DDS[SPrimary]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	DDS[SBuffer]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
//	DDS[MicroMap]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
		
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;//��������ҳ��
		
		return true ;
 }


// ����ģʽ��ʼ��DirectDraw�ĺ���
bool Graph::DDGameInitWindowed(THIS_ HWND hwnd)
{
//    DDSURFACEDESC ddsd;
//    DDSCAPS ddscaps;
    HRESULT ddrval;

    IsWindowed = true;

   /*
    * ����DirectDraw������
    */

  	//����DD������ 
	if(DirectDrawCreateEx(NULL,(void **)&lpDD,IID_IDirectDraw7,NULL)!=DD_OK)return FALSE;
	//����DD���Ƽ�����DDSCL_NORMAL��ʾ����Ҫ��GDI����
	if(lpDD->SetCooperativeLevel(hwnd,DDSCL_NORMAL )!=DD_OK ){lpDD->Release();return FALSE;}
	//������ʾģʽ
	if(lpDD->SetDisplayMode (XSCREEN,YSCREEN,32,0,DDSDM_STANDARDVGAMODE)!=DD_OK)return FALSE;

	//	RECT  rcWork;
	//	RECT  rc;
	////	DWORD dwStyle;	

	////	SetWindowLong( hWnd, GWL_STYLE, dwStyle );
	//	// ���óߴ�
	//	SetRect( &rc, 0, 0, XSCREEN, YSCREEN );
	//	SetWindowPos( hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
 //                 SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE );

	//	SetWindowPos( hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,
 //                 SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE );
	//	// ��֤���ᵽ������
	//	SystemParametersInfo( SPI_GETWORKAREA, 0, &rcWork, 0 );
	//	GetWindowRect( hWnd, &rc );
 //   
	//	if( rc.left < rcWork.left ) rc.left = rcWork.left;
	//	    
	//	if( rc.top  < rcWork.top )  rc.top  = rcWork.top;
	//	    
	//	SetWindowPos( hWnd, NULL, rc.left, rc.top, 0, 0,
	//	              SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
	
	// �����ҳ�治�ǿɷ�ҳ��ҳ��
    memset( &ddsd, 0, sizeof(ddsd) );
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE; 
	ddsd.dwHeight = YSCREEN ;
	ddsd.dwWidth  = XSCREEN ;
	if(lpDD->CreateSurface(&ddsd,&DDS[SPrimary],NULL)!=DD_OK){lpDD->Release();return FALSE;}
	RECT client; 
	GetWindowRect(hWnd, &client);


    // ����һ�����а屣֤��������������
    ddrval = lpDD->CreateClipper( 0, &lpClipper, NULL );
    if( ddrval != DD_OK )
    {
        DDS[SPrimary]->Release();
        lpDD->Release();
        return(false);
    }

    // �Ѵ��ھ�����ø����а�͸�����һ���봰�����ʵĲ��п�
    ddrval = lpClipper->SetHWnd( 0, hWnd );
    if( ddrval != DD_OK )
    {
        lpClipper-> Release();
        DDS[SPrimary]->Release();
        lpDD->Release();
        return(false);
    }

    // �Ѳ��а帽����ҳ��
    ddrval = DDS[SPrimary]->SetClipper( lpClipper );
    if( ddrval != DD_OK )
    {
        lpClipper-> Release();
        DDS[SPrimary]->Release();
        lpDD->Release();
        return(false);
    }

    memset( &ddsd, 0, sizeof(ddsd) );
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth = XSCREEN;
    ddsd.dwHeight = YSCREEN;

    // ���������󻺳�ҳ��С��ͼ����ҳ��
    ddrval = lpDD->CreateSurface( &ddsd, &DDS[SBuffer], NULL );
    if( ddrval != DD_OK )
    {
        lpClipper-> Release();
        DDS[SPrimary]->Release();
        lpDD->Release();
        return(false);
    }

	ddrval = lpDD->CreateSurface( &ddsd, &DDS[MicroMap], NULL );
	if( ddrval != DD_OK )
	{
		lpClipper-> Release();
		DDS[SPrimary]->Release();
		lpDD->Release();
		return(false);
	}

	ddsd.dwWidth = 3200;
	ddsd.dwHeight = 3200;
	ddrval = lpDD->CreateSurface( &ddsd, &DDS[MicroMapZoom], NULL );
	if( ddrval != DD_OK )
	{
		lpClipper-> Release();
		DDS[SPrimary]->Release();
		lpDD->Release();
		return(false);
	}

    return(true);
}
HRESULT Graph::InitClipper()
{
	LPDIRECTDRAWCLIPPER pClipper;
	HRESULT hr;

	// Create a clipper when using GDI to draw on the primary surface 
	if( FAILED( hr = lpDD->CreateClipper( 0, &pClipper, NULL ) ) )
		return hr;

	pClipper->SetHWnd( 0, hWnd );

	if( FAILED( hr = DDS[SPrimary]->SetClipper( pClipper ) ) )
		return hr;

	// We can release the clipper now since g_pDDSPrimary 
	// now maintains a ref count on the clipper
	 pClipper->Release();

	return S_OK;
}
 BOOL Graph::CreateWindowedSurfaces( )
 {
  	//����DD���� 
	if(DirectDrawCreateEx(NULL,(void **)&lpDD,IID_IDirectDraw7,NULL)!=DD_OK)return FALSE;
	//����DD���Ƽ�
	if(lpDD->SetCooperativeLevel(hWnd,DDSCL_NORMAL )!=DD_OK )return FALSE;//DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN
	//������ʾģʽ�����ϵͳ�ֱ���GetSystemMetrics()
	if(lpDD->SetDisplayMode (XSCREEN,YSCREEN,32,0,DDSDM_STANDARDVGAMODE)!=DD_OK)return FALSE;
	
		RECT  rcWork;
		RECT  rc;
	//	DWORD dwStyle;	

	//	SetWindowLong( hWnd, GWL_STYLE, dwStyle );
		// ���óߴ�
		SetRect( &rc, 0, 0, XSCREEN, YSCREEN );
		SetWindowPos( hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
                  SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE );

		SetWindowPos( hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,
                  SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE );
		// ��֤���ᵽ������
		SystemParametersInfo( SPI_GETWORKAREA, 0, &rcWork, 0 );
		GetWindowRect( hWnd, &rc );
    
		if( rc.left < rcWork.left ) rc.left = rcWork.left;
		    
		if( rc.top  < rcWork.top )  rc.top  = rcWork.top;
		    
		SetWindowPos( hWnd, NULL, rc.left, rc.top, 0, 0,
		              SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );

		//������ҳ��
		memset(&ddsd,0,sizeof(DDSURFACEDESC2));//�����ҳ������
		//���ҳ������
		ddsd.dwSize =sizeof(ddsd);
		ddsd.dwFlags =DDSD_CAPS;//�޺�̨����
		ddsd.dwWidth = XSCREEN;
		ddsd.dwHeight = YSCREEN;
		ddsd.ddsCaps .dwCaps = DDSCAPS_PRIMARYSURFACE;//ȥ����̨����ͻ�ҳDDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		ddsd.dwBackBufferCount=1;//һ����̨����
	if(lpDD->CreateSurface(&ddsd,&DDS[SPrimary],NULL)!=DD_OK)return FALSE;//������ҳ��

	//	ddsd.ddsCaps .dwCaps =DDSCAPS_BACKBUFFER;//���Ǻ�̨����//������̨����	
	//if(DD_OK!=DDS[SPrimary]->GetAttachedSurface (&ddsd.ddsCaps ,&DDS[SPrimary]))return FALSE;
		
	    // ����������������������
		if (lpDD->CreateClipper( 0, &lpClipper, NULL ) != DD_OK )goto fail;
		if ( lpClipper->SetHWnd( 0, hWnd ) != DD_OK )goto fail;
		//if ( lpFrontBuffer->SetClipper( lpClipper ) != DD_OK )
		// �ͷż�������������ʹ��SetClipper����ʱ�����Զ��Ļ�ò�����
		//if ( lpClipper->Release() != DD_OK )goto fail;
		fail:
		    return FALSE;

		//��䱳��
		//	DDBLTFX ddBltFx;
		//	ddBltFx.dwSize =sizeof(DDBLTFX);//ddBltFx.dwFillPixel=0;
		//	ddBltFx.dwFillColor =RGB(0,0,0);//��ɫ����
		//DDS[SPrimary]->Blt (NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
		//DDS[SBuffer]->Blt (NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
		//ddsd.dwSize =sizeof(ddsd);
		//ddsd.dwFlags =DDSD_CAPS;
		//ddsd.ddsCaps.dwCaps =DDSCAPS_OFFSCREENPLAIN;//��������ҳ��
 }
//��Ϸ����ˢ��
 void Graph::GameRefresh(HINSTANCE hInstance, int nCmdShow)
{	
		//ˢ��ͼ��ʱ��䱳��ɫ
	//	MakeRect(0,0,XSCREEN,YSCREEN);//�������
		DDBLTFX ddBltFx;
		ddBltFx.dwSize =sizeof(DDBLTFX);
		ddBltFx.dwFillPixel=0;//��䱳��ɫΪ��ɫ	
	//	ddBltFx.dwFillColor = RGB(100,100,0);//ָ�����ɫ	
	DDS[SBuffer]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	//DDS[SBuffer]->BltFast ( 500 , 300 , DDS[BaseBulle] , NULL ,
	//						DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
	if( �ؿ� == MAIN_BTN ) 
	{
		////���ô���Ϊ�Զ����	
		//WINDOWPLACEMENT wt;	
		//wt.rcNormalPosition.top = 50;
		//wt.rcNormalPosition.left = 100;
		//wt.rcNormalPosition.right = 960;
		//wt.rcNormalPosition.bottom = 540;
		//wt.length =sizeof(WINDOWPLACEMENT);
		//wt.showCmd = SW_SHOWNORMAL;//��� SW_SHOWMAXIMIZED ��С�� SW_SHOWMINIMIZED. ��ͨ SW_SHOWNORMAL.  
		//SetWindowPlacement(hWnd,&wt);
		gameGUI.MainBtn() ; //������Ϸ���˵�
		oMapedit.SetShowAllMapLayer(true);
		
		oDirectXAudio.StopMicMidiWav();
		oMp3.Stop();

		HDC hdc(NULL);
	  if (DDS[SBuffer]->GetDC(&hdc) == DD_OK)
	  { 
		SetBkMode(hdc,TRANSPARENT);//���ñ���ģʽ
		SetTextColor(hdc, RGB(230, 230, 230));
		SetTextCharacterExtra (hdc, 1) ;//�����м��
		
		//SetMapMode 	(hdc, MM_ANISOTROPIC) ;
		//SetWindowExtEx 	 (hdc, 1440, 1440, NULL) ;
		//SetViewportExtEx (hdc,	GetDeviceCaps (hdc, LOGPIXELSX),
  //                   	GetDeviceCaps (hdc, LOGPIXELSY), NULL) ;


		static LOGFONT   lf; 
		memset(&lf,   0,   sizeof(LOGFONT)); 
		lf.lfHeight   =   18;//��������߶�
		lf.lfWidth	  =	  16;//����������
		lf.lfWeight	  =	  900;//���塢0Ĭ�ϡ���100-900��ÿ�μ�100��
		lf.lfUnderline=	  1;//�ڷ���ֵʱ����ָ������
	//	lf.lfStrikeOut=   1; //�ڷ���ֵʱ����ָ��������Ӧ����һ���ߴ�����
	//	lf.lfItalic   =	  1;//б�� ����0ֵʱΪб��
	//	lf.lfQuality  =   0;//DRAFT_QUALITY���ָ����ҪGDI���ŵ��������Եõ���Ҫ�Ĵ�С��PROOF_QUALITY���ָ���������š�PROOF_QUALITY������Ư���������ǿ��ܱ���ϣ����ҪСһЩ�������λ��Ҳ����ʹ��DEFAULT_QUALITY����0����
	//	lf.lfEscapement =1800;//��������0 �������ң��ڶ��� ��900 ����   ��2700 ���� 
	//	lf.lfOrientation =900 ;//������б90�� /0 �������ڶ��� /1800 �ߵ� /2700 ������б90�� 
		HFONT ht = CreateFontIndirectW(&lf); 
		ht=(HFONT)SelectObject(hdc,ht);
		////�����Ժ�������ĺ�ʽȡ��ĳ�ֱ�������Ĵ��ţ�
		//ht = GetStockObject (ht) ;
		////���У�iFont�Ǽ���ʶ����֮һ��Ȼ�ᣬ���Ϳ��Խ�������ѡ��װ�����ݣ�
		//SelectObject (hdc, ht) ;
		////��Щ��Ҳ����ֻ��һ����ɣ�
		//SelectObject (hdc, GetStockObject (ht)) ;

		TCHAR text[64]= L"���Ǽʴ�˵�����ܲ��԰� - �ռ����� 2013";
	//	SetTextAlign(hdc,TA_RIGHT);//���־��� �Ǽ�̹��V2.1 �ر�� ��������ǰ��<�Ǽʹ�����>�������� �� �ռ����� 2013.5.4
		TabbedTextOutW(hdc,0 ,YSCREEN-25,text, wcslen(text),NULL,NULL,NULL );
		DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

		lf.lfHeight   =   36;//��������߶�
		lf.lfWidth	  =	  36;//����������
		lf.lfWeight	  =	  900;//���塢0Ĭ�ϡ���100-900��ÿ�μ�100��
		lf.lfUnderline=	  0;//�ڷ���ֵʱ����ָ������
		ht = CreateFontIndirectW(&lf); 
		SelectObject(hdc,ht);
		WCHAR tx[8]= L"�Ǽʴ�˵";
		SetTextCharacterExtra (hdc, 10) ;//�����м��
		SetTextAlign(hdc,TA_CENTER);//���־���
		TextOutW(hdc,XSCREEN/2 ,YSCREEN/2-100,tx, wcslen(tx));
		DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

		DDS[SBuffer]->ReleaseDC(hdc);
	  }
	}else
	if( �ؿ� == MAP_EDIT )
	{	
		//���ô���Ϊ�Զ����	
		//WINDOWPLACEMENT wt;
		//wt.length =sizeof(WINDOWPLACEMENT);
		//wt.showCmd = SW_SHOWMAXIMIZED;//��� SW_SHOWMAXIMIZED ��С�� SW_SHOWMINIMIZED. ��ͨ SW_SHOWNORMAL.  
		//SetWindowPlacement(hWnd,&wt);
		//�����ͼ�༭��	
		oMapedit.MapEditUpdate() ; 
	}else
	if( �ؿ� == GAME_MAP )
	{	
		oMapedit.GameMapUpdate() ; //��ʾ��Ϸ��ͼ		
	}
	
	if( ��ͼ == false )dxinput.DXInputRefresh(); //�û�����ˢ��	
//	cime.ShowIME(nCmdShow);
	/*for(short i=0; i<10; i++)
	{
		if(oPlayer.m_bullePool.at(i)->GetShootSwitch() == true )
			oPlayer.m_bullePool.at(i)->Shooting();
	}*/
	
		//����mouseͼ��
	/*DDS[SBuffer]->BltFast( mouse.x , mouse.y , DDS[SXbmp] , NULL ,
							 DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT );*/
	MyFlip();
		//HRESULT ddrval;
		//MakeRect(0,0,1024,768);
		//ddrval=Blt(0,0,SBuffer,SPrimary,NoKey);
	
	//cime.ShowIME(nCmdShow);
}
bool Graph::MyFlip()
{
	HRESULT ddrval;

    // ����ģʽblit������Flip����
    if (IsWindowed)
    {
		RECT rcRectSrc;
		RECT rcRectDest;
		POINT p;
        // ������Ҫָ����ҳ���λ��
        p.x = 0; p.y = 0;
        ClientToScreen(hWnd, &p);
        GetClientRect(hWnd, &rcRectDest);
        OffsetRect(&rcRectDest, p.x, p.y);
        SetRect(&rcRectSrc, 0, 0, XSCREEN, YSCREEN);
	//	MakeRect(0,0,XSCREEN,YSCREEN);
	//	ddrval = Blt(0,0,SBuffer,SPrimary,DDBLTFAST_NOCOLORKEY| DDBLTFAST_WAIT);
		ddrval = DDS[SPrimary]->Blt( &rcRectDest, DDS[SBuffer], &rcRectSrc, DDBLT_WAIT, NULL);	
	//	ddrval = DDS[SPrimary]->BltFast(0,0,DDS[SBuffer],&rcRectSrc,DDBLTFAST_WAIT);
    }else{
        	//��ҳ
		MakeRect(0,0,XSCREEN,YSCREEN);
		ddrval=DDS[SPrimary]->Flip (DDS[SBuffer],DDFLIP_WAIT);
    }

	if (ddrval==DDERR_SURFACELOST)
	{ //int c =0;
		Restore();
	}
    return (ddrval == DD_OK);
}
void Graph::Restore()
{
	lpDD->RestoreAllSurfaces();	
	//for (int i=1;i<(DDSNum-1);i++)
	//{ DDS[i]->Restore( );}	
	////-----------------------------���ҳ��------------------------------
	//DDBLTFX ddBltFx;
	//ddBltFx.dwSize=sizeof(DDBLTFX);
	//ddBltFx.dwFillPixel=0;
	//for (int i=1;i<(DDSNum-1);i++)
	//{ DDS[i]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);}
	this->AddPictrue();
		
	//dxinput.~DxInput();
	//dxinput.DXInputInit(); //�ָ������ʼ��

}

HRESULT Graph::Blt(int x,int y,int src_id,int dest_id,int method)
{
	int rl,rt,tx1,tx2,ty1,ty2,tl,tt;
	RECT rect2=rect;

	rl=rect.left;
	rt=rect.top;

	if (rect.left>=SW[src_id])
		goto noblt; //Խ�磬��Blt
	if (rect.top>=SH[src_id])
		goto noblt;
	if (rect.right<=0)
		goto noblt;
	if (rect.bottom<=0)
		goto noblt;

	if (rect.left<0)
		rect.left=0;
	if (rect.top<0)
		rect.top=0;
	if (rect.right>SW[src_id])
		rect.right=SW[src_id];
	if (rect.bottom>SH[src_id])
		rect.bottom=SH[src_id];

	tx1=x+rect.left-rl;
	ty1=y+rect.top-rt;
	tx2=x+rect.right-rl;
	ty2=y+rect.bottom-rt;

	if (tx2<=0)
		goto noblt;
	if (ty2<=0)
		goto noblt;
	if (tx1>=SW[dest_id])
		goto noblt;
	if (ty1>=SH[dest_id])
		goto noblt;

	tl=tx1;
	tt=ty1;

	if (tx1<0)
		tx1=0;
	if (ty1<0)
		ty1=0;
	if (tx2>SW[dest_id])
		tx2=SW[dest_id];
	if (ty2>SH[dest_id])
		ty2=SH[dest_id];
	
	rl=rect.left;
	rt=rect.top;

	rect.left=tx1-tl+rl;
	rect.top=ty1-tt+rt;
	rect.right=tx2-tl+rl;
	rect.bottom=ty2-tt+rt;

	return DDS[dest_id]->BltFast(tx1,ty1,DDS[src_id],&rect,method);
noblt: 
	rect=rect2;
	return E_FAIL;
}