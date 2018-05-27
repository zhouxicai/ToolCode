#include "main.h"
#include "SpecialEfficiency.h"
#include "../../include/define.h"
GameGUI gameGUI ;

void GameGUI::MainBtn ()
{	// 获取mouse所指向的坐标值;
	POINT mouse ;	 GetCursorPos( &mouse ) ;

	// 游戏开始的背景图;
	DDS[SBuffer]->BltFast ( 0 , 0 , DDS[GameBack] , NULL ,
							DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT ) ;	
	// 绘制游戏主菜单按钮默认效果;
		MakeRect( 0 , 0 , 90 , 100 ) ; 
	DDS[SBuffer]->BltFast(	XSCREEN / 2 - 45 , YSCREEN / 2 ,
							DDS[主菜单] , &rect , 
							DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;
	RECT rc ;GetWindowRect(hWnd,&rc);
	//游戏屏幕中心;
	long bx = ( rc.right-rc.left )/2+rc.left;
	long by = ( rc.bottom-rc.top )/2+rc.top;
	// mouse坐标与主菜单“游戏开始”按钮坐标的接触检测	;
	if ( mouse.x > bx - 45			 && 
		 mouse.x < bx + 180 / 2 - 45 && 
		 mouse.y > by 				 && 
		 mouse.y < by + 100 / 4		 )
		{	// “开始游戏”按钮动态感应mouse按下效果代码;
			MakeRect( 90 , 0 , 180 , 25 ) ; 
		 DDS[SBuffer]->BltFast( XSCREEN / 2 - 45 , YSCREEN / 2 ,
		 						DDS[主菜单] , &rect ,
		 						DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;
		}
	// mouse坐标与主菜单“地图编辑器”按钮坐标的接触检测;	
	if ( mouse.x > bx - 45			&& 
		 mouse.x < bx + 180 / 2 - 45&& 
		 mouse.y > by + 100 / 4		&& 
		 mouse.y < by + 100 / 2		)
		{	//“地图编辑器”按钮动态感应mouse按下效果代码;
			MakeRect( 90 , 25 , 180 , 50 ) ;
		 DDS[SBuffer]->BltFast( XSCREEN / 2 - 45 , YSCREEN / 2 + 25 ,
								DDS[主菜单] , &rect ,
								DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT);
		}
	//cse.transparent();

		// 绘制游戏主菜单标题
		//HDC hdc=NULL;	wchar_t* text =L"奇门遁甲之迷你坦克";
		//DDS[SBuffer]->GetDC(&hdc);
		//SetBkMode(hdc,TRANSPARENT);
		//SetTextColor(hdc, RGB(200, 250, 100));
		//TextOut(hdc,10,10, text, wcslen(text) );
		//DDS[SBuffer]->ReleaseDC(hdc);	
}
//#include "DirectXAudio.h"
short GameGUI::SetMainBtn ()
{
	if ( graph.获得关卡数() != MAIN_BTN) return false; /*在主菜单点击该范围才有效*/
	// 获取mouse所指向的坐标值
	POINT mouse ;	 GetCursorPos( &mouse ) ; 
	RECT rc ; GetWindowRect(hWnd,&rc);
	long bx = ( rc.right-rc.left )/2+rc.left;
	long by = ( rc.bottom-rc.top )/2+rc.top;

	//mouse坐标与“地图编辑器”按钮坐标接触检测
	if ( mouse.x > bx-45		&& 
		 mouse.x < bx+180/2-45  && 
		 mouse.y > by+100/4	   && 
		 mouse.y < by+100/2		)
	{	
		return MAP_EDIT;
	}
	//mouse坐标与“开始游戏”按钮坐标接触检测/
	if ( mouse.x > bx-45		 && 
		 mouse.x < bx+180/2-45   && 
		 mouse.y > by			 && 
		 mouse.y < by+100/4		)
		{					
		//	oMapedit.ReadMapFile() ;		
			return GAME_MAP;
		}
	return MAIN_BTN;
}

/*地图编辑器按钮*/
void GameGUI::SetMapBtn () 
{
	// 获取mouse所指向的坐标值
	POINT mouse ;	 
	GetCursorPos( &mouse ) ; 

	RECT rc ; GetWindowRect(hWnd,&rc);
	double bx = rc.right-rc.left;
	double by = rc.bottom-rc.top;

	const long btn_bmp_x_size = 540;
	//double 比率 = ;
	double 地图按钮缩放的实际尺寸 = btn_bmp_x_size/(XSCREEN/bx);

	/*地图编辑器按钮默认效果*/
	MakeRect( 0 , 0 , 540 , 43 ) ; 
	DDS[SBuffer]->BltFast( 0 , YSCREEN - 43,DDS[MapBtn] , &rect ,
							DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT );
	
	/*地图编辑器按钮,动态感应mouse效果*/
	if ( mouse.x > rc.left && mouse.x < rc.left + 地图按钮缩放的实际尺寸 / 4   && 
		 mouse.y > by - 43 &&
		 mouse.y < by - 10 )
		{	MakeRect( 0 , 43 , 540 / 4 , 86 ) ; //指向 新建地图 效果
			DDS[SBuffer]->BltFast( 0 , YSCREEN - 43,DDS[MapBtn] , &rect , 
								DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT ) ;	
		}
	else if ( mouse.x > rc.left + 地图按钮缩放的实际尺寸  / 4  && 
			  mouse.x < rc.left + 地图按钮缩放的实际尺寸  / 2  && 
			  mouse.y > by - 43  &&
			  mouse.y < by - 15 		  )	
		{	MakeRect( 540 / 4 , 43 , 540 / 2 , 86 ) ; //指向 打开地图 效果
			DDS[SBuffer]->BltFast( 540 / 4 , YSCREEN - 43,DDS[MapBtn] , &rect , 
								DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT ) ;	
		}
	else if ( mouse.x > rc.left + 地图按钮缩放的实际尺寸 / 2   && 
			  mouse.x < rc.left + 地图按钮缩放的实际尺寸 - 地图按钮缩放的实际尺寸 / 4  && 
			  mouse.y > by - 43 &&
			  mouse.y < by - 15		  )	
		{	MakeRect( 540 / 2 , 43 , 540 - 540 / 4 , 86 ) ; //指向 保存地图 效果
			DDS[SBuffer]->BltFast( 540 / 2 , YSCREEN - 43,DDS[MapBtn] , &rect , 
								DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT ) ;	
		}
	else if ( mouse.x > rc.left + 地图按钮缩放的实际尺寸 - 地图按钮缩放的实际尺寸 / 4  && 
			  mouse.x < rc.left + 地图按钮缩放的实际尺寸	&&
			  mouse.y > by - 43 &&
			  mouse.y < by - 15		  )	
		{	MakeRect( 540 - 540 / 4 , 43 , 540 , 86 ) ; //指向 回主菜单 效果
			DDS[SBuffer]->BltFast( 540 - 540 / 4 , YSCREEN - 43,DDS[MapBtn] , &rect , 
								DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT) ;
		}
}