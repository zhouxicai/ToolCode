#include "MapEdt.h"
#include "MapDefine.h"
#include "Player.h"
#include "Spirit.h"
#include "FileOperate.h"
#include "SpecialEfficiency.h"
#include "TimeCount.h"
#include "main.h"
#include "Snow.h"
#include "DirectXAudio.h"

//显示游戏地图;
void Mapedit::GameMapUpdate()
{		
	ShowMap ( TILE_WIDE , TILE_HIGH , 0 , 0 ) ;
	CollideCheck ( PLAYER_MOVE_SPEED ) ;

	if (m_bTinyMap) 
	{
		ShowMicroMap ( ) ; //用M按键控制开关	
	}
	//特效;
	if(cse.GetRainBool()) 
	{
		cse.RainRandom();
	}
	else if(gRainKeepTime.GetNowTime() > (cse.GetRainKeepTime()+(rand()%120)))
	{ //随机停止一段时间，再初始化，初始化后，上面就开始下雨了;
		cse.InitRain();
	}
	else
	{
		cse.StopRain();//停止播放音效
	//	oDirectXAudio.PlayMicMidiWav();//播放背景音乐
	}

	if( cse.GetSnowBool() ) { cse.SnowRandom(200);oSnowMgr.Snowing(200);}
	if( cse.GetLightBool() ) {/*cse.LightIntensity();*/ cse.light_asm();}
	

	//绘制角色坐标
	HDC hdc(NULL);
	if (DDS[SBuffer]->GetDC(&hdc) == DD_OK)
	{ 
		TCHAR text[128];
		wsprintfW(text,L"%s:X:%d Y:%d + RollScreenX:%d RollScreenY:%d = x:%d ,y:%d" ,szMapName, oPlayer.GetPlayerMapX(),oPlayer.GetPlayerMapY(),mRollScreenX,mRollScreenY,
			(oPlayer.GetPlayerMapX()+ mRollScreenX),(oPlayer.GetPlayerMapY()+ mRollScreenY));
		SetBkMode(hdc,TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOutW(hdc,TILE_WIDE,TILE_HIGH,text, wcslen(text) ); //多字符集用strlen代替wcslen;
		DDS[SBuffer]->ReleaseDC(hdc);
	}

	//填充边框为黑色,游戏区域;
	DDBLTFX ddBltFx;
	ddBltFx.dwSize =sizeof(DDBLTFX);
	ddBltFx.dwFillPixel=0;//设置黑色;
	//填充区域	顶部;
	MakeRect(0,0,XSCREEN,TILE_HIGH);		
	DDS[SBuffer]->Blt(&rect,NULL,&rect,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	//填充区域	底部;	
	MakeRect(0,YSCREEN-TILE_HIGH,XSCREEN,YSCREEN);
	DDS[SBuffer]->Blt(&rect,NULL,&rect,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	//填充区域	左部;		
	MakeRect(0,0,TILE_WIDE,YSCREEN);
	DDS[SBuffer]->Blt(&rect,NULL,&rect,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	//填充区域	右部;	
	MakeRect(XSCREEN-TILE_WIDE,0,XSCREEN,YSCREEN);
	DDS[SBuffer]->Blt(&rect,NULL,&rect,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
}

/*地图编辑器;*/
void Mapedit::MapEditUpdate()
{
	//绘制地图编辑器网格;
	HDC hDC;	DDS[SBuffer]->GetDC(&hDC);
	//COLORREF crCol = ::GetPixel(hDC,200, 200); //取得（200, 200）处的颜色值;
	for(int line = 0 ; line <= MAP_EDIT_AREA_Y ; line += TILE_WIDE )
		for(int law = 0 ; law <= MAP_EDIT_AREA_X ; law  += TILE_HIGH )
			::SetPixel(hDC, law, line, RGB(255,255,255)); //绘制白色网格;
	DDS[SBuffer]->ReleaseDC(hDC);   //别忘了释放DC;

	//鼠标左键是否在地图区按下&是否选择单个对象&是否在地图编辑区;
	if( !m_EditSave && bMouseLeftHitMap && IsNoSelectSingleTile() /*&& MouseIsAtMapEditArae()*/ )	
	{	//根据鼠标按下时“移动轨迹”区域,“动态存储”Tile;
		存储单个素材 ();
	}
	if( iMouseRightHitMap == PUSH_DOWN )//按下;
	{
		//if(TileBeginX <TileXEnd || TileBeginY <TileYEnd)
		//存储框选素材 (); 
	}
	else
		if( iMouseRightHitMap == PUSH_UP )//松开;
		{
			//if( sMouseRightHitMapDownX != sMouseRightHitMapUpX ||
			//	sMouseRightHitMapDownY != sMouseRightHitMapUpY  )
			//填充地图();
			iMouseRightHitMap = PUSH_NOT;//完成操作;
		}
	
		ShowMap   ( TILE_WIDE , TILE_HIGH , -256 , -64 ) ;	
		//RefreshMap(0,0);
		//	if( m_bCollideState != false )
		显示碰撞点 ( ) ;
		if (m_bTinyMap)
		{
			ShowMicroMap () ;
		}		
		显示素材   ( ) ;
		SetRollScreen ( MAP_EDIT_MOVE_SPEED ) ;

		if( 大刷子 ) 
		{	//如果大刷子功能打开，则让地图混一色;
			if( MessageBoxW(hWnd,L"是否填充整个地图？",L"刷子",MB_OKCANCEL)!=2 )
			{//确认
				GetBigBrush () ; 
			}
			大刷子 = false;
		}

		gameGUI.SetMapBtn(); /*地图编辑器按钮GUI;*/

		//绘制地图编辑器标题文字;
		static HDC hdc; 
		if (DDS[SBuffer]->GetDC(&hdc) == DD_OK)
		{	
			static HFONT ht;
			static LOGFONT lf; 
			SetBkMode(hdc,TRANSPARENT);//设置背景模式透明;
			SetTextColor(hdc, RGB(200, 0, 0));//设置字体颜色;
			SetTextCharacterExtra (hdc, 1) ;//设置行间距;

			memset(&lf,   0,   sizeof(LOGFONT)); 
			lf.lfHeight   =   28;//设置字体高度;
			lf.lfWidth	  =	  26;//设置字体宽度;
			lf.lfWeight	  =	  900;//粗体、0默认、从100-900，每次加100；
			ht = CreateFontIndirectW(&lf); 
			ht = (HFONT)SelectObject(hdc,ht);
			static TCHAR text[32];
			if (m_bCollideState)
			{
				wsprintfW(text,L"编辑第 %d 层 碰撞:打开" , 图层+1);
			} 
			else
			{
				wsprintfW(text,L"编辑第 %d 层 碰撞:关闭！" , 图层+1);

			}				
			TabbedTextOutW(hdc,555 ,YSCREEN-35,text, wcslen(text),NULL,NULL,NULL );
			DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

			//	SetTextAlign(hdc,TA_RIGHT);//文字居中;
			memset(&lf,   0,   sizeof(LOGFONT)); 
			lf.lfHeight   =   12;//设置字体高度;
			lf.lfWidth	  =	  10;//设置字体宽度;
			lf.lfWeight	  =	  900;
			ht = CreateFontIndirectW(&lf); 
			ht = (HFONT)SelectObject(hdc,ht);
			SetTextColor(hdc, RGB(255, 255, 0));
			static TCHAR txt[MAX_PATH];// = L"星际地图编辑器";
			wsprintfW(txt,L"星际地图编辑器 - %s" ,szMapName);

			TextOutW(hdc,10,10, txt, wcslen(txt) ); //多字符集用strlen代替wcslen;				
			DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

			DDS[SBuffer]->ReleaseDC(hdc);
		}
		DrawMouseRightKeySelectRect();
		DrawMouseLeftKeySelectRect();
		
		//	MapEditBottomLine();
}

void Mapedit::LoadDefaultMap()
{
	if (!wcslen(szMapName))
	{ 
		if (FILE * f = _wfopen(L"map//白云城.dat",L"r"))
		{ 	
			fread(MapX,sizeof(int),30000,f);
			fread(MapY,sizeof(int),30000,f);
			fread(mCollideArray,sizeof(bool),10000,f);
			wcscpy_s(szMapName,L"白云城");
			SetMonster(SPIRIT_POOL_MAX);
			fclose(f);
		}	
	}
}

void Mapedit::SetMonster(unsigned int cnt)
{
	for (unsigned int c = 0; c < cnt; ++ c)//测试
	{ 
		oSpiritManager.SpiritInit(c,rand()%AI_ACTION_WIDE, rand()%AI_ACTION_HEIGHT);
	}
}

void Mapedit::SetTinyMapStatus(bool is_open)
{
	m_bTinyMap = is_open;
	if( graph.获得关卡数() == MAP_EDIT )//游戏地图暂时不更新小地图;
	SetMicroMap();
}