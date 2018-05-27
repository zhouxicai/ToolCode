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
	关卡 = 1 ;
	截图 = true;
	IsWindowed = false;
	//初始10发子弹
	//CGun * bulle = new CGun[10];
}
void Graph::设置关卡(int 关卡数)
{
	关卡=关卡数;
	/*  if 关卡=1 游戏主菜单
		if 关卡=2 地图编辑器
		if 关卡=3 开始游戏   */
}

bool Graph::Init()
{
	DDGameInitWindowed(hWnd);
	//CreateFullScreenSurfaces( ) ;


	AddPictrue();
	dxinput.DXInputInit(); //用户输入初始化

	oDirectXAudio.LoadMicMidiWav(L"audios/TMEMO01.mid",0);
	oMp3.Init();
	oMp3.Render("audios/TheDawn.mp3");

	return TRUE;
}

inline bool Graph::AddPictrue()
{	//创建后缓冲页

	//加载X标志,ddsd：DD页面描述
	memset( &ddsd, 0, sizeof(ddsd) );
	ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;//离屏页面,把除了主页面外的所有页面放在内存中;

	DDSetColorKey(DDS[MicroMap],RGB(0,0,0));//设置黑色为透明色
	DDSetColorKey(DDS[MicroMapZoom],RGB(0,0,0));//设置黑色为透明色
//	DDSetColorKey(DDS[BigMap],RGB(255,0,255));//设置紫色为透明色
	ddsd.dwHeight = YSCREEN+TILE_HIGH+TILE_HIGH ;//大一圈，用于滚动优化;
	ddsd.dwWidth  = XSCREEN+TILE_WIDE+TILE_WIDE ;
	if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[BigMap],NULL))return FALSE;//创建页面

	ddsd.dwHeight = 30 ;
	ddsd.dwWidth  = 30 ;
	if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[SXbmp],NULL))return FALSE;//创建页面
	DDReLoadBitmap(DDS[SXbmp],L"bmp/SXbmp.bmp");
	DDSetColorKey(DDS[SXbmp],RGB(0,255,0));//设置绿色为透明色
		//加载背景图
		ddsd.dwHeight = YSCREEN ;
		ddsd.dwWidth  = XSCREEN ;
		if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[GameBack],NULL))return FALSE;//创建页面
		DDReLoadBitmap(DDS[GameBack],L"bmp/star.bmp");	
	//加载开始页面按钮
	ddsd.dwHeight = 100 ;
	ddsd.dwWidth  = 180 ;
	if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[主菜单],NULL))return FALSE;//创建页面
	DDReLoadBitmap(DDS[主菜单],L"bmp/starbtn.bmp");
	DDSetColorKey(DDS[主菜单],RGB(0,0,0));//设置黑色为透明色
		//加载地图贴片
		ddsd.dwHeight = 704 ;
		ddsd.dwWidth  = 256 ;
		if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[STile],NULL))return FALSE;//创建页面
		DDReLoadBitmap(DDS[STile],L"bmp/MapT2.bmp");//14排,8列，32*32，256*448	
		DDSetColorKey(DDS[STile],RGB(255,0,255));//设置紫色为透明色
	//加载地图编辑器按钮
	ddsd.dwHeight = 86  ;
	ddsd.dwWidth  = 540 ;
	if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[MapBtn],NULL))return FALSE;//创建页面
	DDReLoadBitmap(DDS[MapBtn],L"bmp/MapBtn.bmp");
		//加载战车贴片
		ddsd.dwHeight = 128 ;
		ddsd.dwWidth  = 64 ;
		if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[MM2TankB],NULL))return FALSE;//创建页面
		DDReLoadBitmap(DDS[MM2TankB],L"bmp/Tank01.bmp");
		DDSetColorKey(DDS[MM2TankB],RGB(255,0,255));//设置紫色为透明色
	//加载子弹位图
	ddsd.dwHeight = 16 ;
	ddsd.dwWidth  = 16 ;
	if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[BaseBulle],NULL))return FALSE;//创建页面
	DDReLoadBitmap(DDS[BaseBulle],L"bmp/Bulle.bmp");
	DDSetColorKey(DDS[BaseBulle],RGB(0,0,255));//设置透明色
	//如果还有其他页面可在此继续创建	
		//加载机甲贴片
		ddsd.dwHeight = 256 ;
		ddsd.dwWidth  = 256 ;
		if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[机甲],NULL))return FALSE;//创建页面
		DDReLoadBitmap(DDS[机甲],L"bmp/机甲.bmp");
		DDSetColorKey(DDS[机甲],RGB(255,0,255));//设置紫色为透明色
	
	//初始化背景地图
	//SW[BackMap] = 100*32;	SH[BackMap] = 100*32;
	//ddsd.dwHeight = SW[BackMap] ;
	//ddsd.dwWidth  = SH[BackMap] ;
	//if(DD_OK!=lpDD->CreateSurface(&ddsd,&DDS[BackMap],NULL))return FALSE;//创建页面
	//mapEdt.SetShowAllMapLayer(true);
	//mapEdt.ReadMapFile ( ) ;
	//mapEdt.ShowMap ( 32 , 32 , 0 , 0 ) ;
	return TRUE;
}

 BOOL Graph::CreateFullScreenSurfaces()
 {	//初始化DirectDraw---------------------------------------------------
		//创建DD对象 
	if(DirectDrawCreateEx(NULL,(void **)&lpDD,IID_IDirectDraw7,NULL)!=DD_OK)return FALSE;
		//设置控制级，取得独占和全屏模式
	if(lpDD->SetCooperativeLevel(hWnd,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN)!=DD_OK )return FALSE;
		//设置显示模式
	if(lpDD->SetDisplayMode (XSCREEN,YSCREEN,32,0,DDSDM_STANDARDVGAMODE)!=DD_OK)return FALSE;
	//初始化各页面-------------------------------------------------------
		//设置主页面
		memset(&ddsd,0,sizeof(DDSURFACEDESC2));//先清空页面描述
		//填充主页面描述
		ddsd.dwSize =sizeof(ddsd);
		ddsd.dwFlags =DDSD_CAPS|DDSD_BACKBUFFERCOUNT;//有后台缓存
		ddsd.ddsCaps .dwCaps =DDSCAPS_PRIMARYSURFACE|DDSCAPS_FLIP|DDSCAPS_COMPLEX;//主页面，有换页链，有后台缓存
		ddsd.dwBackBufferCount=1;//一个后台缓存
		//创建主页面
	if(lpDD->CreateSurface(&ddsd,&DDS[SPrimary],NULL)!=DD_OK)return FALSE;
		ddsd.ddsCaps .dwCaps =DDSCAPS_BACKBUFFER;//这是后台缓存
		//提取后台缓存表面指针，GetAttachedSurface得到一个指向缓冲的指针
	if(DD_OK!=DDS[SPrimary]->GetAttachedSurface (&ddsd.ddsCaps ,&DDS[SBuffer]))return FALSE;
	

	// 单独创建后缓冲页和小地图缓冲页面
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

	
		//填充背景
		DDBLTFX ddBltFx;
		ddBltFx.dwSize =sizeof(DDBLTFX);//ddBltFx.dwFillPixel=0;
		ddBltFx.dwFillColor =RGB(0,0,0);//黑色背景
	DDS[SPrimary]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	DDS[SBuffer]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
//	DDS[MicroMap]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
		
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;//这是离屏页面
		
		return true ;
 }


// 窗口模式初始化DirectDraw的函数
bool Graph::DDGameInitWindowed(THIS_ HWND hwnd)
{
//    DDSURFACEDESC ddsd;
//    DDSCAPS ddscaps;
    HRESULT ddrval;

    IsWindowed = true;

   /*
    * 创建DirectDraw主对象
    */

  	//创建DD主对象 
	if(DirectDrawCreateEx(NULL,(void **)&lpDD,IID_IDirectDraw7,NULL)!=DD_OK)return FALSE;
	//设置DD控制级，用DDSCL_NORMAL表示我们要与GDI共存
	if(lpDD->SetCooperativeLevel(hwnd,DDSCL_NORMAL )!=DD_OK ){lpDD->Release();return FALSE;}
	//设置显示模式
	if(lpDD->SetDisplayMode (XSCREEN,YSCREEN,32,0,DDSDM_STANDARDVGAMODE)!=DD_OK)return FALSE;

	//	RECT  rcWork;
	//	RECT  rc;
	////	DWORD dwStyle;	

	////	SetWindowLong( hWnd, GWL_STYLE, dwStyle );
	//	// 设置尺寸
	//	SetRect( &rc, 0, 0, XSCREEN, YSCREEN );
	//	SetWindowPos( hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
 //                 SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE );

	//	SetWindowPos( hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,
 //                 SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE );
	//	// 保证不会到窗口外
	//	SystemParametersInfo( SPI_GETWORKAREA, 0, &rcWork, 0 );
	//	GetWindowRect( hWnd, &rc );
 //   
	//	if( rc.left < rcWork.left ) rc.left = rcWork.left;
	//	    
	//	if( rc.top  < rcWork.top )  rc.top  = rcWork.top;
	//	    
	//	SetWindowPos( hWnd, NULL, rc.left, rc.top, 0, 0,
	//	              SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
	
	// 这次主页面不是可翻页的页面
    memset( &ddsd, 0, sizeof(ddsd) );
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE; 
	ddsd.dwHeight = YSCREEN ;
	ddsd.dwWidth  = XSCREEN ;
	if(lpDD->CreateSurface(&ddsd,&DDS[SPrimary],NULL)!=DD_OK){lpDD->Release();return FALSE;}
	RECT client; 
	GetWindowRect(hWnd, &client);


    // 创建一个裁切板保证不画到窗口外面
    ddrval = lpDD->CreateClipper( 0, &lpClipper, NULL );
    if( ddrval != DD_OK )
    {
        DDS[SPrimary]->Release();
        lpDD->Release();
        return(false);
    }

    // 把窗口句柄设置给裁切板就给了它一个与窗口相适的裁切框
    ddrval = lpClipper->SetHWnd( 0, hWnd );
    if( ddrval != DD_OK )
    {
        lpClipper-> Release();
        DDS[SPrimary]->Release();
        lpDD->Release();
        return(false);
    }

    // 把裁切板附到主页面
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

    // 单独创建后缓冲页和小地图缓冲页面
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
  	//创建DD对象 
	if(DirectDrawCreateEx(NULL,(void **)&lpDD,IID_IDirectDraw7,NULL)!=DD_OK)return FALSE;
	//设置DD控制级
	if(lpDD->SetCooperativeLevel(hWnd,DDSCL_NORMAL )!=DD_OK )return FALSE;//DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN
	//设置显示模式，获得系统分辨率GetSystemMetrics()
	if(lpDD->SetDisplayMode (XSCREEN,YSCREEN,32,0,DDSDM_STANDARDVGAMODE)!=DD_OK)return FALSE;
	
		RECT  rcWork;
		RECT  rc;
	//	DWORD dwStyle;	

	//	SetWindowLong( hWnd, GWL_STYLE, dwStyle );
		// 设置尺寸
		SetRect( &rc, 0, 0, XSCREEN, YSCREEN );
		SetWindowPos( hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
                  SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE );

		SetWindowPos( hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,
                  SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE );
		// 保证不会到窗口外
		SystemParametersInfo( SPI_GETWORKAREA, 0, &rcWork, 0 );
		GetWindowRect( hWnd, &rc );
    
		if( rc.left < rcWork.left ) rc.left = rcWork.left;
		    
		if( rc.top  < rcWork.top )  rc.top  = rcWork.top;
		    
		SetWindowPos( hWnd, NULL, rc.left, rc.top, 0, 0,
		              SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );

		//设置主页面
		memset(&ddsd,0,sizeof(DDSURFACEDESC2));//先清空页面描述
		//填充页面描述
		ddsd.dwSize =sizeof(ddsd);
		ddsd.dwFlags =DDSD_CAPS;//无后台缓存
		ddsd.dwWidth = XSCREEN;
		ddsd.dwHeight = YSCREEN;
		ddsd.ddsCaps .dwCaps = DDSCAPS_PRIMARYSURFACE;//去掉后台缓存和换页DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		ddsd.dwBackBufferCount=1;//一个后台缓存
	if(lpDD->CreateSurface(&ddsd,&DDS[SPrimary],NULL)!=DD_OK)return FALSE;//创建主页面

	//	ddsd.ddsCaps .dwCaps =DDSCAPS_BACKBUFFER;//这是后台缓存//创建后台缓存	
	//if(DD_OK!=DDS[SPrimary]->GetAttachedSurface (&ddsd.ddsCaps ,&DDS[SPrimary]))return FALSE;
		
	    // 创建剪裁器并关联到窗口
		if (lpDD->CreateClipper( 0, &lpClipper, NULL ) != DD_OK )goto fail;
		if ( lpClipper->SetHWnd( 0, hWnd ) != DD_OK )goto fail;
		//if ( lpFrontBuffer->SetClipper( lpClipper ) != DD_OK )
		// 释放剪裁器，在我们使用SetClipper设置时，会自动的获得操作。
		//if ( lpClipper->Release() != DD_OK )goto fail;
		fail:
		    return FALSE;

		//填充背景
		//	DDBLTFX ddBltFx;
		//	ddBltFx.dwSize =sizeof(DDBLTFX);//ddBltFx.dwFillPixel=0;
		//	ddBltFx.dwFillColor =RGB(0,0,0);//黑色背景
		//DDS[SPrimary]->Blt (NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
		//DDS[SBuffer]->Blt (NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
		//ddsd.dwSize =sizeof(ddsd);
		//ddsd.dwFlags =DDSD_CAPS;
		//ddsd.ddsCaps.dwCaps =DDSCAPS_OFFSCREENPLAIN;//这是离屏页面
 }
//游戏画面刷新
 void Graph::GameRefresh(HINSTANCE hInstance, int nCmdShow)
{	
		//刷新图形时填充背景色
	//	MakeRect(0,0,XSCREEN,YSCREEN);//填充区域
		DDBLTFX ddBltFx;
		ddBltFx.dwSize =sizeof(DDBLTFX);
		ddBltFx.dwFillPixel=0;//填充背景色为黑色	
	//	ddBltFx.dwFillColor = RGB(100,100,0);//指定填充色	
	DDS[SBuffer]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	//DDS[SBuffer]->BltFast ( 500 , 300 , DDS[BaseBulle] , NULL ,
	//						DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
	if( 关卡 == MAIN_BTN ) 
	{
		////设置窗口为自动最大化	
		//WINDOWPLACEMENT wt;	
		//wt.rcNormalPosition.top = 50;
		//wt.rcNormalPosition.left = 100;
		//wt.rcNormalPosition.right = 960;
		//wt.rcNormalPosition.bottom = 540;
		//wt.length =sizeof(WINDOWPLACEMENT);
		//wt.showCmd = SW_SHOWNORMAL;//最大化 SW_SHOWMAXIMIZED 最小化 SW_SHOWMINIMIZED. 普通 SW_SHOWNORMAL.  
		//SetWindowPlacement(hWnd,&wt);
		gameGUI.MainBtn() ; //进入游戏主菜单
		oMapedit.SetShowAllMapLayer(true);
		
		oDirectXAudio.StopMicMidiWav();
		oMp3.Stop();

		HDC hdc(NULL);
	  if (DDS[SBuffer]->GetDC(&hdc) == DD_OK)
	  { 
		SetBkMode(hdc,TRANSPARENT);//设置背景模式
		SetTextColor(hdc, RGB(230, 230, 230));
		SetTextCharacterExtra (hdc, 1) ;//设置行间距
		
		//SetMapMode 	(hdc, MM_ANISOTROPIC) ;
		//SetWindowExtEx 	 (hdc, 1440, 1440, NULL) ;
		//SetViewportExtEx (hdc,	GetDeviceCaps (hdc, LOGPIXELSX),
  //                   	GetDeviceCaps (hdc, LOGPIXELSY), NULL) ;


		static LOGFONT   lf; 
		memset(&lf,   0,   sizeof(LOGFONT)); 
		lf.lfHeight   =   18;//设置字体高度
		lf.lfWidth	  =	  16;//设置字体宽度
		lf.lfWeight	  =	  900;//粗体、0默认、从100-900，每次加100；
		lf.lfUnderline=	  1;//在非零值时，它指定底线
	//	lf.lfStrikeOut=   1; //在非零值时，它指定字体上应该有一条线穿过。
	//	lf.lfItalic   =	  1;//斜体 ，非0值时为斜体
	//	lf.lfQuality  =   0;//DRAFT_QUALITY旗标指出需要GDI缩放点阵字体以得到想要的大小；PROOF_QUALITY旗标指出不需缩放。PROOF_QUALITY字体最漂亮，但它们可能比所希望的要小一些。这个栏位中也可以使用DEFAULT_QUALITY（或0）。
	//	lf.lfEscapement =1800;//从右向左、0 从左向右（内定） 、900 向上   、2700 向下 
	//	lf.lfOrientation =900 ;//向右倾斜90度 /0 正常（内定） /1800 颠倒 /2700 向左倾斜90度 
		HFONT ht = CreateFontIndirectW(&lf); 
		ht=(HFONT)SelectObject(hdc,ht);
		////您可以呼叫下面的函式取得某种备用字体的代号：
		//ht = GetStockObject (ht) ;
		////其中，iFont是几个识别字之一。然後，您就可以将该字体选入装置内容：
		//SelectObject (hdc, ht) ;
		////这些您也可以只用一步完成：
		//SelectObject (hdc, GetStockObject (ht)) ;

		TCHAR text[64]= L"《星际传说》功能测试版 - 终极程序 2013";
	//	SetTextAlign(hdc,TA_RIGHT);//文字居中 星际坦克V2.1 特别版 纪念五年前的<星际工作室>和朋友们 ！ 终极程序 2013.5.4
		TabbedTextOutW(hdc,0 ,YSCREEN-25,text, wcslen(text),NULL,NULL,NULL );
		DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

		lf.lfHeight   =   36;//设置字体高度
		lf.lfWidth	  =	  36;//设置字体宽度
		lf.lfWeight	  =	  900;//粗体、0默认、从100-900，每次加100；
		lf.lfUnderline=	  0;//在非零值时，它指定底线
		ht = CreateFontIndirectW(&lf); 
		SelectObject(hdc,ht);
		WCHAR tx[8]= L"星际传说";
		SetTextCharacterExtra (hdc, 10) ;//设置行间距
		SetTextAlign(hdc,TA_CENTER);//文字居中
		TextOutW(hdc,XSCREEN/2 ,YSCREEN/2-100,tx, wcslen(tx));
		DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

		DDS[SBuffer]->ReleaseDC(hdc);
	  }
	}else
	if( 关卡 == MAP_EDIT )
	{	
		//设置窗口为自动最大化	
		//WINDOWPLACEMENT wt;
		//wt.length =sizeof(WINDOWPLACEMENT);
		//wt.showCmd = SW_SHOWMAXIMIZED;//最大化 SW_SHOWMAXIMIZED 最小化 SW_SHOWMINIMIZED. 普通 SW_SHOWNORMAL.  
		//SetWindowPlacement(hWnd,&wt);
		//进入地图编辑器	
		oMapedit.MapEditUpdate() ; 
	}else
	if( 关卡 == GAME_MAP )
	{	
		oMapedit.GameMapUpdate() ; //显示游戏地图		
	}
	
	if( 截图 == false )dxinput.DXInputRefresh(); //用户输入刷新	
//	cime.ShowIME(nCmdShow);
	/*for(short i=0; i<10; i++)
	{
		if(oPlayer.m_bullePool.at(i)->GetShootSwitch() == true )
			oPlayer.m_bullePool.at(i)->Shooting();
	}*/
	
		//绘制mouse图标
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

    // 窗口模式blit，否则Flip即可
    if (IsWindowed)
    {
		RECT rcRectSrc;
		RECT rcRectDest;
		POINT p;
        // 首先需要指出主页面的位置
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
        	//翻页
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
	////-----------------------------清空页面------------------------------
	//DDBLTFX ddBltFx;
	//ddBltFx.dwSize=sizeof(DDBLTFX);
	//ddBltFx.dwFillPixel=0;
	//for (int i=1;i<(DDSNum-1);i++)
	//{ DDS[i]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);}
	this->AddPictrue();
		
	//dxinput.~DxInput();
	//dxinput.DXInputInit(); //恢复输入初始化

}

HRESULT Graph::Blt(int x,int y,int src_id,int dest_id,int method)
{
	int rl,rt,tx1,tx2,ty1,ty2,tl,tt;
	RECT rect2=rect;

	rl=rect.left;
	rt=rect.top;

	if (rect.left>=SW[src_id])
		goto noblt; //越界，不Blt
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