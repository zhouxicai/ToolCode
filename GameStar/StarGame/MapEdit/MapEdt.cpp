#include "main.h"
#include "FileOperate.h"
#include "SpecialEfficiency.h"
#include "TimeCount.h"
#include "Player.h"
#include "Spirit.h"
Mapedit oMapedit;

Mapedit::Mapedit()
{
	bMouseLeftHitMap   = false ; //mouse在地图区按下的状态 ，默认0为什么都没有做;
	iMouseRightHitMap  = PUSH_NOT ;
	TileBeginX = TileBeginY = EMPTY_TILE ;
	TileXEnd   = TileYEnd   = EMPTY_TILE ;
	sMouseLeftHitMapDownX = sMouseLeftHitMapDownY = 0 ;
	RollScreenFace = 0 ; //默认不滚屏
	mRollScreenX = mRollScreenY  = 0 ; //(1)向下移动(2)向上移动(3)向右移动(4)向左移动;

	//初始化地图数组;
		memset( MapX, EMPTY_TILE, sizeof(int)*3*MAPX_GRID*MAPX_GRID ); 
		memset( MapY, EMPTY_TILE, sizeof(int)*3*MAPY_GRID*MAPY_GRID ); 

	m_bCollideState = false ; //默认关闭 碰撞设置;
	大刷子   = false ; //默认关闭刷子;
	m_bRollScreenState = true ;
	//默认显示全图层;
	mShowAllMapLayer = true ;
	图层 = 0 ; 

	iSelectPathX = iSelectPathY=0;
//	r=true;
	bCollide = false;
	m_bTinyMap = false;
	wmemset(szMapName,NULL,NULL);

	sMouseLeftHitMapUpX = sMouseLeftHitMapUpX = sMouseLeftHitMapUpY = sMouseLeftHitMapUpY =
	sMouseLeftHitMapDownX = sMouseLeftHitMapDownX = sMouseLeftHitMapDownY = sMouseLeftHitMapDownY = EMPTY; 
	iLeftHitMapBeginX =  iLeftHitMapBeginY = 0 ;
	bMouseLeftHitMapDownForCopy = false;
}
/*****************************************************************************

*/
void Mapedit::LoadMouseSelectRectangleFromFile()
{

}
int Mapedit::GetRollScreen( int xy )
{
    if ( xy == 0 ) return mRollScreenX ;
    else if ( xy == 1 ) return mRollScreenY ;
	else return 0 ;
}

inline void Mapedit::SaveCollide( int x , int y )
{	//  数组越界检查，如果越界则不存储数据;
	if (x >= 0 && x <= 99 && y >= 0 && y <= 99)
	{
		if( m_bCollideState == FALSE ) 
			mCollideArray[x][y] = FALSE ;
		else 
			mCollideArray[x][y] = TRUE  ;
	}
}

void Mapedit::显示素材 ()
{
	// 获取mouse所指向的坐标值;
	POINT mouse ;	 GetCursorPos( &mouse ) ; 

	// 绘制地图编辑器的素材;
	DDS[SBuffer]->BltFast( XSCREEN - 256  , 0 ,
						   DDS[STile] , NULL , DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;
	// 绘制跟随mouse的帖块图;
	MakeRect( TileBeginX * TILE_WIDE ,TileBeginY * TILE_HIGH ,
			  TileXEnd *TILE_WIDE +TILE_WIDE ,TileYEnd *TILE_HIGH +TILE_HIGH ) ;
	DDS[SBuffer]->BltFast ( mouse.x , mouse.y , DDS[STile] , &rect ,
							DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;
}

void Mapedit::LeftHitTileAreaUp ()
{	
	if (m_EditSave)
	{
		return;
	}
	// 获取mouse所指向的坐标值;
	POINT mouse ;	 GetCursorPos( &mouse ) ; 

	//LONG window_y_move = 8;
	//RECT rc ; GetWindowRect(hWnd,&rc);
	////素材与mouse检测，如果在素材区点击;
	//if ( mouse.x > rc.right - 得到素材缩放后尺寸X() && 
	//	 mouse.x < rc.right && 
	//	 mouse.y - window_y_move > rc.top && 
	//	 mouse.y - window_y_move < rc.top + 得到素材缩放后尺寸Y() ) {
	//	  //计算用户点击贴片的列数与行数
	//	  TileXEnd = ( mouse.x - ( rc.right - 得到素材缩放后尺寸X() ) ) / ( TILE_WIDE/得到窗体缩放比率X() ) ;
	//	  TileYEnd = ( mouse.y - window_y_move ) / ( TILE_HIGH/得到窗体缩放比率Y() ) ;	}

	////素材与mouse检测，如果在素材区松开mouse;
	if ( MouseIsNoAtTileArae() == true ) 
	{	 //计算用户点击贴片的列数与行数;
		  TileXEnd = ( mouse.x - ( XSCREEN - 256 ) ) / TILE_WIDE ;
		  TileYEnd = ( mouse.y  ) / TILE_HIGH ;	
	}
	bMouseLeftHitMap   = false ;//防止没有Click Map（点击地图），却是鼠标按下状态;
}

void Mapedit::LeftHitTileArea ()
{	
	if (m_EditSave)
	{
		return;
	}
	// 获取mouse所指向的坐标值;
	POINT mouse ;	 GetCursorPos( &mouse ) ; 

	////素材与mouse检测，如果在素材区点击;
	if ( mouse.x > XSCREEN - 256 &&  mouse.x < XSCREEN && 
		 mouse.y > 0 && mouse.y < 704 ) {	 
		  //计算用户点击贴片的列数与行数;
		  TileBeginX = ( mouse.x - ( XSCREEN - 256 ) ) / TILE_WIDE ;
		  TileBeginY = ( mouse.y ) / TILE_HIGH ;	}
}
void Mapedit::RightHitTileArea ()
{	// 获取mouse所指向的坐标值;
	POINT mouse ;	 GetCursorPos( &mouse ) ; 

	////素材与mouse检测，如果在素材区点击;
	if ( mouse.x > XSCREEN - 256 &&  mouse.x < XSCREEN && 
		mouse.y > 0 && mouse.y < 704 ) {	 
			SetMouseTileToEmpty();	}
}

void Mapedit::LeftHitMapUp()
{
	iLeftHitMapBeginX = iLeftHitMapBeginY = 0;
	if( graph.获得关卡数() == MAP_EDIT )/*在地图编辑器页面;*/
	{
		bMouseLeftHitMapDownForCopy = false;
		POINT mouse ;	 GetCursorPos( &mouse ) ; 
		//在地图编辑区点击，地图与mouse检测;
		if ( mouse.x > 0 && mouse.x < XSCREEN - 256 && mouse.y > 0 && mouse.y < YSCREEN - 64  )
		{	 
			//计算点击的地图列数与行数;
			sMouseLeftHitMapUpX = ( (int)mouse.x - mRollScreenX ) / TILE_WIDE ;	
			sMouseLeftHitMapUpY = ( (int)mouse.y - mRollScreenY ) / TILE_HIGH ;	
			bMouseLeftHitMap = false;

			if (GetEditSave())
			{
				if (sMouseLeftHitMapUpX == sMouseLeftHitMapDownX && sMouseLeftHitMapUpY == sMouseLeftHitMapDownY)
				{	//2016.5.21注释
				/*	if( MessageBoxW(hWnd,L"确定克隆框选区域吗？",L"复制框选区域",MB_OKCANCEL)!=2 )
					{
						int mpx=sMouseLeftHitMapUpX;
						int mpy=sMouseLeftHitMapUpY;
						for (size_t layer=0;layer<MAP_LAYER;layer++)
						{
							for ( size_t cx=0,mpx=sMouseLeftHitMapUpX;cx<mMultiArray.shape()[1];cx++,mpx++)	
							{
								for ( size_t cy=0,mpy=sMouseLeftHitMapUpY;cy<mMultiArray.shape()[2];cy++,mpy++)
								{
									MapX[layer][mpx][mpy] = mMultiArray[layer][cx][cy].mx ;
									MapY[layer][mpx][mpy] = mMultiArray[layer][cx][cy].my ;	
									mCollideArray[mpx][mpy] = mMultiArray[0][cx][cy].cs;	
									//精确可缩放小地图;
									int LeftX = MapX[layer][mpx][mpy] * TILE_WIDE;  int RightX  = MapX[layer][mpx][mpy] * TILE_WIDE + TILE_WIDE;
									int TopY  = MapY[layer][mpx][mpy] * TILE_HIGH;  int BottomY = MapY[layer][mpx][mpy] * TILE_HIGH + TILE_HIGH;
									MakeRect( LeftX , TopY ,RightX , BottomY );
									DDS[MicroMapZoom]->BltFast( mpx * TILE_WIDE  , mpy * TILE_HIGH , DDS[STile] , &rect ,  DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;

								}
							}
						}
					}*/			
				}	
				SetMicroMap();
				return;//如果准备存储框选区域，则不能继续编辑;
			}

			//存储用户点击的地图列数与行数;
			if (TileBeginX == EMPTY_TILE || TileBeginY == EMPTY_TILE )
			{
			//	SaveCollide ( sMouseLeftHitMapUpX , sMouseLeftHitMapUpY ) ;
				if (!m_bCollideState)
				{ return;
				}			
			}
			
			//
			if(TileBeginX <TileXEnd || TileBeginY <TileYEnd)
				存储框选素材 (); 
		//		SetMicroMap();每次全部存储太卡，如果能局部更新，应该不会卡！;
			//else
			//	存储单个素材 () ;
		}
	}
}

void Mapedit::LeftHitMapDown()
{
	if( graph.获得关卡数() == MAP_EDIT )/*在地图编辑器页面;*/
	{	
		bMouseLeftHitMapDownForCopy = true;
		if (TileBeginX == EMPTY_TILE || TileBeginY == EMPTY_TILE )
		{
				
		}
		// 获取mouse所指向的坐标值;
		POINT mouse ;	 GetCursorPos( &mouse ) ; 
		iMapEndX = mouse.x ;
		iMapEndY = mouse.y ;
		
		if (!iLeftHitMapBeginX)
		{
			iLeftHitMapBeginX = iMapEndX;
			iLeftHitMapBeginY = iMapEndY;
		}
		//在地图编辑区点击，地图与鼠标检测;
		if ( mouse.x > 0 && mouse.x < XSCREEN - 256 && mouse.y > 0 && mouse.y < YSCREEN - 64  )  //2016.6.13注释，加上这个限制用起来很不爽
		{	 //计算点击的地图列数与行数;
			  sMouseLeftHitMapDownX = ( (int)mouse.x - mRollScreenX ) / TILE_WIDE ;	
			  sMouseLeftHitMapDownY = ( (int)mouse.y - mRollScreenY ) / TILE_HIGH ;	
			  if (GetEditSave())return;//如果准备存储框选区域，则不能继续编辑;
			  bMouseLeftHitMap = true;
			 //存储用户点击的地图列数与行数;
			 //SaveCollide ( sMouseRightHitMapDownX , sMouseRightHitMapDownY ) ;
		}
	}
}

void Mapedit::RightHitMapUp ( )
{	
	if( graph.获得关卡数() == MAP_EDIT )/*在地图编辑器页面;*/
	{
		// 获取mouse所指向的坐标值;
		POINT mouse ;	 GetCursorPos( &mouse ) ; 
		//在地图编辑区点击，地图与鼠标检测;
		if ( mouse.x > 0 && mouse.x < XSCREEN - 256 && mouse.y > 0 && mouse.y < YSCREEN - 64  )  //2016.6.13注释，加上这个限制用起来很不爽
		{	 
			//计算点击的地图列数与行数;
			sMouseRightHitMapUpX = ( (int)mouse.x - mRollScreenX ) / TILE_WIDE ;	
			sMouseRightHitMapUpY = ( (int)mouse.y - mRollScreenY ) / TILE_HIGH ;	
			iMouseRightHitMap = PUSH_UP;
		
			if (GetEditSave())return;//如果准备存储框选区域，则不能继续编辑;

			if( sMouseRightHitMapDownX != sMouseRightHitMapUpX ||
				sMouseRightHitMapDownY != sMouseRightHitMapUpY  )//
			{
				填充地图();
				//存储用户点击的地图列数与行数;
				//SaveCollide ( sMouseRightHitMapUpX , sMouseRightHitMapUpY ) ;
			}
			else
			{
				if( EMPTY_TILE==TileXEnd || EMPTY_TILE==TileBeginX )
				{ 
					 RemoveMapTile () ;
				}
			}
		//	SetMicroMap();
			//mouse在地图上按下的标志,根据mouse点击区域动态存储数值;
			//if(TileBeginX <TileXEnd || TileBeginY <TileYEnd)
			//	存储框选素材 (); 
			//else
		//	存储单个素材 () ;
		}
	}
	
}
void Mapedit::RightHitMapDown ( )
{
	if( graph.获得关卡数() == MAP_EDIT )/*在地图编辑器页面;*/
	{	// 获取mouse所指向的坐标值;
		POINT mouse ;	 GetCursorPos( &mouse ) ; 
		 iRightHitMapBeginX = mouse.x  ;
		 iRightHitMapBeginY = mouse.y  ;

		//在地图编辑区点击，地图与鼠标检测;
		if ( mouse.x > 0 && mouse.x < XSCREEN - 256 && mouse.y > 0 && mouse.y < YSCREEN - 64  )	//2016.6.13注释，加上这个限制用起来很不爽
		{	 //计算点击的地图列数与行数;
			  sMouseRightHitMapDownX = ( (int)mouse.x - mRollScreenX ) / TILE_WIDE ;	
			  sMouseRightHitMapDownY = ( (int)mouse.y - mRollScreenY ) / TILE_HIGH ;	
			  iMouseRightHitMap = PUSH_DOWN;
			 //存储用户点击的地图列数与行数;
			 //SaveCollide ( sMouseRightHitMapDownX , sMouseRightHitMapDownY ) ;
			 
		}
	}
}

void Mapedit::SetMouseTileToEmpty()
{
	 TileXEnd = TileBeginX = EMPTY_TILE;
	 TileYEnd = TileBeginY = EMPTY_TILE;
}
//鼠标右键操作有效;
inline void Mapedit::存储框选素材 ()
{	
	//动态存储地图索引坐标对应的素材贴片编号/*数组越界检查*/
	if(	sMouseLeftHitMapDownX >= 0 && sMouseLeftHitMapDownX <= 99 && 
		sMouseLeftHitMapDownY >= 0 && sMouseLeftHitMapDownY <= 99 &&
		sMouseLeftHitMapUpX >= 0   && sMouseLeftHitMapUpX <= 99 &&
		sMouseLeftHitMapUpY >= 0   && sMouseLeftHitMapUpY <= 99   )	
	{	//地图右下角行列数 = （贴的行列数）+ 要绘制地图的起始行列数;
		short tnx =	TileXEnd - TileBeginX  + sMouseLeftHitMapDownX;
		short tny =	TileYEnd - TileBeginY  + sMouseLeftHitMapDownY;			
		int x,y,t;		

		//if( MessageBoxW(hWnd,L"是否设置该区域不能通过？",L"存储框选素材",MB_OKCANCEL)!=2 )
		//{//确认
		//	SetCollideState(true);
		//}
		//else
		//{
		//	SetCollideState(false);
		//}

		for ( y = sMouseLeftHitMapDownY ; y <= tny ;  y++ )	
		{	t = TileBeginX ;//内层循环每执行完毕，重置一次贴数位起始贴数。;
			for ( x = sMouseLeftHitMapDownX ; x <= tnx ;  x++ )				
			{				
				MapX [ 图层 ][ x ][ y ] = t;
				t++;
				SaveCollide ( x , y ) ; 
			}
		}
		
		for ( x = sMouseLeftHitMapDownX ; x <= tnx ;  x++ )
		{	t = TileBeginY ;
			for ( y = sMouseLeftHitMapDownY ; y <= tny ;  y++ )				
			{			
				MapY [ 图层 ][ x ][ y ] = t;
				t++;
				SaveCollide ( x , y ) ; 
			}
		}
	}
}
//鼠标右键操作有效;
void Mapedit::填充地图()
{
	if(	sMouseRightHitMapDownX >= 0 && sMouseRightHitMapDownX <= 99 &&
		sMouseRightHitMapDownY >= 0 && sMouseRightHitMapDownY <= 99 &&
		sMouseRightHitMapUpX >= 0 && sMouseRightHitMapUpX <= 99 &&
		sMouseRightHitMapUpY >= 0 && sMouseRightHitMapUpY <= 99 
	)//&&TileBeginX != EMPTY_TILE && TileBeginY != EMPTY_TILE 	 
	{			
		int bx ,sx , by , sy;
		//判断鼠标按下与松开时X轴谁大。;
		if( sMouseRightHitMapDownX > sMouseRightHitMapUpX )
		{
			bx = sMouseRightHitMapDownX;
			sx = sMouseRightHitMapUpX;
		}else 
		{
			bx = sMouseRightHitMapUpX;
			sx = sMouseRightHitMapDownX;
		}
		//判断鼠标按下与松开时Y轴谁大。;
		if( sMouseRightHitMapDownY > sMouseRightHitMapUpY )
		{
			by = sMouseRightHitMapDownY;
			sy = sMouseRightHitMapUpY;
		}else
		{
			by = sMouseRightHitMapUpY;
			sy = sMouseRightHitMapDownY;
		}
	//	wchar_t* txt;
	//	if(TileBeginX != EMPTY_TILE)
	//		txt = L"确定填充框选区域？";
	//	else txt = L"确定删除框选区域？";
	//	if( MessageBoxW(hWnd,txt,L"地图刷子",MB_OKCANCEL)!=2 )
	//	{
			for ( int x = sx ; x <= bx;  x++ )
			for ( int y = sy ; y <= by;  y++ )
			{
				MapX [ 图层 ][ x ][ y ] = TileBeginX ;
				MapY [ 图层 ][ x ][ y ] = TileBeginY ;
				SaveCollide ( x , y ) ;
				//精确可缩放小地图;
				int LeftX = MapX[图层][x][y] * TILE_WIDE;  int RightX  = MapX[图层][x][y] * TILE_WIDE + TILE_WIDE;
				int TopY  = MapY[图层][x][y] * TILE_HIGH;  int BottomY = MapY[图层][x][y] * TILE_HIGH + TILE_HIGH;
				MakeRect( LeftX , TopY ,RightX , BottomY );
				DDS[MicroMapZoom]->BltFast( x * TILE_WIDE  , y * TILE_HIGH , DDS[STile] , &rect ,  DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;
			}
	//	}
	}
}

void Mapedit::RemoveMapTile () 
{
		// 获取mouse所指向的坐标值;
	POINT mouse ;	 GetCursorPos( &mouse ) ; 

	//在地图编辑区点击，地图与鼠标检测;
	if ( graph.获得关卡数() == MAP_EDIT && /*在地图编辑器页面;*/
		 mouse.x > 0 && mouse.x < XSCREEN - 256 && 
		 mouse.y > 0 && mouse.y < YSCREEN - 64  )
		{	 //计算点击的地图列数与行数;
		  sMouseLeftHitMapDownX = ( mouse.x - mRollScreenX ) / TILE_WIDE ;	
		  sMouseLeftHitMapDownY = ( mouse.y - mRollScreenY ) / TILE_HIGH ;	}
	/*数组越界检查;*/
	if(	sMouseLeftHitMapDownX >= 0 && sMouseLeftHitMapDownX <= 99 && sMouseLeftHitMapDownY >= 0 && sMouseLeftHitMapDownY <= 99 )	 
	{	
	//	if( MessageBoxW(hWnd,L"确定删除mouse指向の图块和碰撞？",L"删除默认图层の图块和撤销碰撞",MB_OKCANCEL)!=2 )
	//	{//确认;
			MapX [ 图层 ][ sMouseLeftHitMapDownX ][ sMouseLeftHitMapDownY ] = EMPTY_TILE ; //EMPTY_TILE则不会绘制;
			MapY [ 图层 ][ sMouseLeftHitMapDownX ][ sMouseLeftHitMapDownY ] = EMPTY_TILE ;
			mCollideArray[ sMouseLeftHitMapDownX ][ sMouseLeftHitMapDownY ] = FALSE ;  // 撤销本区域碰撞检测;
	//	}

	}	
	// 撤销鼠标选定素材;
	TileBeginX = EMPTY_TILE ; TileBeginY = EMPTY_TILE ; 
	TileXEnd = EMPTY_TILE ; TileYEnd = EMPTY_TILE ;
}

void Mapedit::存储单个素材 () 
{
	if(	sMouseLeftHitMapDownX >= 0 && sMouseLeftHitMapDownX <= 99 &&	/*数组越界检查;*/
		sMouseLeftHitMapDownY >= 0 && sMouseLeftHitMapDownY <= 99  )	 
	{	
		MapX [ 图层 ][ sMouseLeftHitMapDownX ][ sMouseLeftHitMapDownY ] = TileBeginX ;
		MapY [ 图层 ][ sMouseLeftHitMapDownX ][ sMouseLeftHitMapDownY ] = TileBeginY ;
		SaveCollide ( sMouseLeftHitMapDownX , sMouseLeftHitMapDownY ) ;
	}
}

bool Mapedit::ReadMapFile () 
{
	//::OpenFile("MapNum",(LPOFSTRUCT)(&mCollideArray),NULL);
	TCHAR szCurrentDirectory[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH,szCurrentDirectory);
	SetCurrentDirectoryW(szCurrentDirectory);
	static	TCHAR szFileName[MAX_PATH];//取消static声明会造成DEBUG时打开文件对话框失败！;
	static	TCHAR szTitleName[MAX_PATH];//取消static声明0715
	HWND hwnd = GetForegroundWindow(); //获取前台窗口句柄。
	oFileOperatr.OpenFileInitialize(hwnd);
	if( oFileOperatr.BOpenFileDialogBox(hwnd, szFileName, szTitleName) )
	{
		
		//读取地图数据文件(文件路径，读或写，本进程独占本文件，子进程不可继承本剧柄，文件操作模式，文件属性和标志，是否使用模板句柄）;
	//	HANDLE mapFile =CreateFile( szFileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_READONLY,NULL);
	//	DWORD dwBytesRead;
		//ReadFile( mapFile , &MapX , sizeof(MapX) , &dwBytesRead , NULL );
		//ReadFile( mapFile , &MapY , sizeof(MapY) , &dwBytesRead , NULL );	
	//	ReadFile( mapFile , &mCollideArray , sizeof(mCollideArray) , &dwBytesRead , NULL );
	//	CloseHandle(mapFile);		

		bMouseLeftHitMap = false;	//防止打开地图后，鼠标状态是按下！

		FILE * f =_wfopen(szTitleName,L"r+");
		if (f)
		{ 	
			fread(MapX,sizeof(int),30000,f);
			fread(MapY,sizeof(int),30000,f);
			fread(mCollideArray,sizeof(bool),10000,f);
			//for (int y=0 ;y<MAPY_GRID;y++)
			//{
			//	for (int x=0 ;x<MAPX_GRID;x++)
			//	{
			//		fscanf(f,"%d",MapX[0][x][y]);
			//		fscanf(f," %d ",MapY[0][x][y]);
			//		
			//	}
			//	fprintf(f,"\n");
			//}
			wcscpy_s(szMapName,szTitleName);
			SetMicroMap();
			SetMonster(SPIRIT_POOL_MAX);

			fclose(f);
			return true;
		}
	}
	return false;
}
/* 
  文件操作模式;
CREATE_ALWAYS 如果指向的文件存在，则重建该文件，清除文件内容和属性；如果不存在，则新建一个文件;
REATE_NEW 新建文件，如果文件已经存在，则返回失败;
OPEN_ALWAYS 如果文件存在则打开文件；如果不存在，则等于CREATE_NEW;
OPEN_EXISTING 打开存在的文件，如果文件不存在，则删除文件;
TRUNCATE_EXISTING 打开已存在的文件，并把内容清空，文件大小变为0;
  文件属性
FILE_ATTRIBUTE_READONLY					只读文件;
FILE_ATTRIBUTE_HIDDEN					隐藏文件;
FILE_ATTRIBUTE_SYSTEM					系统文件;		
FILE_ATTRIBUTE_DIRECTORY				       
FILE_ATTRIBUTE_ARCHIVE					     
FILE_ATTRIBUTE_DEVICE					存档文件;     
FILE_ATTRIBUTE_NORMAL					不含有其他文件属性，只能单独使用;			
FILE_ATTRIBUTE_TEMPORARY				临时文件;        
FILE_ATTRIBUTE_SPARSE_FILE				
FILE_ATTRIBUTE_REPARSE_POINT      
FILE_ATTRIBUTE_COMPRESSED         
FILE_ATTRIBUTE_OFFLINE					离线存储文件;
FILE_ATTRIBUTE_NOT_CONTENT_INDEXED		没有使用内容索引服务;
FILE_ATTRIBUTE_ENCRYPTED				加密文件;
FILE_ATTRIBUTE_VIRTUAL					
  文件操作标志;
FILE_FLAG_WRITE_THROUGH				存储文件时，直接对磁盘进行操作，不经过缓存;
FILE_FLAG_OVERLAPPED				已异步IO方式创建可打开文件;
FILE_FLAG_NO_BUFFERING				不使用系统缓存，caching，不同于硬件缓存;
FILE_FLAG_RANDOM_ACCESS				随机存储;
FILE_FLAG_SEQUENTIAL_SCAN			文件从头到尾是连续的;
FILE_FLAG_DELETE_ON_CLOSE			如果文件句柄全部关闭，则删除文件;
FILE_FLAG_BACKUP_SEMANTICS			打开和创建文件是为了进行备份和恢复操作;
FILE_FLAG_POSIX_SEMANTICS			按照POSIX规则存取
FILE_FLAG_OPEN_REPARSE_POINT		系统将禁止NTFS文件系统的 再解析 行为;
FILE_FLAG_OPEN_NO_RECALL			远程存储;
FILE_FLAG_FIRST_PIPE_INSTANCE		
*/ 
#include <fstream>
#include <sstream> 
void Mapedit::SaveMapFile () 
{
	static TCHAR szFileName[MAX_PATH];
	static TCHAR szTitleName[MAX_PATH];// = TEXT ("save/")
	HWND hwnd = GetForegroundWindow(); //获取前台窗口句柄。
	oFileOperatr.SaveFileInitialize();
	if( oFileOperatr.BSaveFileDialogBox(hwnd, szFileName, szTitleName) )
	{
		//存取地图数据文件;
	//	HANDLE mapFile =CreateFile( szFileName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	//	DWORD dwBytesWritten;
	//	WriteFile( mapFile , &MapX , sizeof(MapX) , &dwBytesWritten , NULL );
	//	WriteFile( mapFile , &MapY , sizeof(MapY) , &dwBytesWritten , NULL );
	//	WriteFile( mapFile , &mCollideArray , sizeof(mCollideArray) , &dwBytesWritten , NULL );
	//	CloseHandle( mapFile ); 
		wchar_t buffer [MAX_PATH];
		wsprintf(buffer,L"%s",szFileName);
		FILE * f =_wfopen(szFileName,L"w+");
		if (f) 
		{ 		
			fwrite(MapX,sizeof(int),30000,f);
			fwrite(MapY,sizeof(int),30000,f);
			fwrite(mCollideArray,sizeof(bool),10000,f);
		//	输出文本用;
		//	for (int y=0 ;y<MAPY_GRID;y++)
		//	{
		//		for (int x=0 ;x<MAPX_GRID;x++)
		//		{
		//			fprintf(f,"%d %d ",MapX[0][x][y],MapY[0][x][y]);
		//		}
		//		fprintf(f,"\n");
		//	}
		}
		fclose(f);
	}
}

void Mapedit::GetBigBrush ()
{	//用刷子刷整个地图;
	for ( int mx = 0 ; mx < 80 ; mx ++ )
	for ( int my = 0 ; my < 80 ; my ++ ) 
	{	MapX [ 图层 ][ mx ][ my ] = TileBeginX ;
		MapY [ 图层 ][ mx ][ my ] = TileBeginY ;  }
	//全部不能通过;
	if( m_bCollideState == TRUE ) 
	{	for ( int x = 0 ; x < 80 ; x ++  )
		for ( int y = 0 ; y < 80 ; y ++  ) 
		  mCollideArray[x][y] = TRUE  ;		  
	}
	else//全部能够通过;
	{	for ( int x = 0 ; x < 80 ; x ++  )
		for ( int y = 0 ; y < 80 ; y ++  ) 
		  mCollideArray[x][y] = FALSE  ;		  
	}
}


void Mapedit::RefreshMap( int MapXAdd , int MapYAdd )
{
	//MakeRect( 0+ mRollScreenX , 0+ mRollScreenY ,XSCREEN+ mRollScreenX , YSCREEN+ mRollScreenY );
	//DDS[SBuffer]->BltFast( 0  + mRollScreenX , 0 + mRollScreenY, DDS[BackMap] ,
	//						&rect , DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT );

	graph.Blt( 0 , 0 ,BackMap,SBuffer,DDBLTFAST_NOCOLORKEY| DDBLTFAST_WAIT);
	//计时器在main.cpp初始化时间;
	if ( timeCount.GetNowTime() > 0.001 ) //如果计时器大于X秒;
	{	//更新动画;
		oPlayer.TankMove(); 	
		//oPlayer.JiJaMove(); 
		timeCount.ResetTime();//计时器重新设置开始时间为当前时间。;
	}			
}
void Mapedit::SetMicroMap()
{
	//填充背景
	DDBLTFX ddBltFx;
	ddBltFx.dwSize =sizeof(DDBLTFX);//ddBltFx.dwFillPixel=0;
	ddBltFx.dwFillColor =RGB(0,0,0);//黑色背景
	DDS[MicroMap]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	DDS[MicroMapZoom]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	int LeftX , RightX , TopY , BottomY ;

	RECT rcRectSrc;
	SetRect(&rcRectSrc, 0, 0, 32, 32);
	
	//循环绘制小地图;		 
	for( int mtc = 0 ; mtc < 3 ; mtc ++ )
		for( int mtx = 0 ; mtx < MAPX_GRID ; mtx++ )
			for( int mty = 0 ; mty < MAPY_GRID ; mty++ ) 
			{	
				if( MapX[mtc][mtx][mty] == EMPTY_TILE || MapY[mtc][mtx][mty] == EMPTY_TILE)
				{ continue; }
				//精确可缩放小地图;
				LeftX = MapX[mtc][mtx][mty] * TILE_WIDE;  RightX  = MapX[mtc][mtx][mty] * TILE_WIDE + TILE_WIDE;
				TopY  = MapY[mtc][mtx][mty] * TILE_HIGH;  BottomY = MapY[mtc][mtx][mty] * TILE_HIGH + TILE_HIGH;
				MakeRect( LeftX , TopY ,RightX , BottomY );
				DDS[MicroMapZoom]->BltFast( mtx * TILE_WIDE  , mty * TILE_HIGH , DDS[STile] , &rect ,  DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;
				//小地图，TILE_WIDE后加的是贴的间隔，可实现透明化;
				LeftX = MapX[mtc][mtx][mty] * TILE_WIDE + 10  ;  RightX  = MapX[mtc][mtx][mty] * TILE_WIDE + 12 ;
				TopY  = MapY[mtc][mtx][mty] * TILE_HIGH + 10 ;  BottomY = MapY[mtc][mtx][mty] * TILE_HIGH + 12 ;
				MakeRect( LeftX , TopY ,RightX , BottomY );
				DDS[MicroMap]->BltFast( mtx * 2  , mty * 2 , DDS[STile] , &rect ,  DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;	
			} 
}
void Mapedit::ShowMicroMap ()
{
//	MakeRect( 0 , 0 ,200 , 200);
//	DDS[SBuffer]->BltFast( 32 ,50, DDS[MicroMap] ,   &rect , DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;	

	RECT rcRectSrc,rcRectDest;
	SetRect(&rcRectSrc, 0, 0, 3200, 3200);
	SetRect(&rcRectDest, 32 ,32, 532, 532);
	DDS[SBuffer]->Blt( &rcRectDest ,DDS[MicroMapZoom] , &rcRectSrc, DDBLT_KEYSRC|DDBLT_WAIT, NULL) ;
		//显示小地图上坦克移动;
	//	MakeRect(11,11,15,15);//绘制坦克位图中的一小块区域;
	//	DDS[SBuffer]->BltFast( -mRollScreenX / 16 + 64 ,-mRollScreenY / 19 + 64, //精灵位置模拟不精确，需重新设计方案;
	//		DDS[MM2TankB] , &rect , DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT ) ;
}

void Mapedit::InitBigMap()
{
	//图层显示控制;
	int tc1 (0) , tc2 (0) ; 
	//tcX为循环变量tc1为循环初始值，tc2为循环结束值;
	if( 图层 == 0 ) { tc1 = 0 ; tc2 = 1 ; } 
	if( 图层 == 1 ) { tc1 = 1 ; tc2 = 2 ; }
	if( 图层 == 2 ) { tc1 = 2 ; tc2 = 3 ; }
	if( mShowAllMapLayer )  { tc1 = 0 ; tc2 = 3 ; }

	//循环绘制地图;		
	int map_x_coordinate_tile_number = XSCREEN / TILE_WIDE + 2;//比屏幕大一圈
	int map_y_coordinate_tile_number = YSCREEN / TILE_HIGH + 2;
//	assert(map_x_coordinate_tile_number<100);	2016.5.21注释
//	assert(map_y_coordinate_tile_number<100);
	for( int mtc = tc1 ; mtc < tc2 ; mtc ++ )
	{
		for( int mtx = 1 ; mtx <= map_x_coordinate_tile_number; mtx++ )
		{
			for( int mty = 1 ; mty <= map_y_coordinate_tile_number; mty++ )		
			{	
				if( MapX[mtc][mtx][mty]==EMPTY_TILE )//是否空贴
				{	continue;
				}
				MakeRect(	MapX[mtc][mtx-1][mty-1] * TILE_WIDE , 
							MapY[mtc][mtx-1][mty-1] * TILE_HIGH , 
							MapX[mtc][mtx-1][mty-1] * TILE_WIDE + TILE_WIDE , 
							MapY[mtc][mtx-1][mty-1] * TILE_HIGH + TILE_HIGH		);
				DDS[BigMap]->BltFast( mtx*TILE_WIDE + mRollScreenX , mty*TILE_HIGH + mRollScreenY, DDS[STile] , &rect , DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT );
			}
		}
	}	
}
void Mapedit::SetBigMap()
{
	int map_x_coordinate_tile_number = ( XSCREEN - mRollScreenX ) / TILE_WIDE;
	int map_y_coordinate_tile_number = ( YSCREEN - mRollScreenY ) / TILE_HIGH;
	int begin_x_coordinate_tile_number = map_x_coordinate_tile_number - XSCREEN  / TILE_WIDE;
	int begin_y_coordinate_tile_number = map_y_coordinate_tile_number - YSCREEN  / TILE_HIGH;
	if (begin_x_coordinate_tile_number<1) begin_x_coordinate_tile_number=1;
	if (begin_y_coordinate_tile_number<1) begin_y_coordinate_tile_number=1;

	if ( RollScreenFace == UP    )//Y轴上方最小值;
	{ 
	}	

	if ( RollScreenFace == DOWN   )//Y轴下方最大值;
	{  
	}	

	if ( RollScreenFace == LEFT  )//X轴左方最小值;
	{ 

	}

	if ( RollScreenFace == RIGHT ) 
	{ 

	}  

}
#if 0
void Mapedit::ShowMap ( int 贴宽 , int 贴高 , int MapXAdd , int MapYAdd )
{
	int _left = TILE_WIDE;
	int _top = TILE_HIGH;
	int _right = XSCREEN;
	int _bottom = YSCREEN;

	if ( RollScreenFace == UP    )//Y轴上方最小值;
	{ 
	}	

	if ( RollScreenFace == DOWN   )//Y轴下方最大值;
	{  
	}	

	if ( RollScreenFace == LEFT  )//X轴左方最小值;
	{ 

	}

	if ( RollScreenFace == RIGHT ) //
	{ 

	}  


	MakeRect( _left , _top ,_right , _bottom); 
	DDS[SBuffer]->BltFast( 0 + mRollScreenX ,0 + mRollScreenY, DDS[BigMap] ,  &rect , DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT ) ;	
	
	//在第0层与第1层之间显示坦克精灵;计时器在main.cpp初始化时间;
	if (timeCount.GetNowTime() > 0.001) //如果计时器大于X秒;
	{	//更新动画;;
		oPlayer.TankMove(); 	
		oPlayer.JiJaMove(); 
		timeCount.ResetTime();//计时器重新设置开始时间为当前时间。;
	}
}
#endif
#if 1
void Mapedit::ShowMap ( int 贴宽 , int 贴高 , int MapXAdd , int MapYAdd )
{			
	//图层显示控制;
	int tc1 (0) , tc2 (0) ; 
	//tcX为循环变量tc1为循环初始值，tc2为循环结束值;
	if( 图层 == 0 ) { tc1 = 0 ; tc2 = 1 ; } 
	if( 图层 == 1 ) { tc1 = 1 ; tc2 = 2 ; }
	if( 图层 == 2 ) { tc1 = 2 ; tc2 = 3 ; }
	if( mShowAllMapLayer )  { tc1 = 0 ; tc2 = 3 ; }

	//循环绘制地图;		
		int map_x_coordinate_tile_number = ( XSCREEN - mRollScreenX + MapXAdd ) / 贴宽;
		int map_y_coordinate_tile_number = ( YSCREEN - mRollScreenY + MapYAdd ) / 贴高;
		int begin_x_coordinate_tile_number = map_x_coordinate_tile_number - XSCREEN  / 贴宽;
		int begin_y_coordinate_tile_number = map_y_coordinate_tile_number - YSCREEN  / 贴高;
		if (begin_x_coordinate_tile_number<1) begin_x_coordinate_tile_number=1;
		if (begin_y_coordinate_tile_number<1) begin_y_coordinate_tile_number=1;
	for( int mtc = tc1 ; mtc < tc2 ; mtc ++ )
	{
		//在第0层与第1层之间显示坦克精灵;计时器在main.cpp初始化时间;
		if ( mtc ==2)
		{	
			if (graph.获得关卡数() == GAME_MAP )
			{	//更新动画;;
				oPlayer.TankMove(); 
			}
		
			if (timeCount.GetNowTime() > 0.001) //如果计时器大于X秒;
			{
				oSpiritManager.MoveAlloSpirit();
			}
			
			timeCount.ResetTime();//计时器重新设置开始时间为当前时间。;
		}	
		for( int mtx = begin_x_coordinate_tile_number ; mtx < map_x_coordinate_tile_number; mtx++ )
		{
			for( int mty = begin_y_coordinate_tile_number ; mty < map_y_coordinate_tile_number; mty++ )		
			{	
				//	if(mtx>100)MessageBoxW(hWnd,L"地图绘制错误",L"mtx值超出100",MB_OK);
				if( MapX[mtc][mtx][mty]==EMPTY_TILE )//是否空贴
				{	continue;
				}

				MakeRect( MapX[mtc][mtx][mty] * 贴宽 , MapY[mtc][mtx][mty] * 贴高 , MapX[mtc][mtx][mty] * 贴宽 + 贴宽 , MapY[mtc][mtx][mty] * 贴高 + 贴高 );
				DDS[SBuffer]->BltFast( mtx*贴宽 + mRollScreenX , mty*贴高 + mRollScreenY, DDS[STile] , &rect , DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT );
			}
		}
	}	
}
#endif
void Mapedit::显示碰撞点()
{
	for( int mtx= 1 ; mtx < ( XSCREEN - 256 - mRollScreenX ) / TILE_WIDE  ; mtx++ )
	for( int mty= 1 ; mty < ( YSCREEN - 64  - mRollScreenY ) / TILE_HIGH  ; mty++ )
	{		
		if(mCollideArray[mtx][mty]) //绘制碰撞点标记;
		DDS[SBuffer]->BltFast( mtx * TILE_WIDE  + mRollScreenX , mty * TILE_HIGH + mRollScreenY , DDS[SXbmp] , 
							   NULL , DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;		
	}
}

void Mapedit::MapEditBottomLine()
{
	//绘制地图编辑器有效区域底部界线（直线）
	HDC hdc2 ;	DDS[SBuffer]->GetDC(&hdc2);
	HPEN hpen = CreatePen(PS_SOLID,1,RGB(250,0,0));
	HPEN old_pen = (HPEN)SelectObject(hdc2,hpen);
	int x=0; //x=y=0;
	MoveToEx(hdc2,x,MAP_EDIT_AREA_Y,NULL);
	LineTo  (hdc2,MAP_EDIT_AREA_X ,MAP_EDIT_AREA_Y);
	DDS[SBuffer]->ReleaseDC(hdc2);
}

void Mapedit::CollideCheck( int nReverseRollScreen )
{
	//if ( m_bRollScreenState == true )
		SetRollScreen ( nReverseRollScreen ) ;//碰撞地图边界检测	
		bCollide = false;
	//地图与坦克碰撞检测;	
	for( int mtx = 1 ; mtx < ( XSCREEN - mRollScreenX ) / TILE_WIDE ; mtx++ )
	for( int mty = 1 ; mty < ( YSCREEN - mRollScreenY ) / TILE_HIGH ; mty++ )
	{	static const int zoom_cs = 5;
		if ( mCollideArray[mtx][mty]	 /*锁定碰撞范围; */			  &&
			 oPlayer.GetTankXY( X ) + TILE_WIDE + -zoom_cs > mtx * TILE_WIDE + mRollScreenX  && 
			 oPlayer.GetTankXY( X ) + zoom_cs  < mtx * TILE_WIDE + mRollScreenX + TILE_WIDE  &&
			 oPlayer.GetTankXY( Y ) + zoom_cs  < mty * TILE_HIGH + mRollScreenY + TILE_HIGH  &&	
			 oPlayer.GetTankXY( Y ) + TILE_HIGH + -zoom_cs > mty * TILE_HIGH + mRollScreenY	 ) 	
			{	bCollide = true;
				if( oPlayer.GetTankFace() == UP    ) 
				{ 
					 mRollScreenY -= nReverseRollScreen ; 
					 oPlayer.SetPlayerMapY(+nReverseRollScreen);
				} // 退后X像素;
				if( oPlayer.GetTankFace() == DOWN  ) 
				{ 
					 mRollScreenY += nReverseRollScreen ; 
					 oPlayer.SetPlayerMapY(-nReverseRollScreen);
				} // 退后X像素;
				if( oPlayer.GetTankFace() == LEFT  ) 
				{ 
					 mRollScreenX -= nReverseRollScreen ; 
					 oPlayer.SetPlayerMapX(+nReverseRollScreen);
				} // 退后X像素;
				if( oPlayer.GetTankFace() == RIGHT ) 
				{ 
					 mRollScreenX += nReverseRollScreen ;
					 oPlayer.SetPlayerMapX(-nReverseRollScreen); 
				} // 退后X像素;		 		
			}//m_bRollScreenState = false ;
		
	}// m_bRollScreenState = true ;
		
		static short bc;
		if( bCollide == true ) bc = 0;//防止子弹飞歪;
		else bc = PLAYER_MOVE_SPEED;		
		oPlayer.ShootLoop(bc);//射击动画;
}

/**************************************************
* 函数介绍：SetRollScreen,设置移动滚屏的速度和 碰撞地图边界检测（20140815注释掉了）;
* 输入参数：moveSpeed ,移动速度,值域在1-30之间;
* 返回参数：无;
**************************************************/
inline void Mapedit::SetRollScreen ( int moveSpeed )
{	   	//没碰撞的方向		  不超过 边界;	
	if ( RollScreenFace == UP    )// &&  mRollScreenY < 350   )//Y轴上方最小值;
	{ 
		mRollScreenY += moveSpeed ; //累加	;
		oPlayer.SetPlayerMapY(-moveSpeed);  
	}	

	if ( RollScreenFace == DOWN  )// &&  mRollScreenY > -2500 )//Y轴下方最大值;
	{ 
		mRollScreenY -= moveSpeed ; 
		oPlayer.SetPlayerMapY(+moveSpeed);  
	}	

	if ( RollScreenFace == LEFT  )// &&  mRollScreenX < 650   )//X轴左方最小值;
	{ 
		mRollScreenX += moveSpeed ; 
		oPlayer.SetPlayerMapX(-moveSpeed); 
	}

	if ( RollScreenFace == RIGHT )// &&  mRollScreenX > -2000 ) 
	{ 
		mRollScreenX -= moveSpeed ; 
		oPlayer.SetPlayerMapX(+moveSpeed);  
	}  

	RollScreenFace = 0 ; //停止滚屏  ;
}

bool Mapedit::MouseIsAtMapEditArae()
{
	POINT mouse ;	 GetCursorPos( &mouse ) ;

	if ( mouse.x > 0 && mouse.x < XSCREEN - BMPMAPWIDE && mouse.y > 0 && mouse.y < YSCREEN - 64  )
	{	
		return true;
	}
	else
	{
		sMouseLeftHitMapUpX = sMouseLeftHitMapUpX = sMouseLeftHitMapUpY = sMouseLeftHitMapUpY =
		sMouseLeftHitMapDownX = sMouseLeftHitMapDownX = sMouseLeftHitMapDownY = sMouseLeftHitMapDownY = EMPTY; 
		return false;
	}
		
}

bool Mapedit::MouseIsNoAtTileArae()
{
	// 获取鼠标所指向的坐标值;
	POINT mouse ;	 GetCursorPos( &mouse ) ;

	if ( mouse.x > XSCREEN - BMPMAPWIDE && mouse.x < XSCREEN && 
		 mouse.y > 0 && mouse.y < BMPMAPHIGH ) 
		return true;
	else
		return false;
}

bool Mapedit::IsNoSelectSingleTile()
{
	if( TileBeginX==TileXEnd && TileBeginY==TileYEnd  )
		return true;
	else
		return false;
}

void Mapedit::SaveMouseSelectRectangleToFile()
{
	//if (!MouseIsAtMapEditArae())
	//{ return;
	//}
	//动态存储地图索引坐标对应的素材贴片编号/*数组越界检查*/
	if(	sMouseLeftHitMapDownX<0 || sMouseLeftHitMapDownY<0 || sMouseLeftHitMapUpX<0 || sMouseLeftHitMapUpY<0 )
	{ return;
	}
	
	if (abs(sMouseLeftHitMapDownX - sMouseLeftHitMapUpX)<2 || abs(sMouseLeftHitMapDownY - sMouseLeftHitMapUpY)<2 )
	{ return;
	}

 	if( MessageBoxW(hWnd,L"是否复制选中区域？",L"复制框选地图",MB_OKCANCEL)==2 )
 		return;
//	static TCHAR file_name[MAX_PATH];
//	static TCHAR title_name[MAX_PATH];// = TEXT ("save/")
//	HWND hwnd = GetForegroundWindow(); //获取前台窗口句柄。
//	oFileOperatr.SaveFileInitialize();
//	if( oFileOperatr.BSaveFileDialogBox(hwnd, file_name, title_name) )
//	{	
	
	//	FILE * f =_wfopen(file_name,L"w+");
	//	if (f) 
	//	{ 	//	输出文本用;
			int x_max,y_max,x_min,y_min;
			if (sMouseLeftHitMapDownY < sMouseLeftHitMapUpY)
			{	
				y_min = sMouseLeftHitMapDownY;
				y_max = sMouseLeftHitMapUpY;
			} 
			else
			{	
				y_max = sMouseLeftHitMapDownY;
				y_min = sMouseLeftHitMapUpY;
			}
			if (sMouseLeftHitMapDownX < sMouseLeftHitMapUpX)
			{	
				x_min = sMouseLeftHitMapDownX;
				x_max = sMouseLeftHitMapUpX;
			} 
			else
			{	
				x_max = sMouseLeftHitMapDownX;
				x_min = sMouseLeftHitMapUpX;
			}
/*2016.5.21注释
			int cy=y_min, cx=x_min;
			mMultiArray.resize(extents[MAP_LAYER][x_max-x_min+1][y_max-y_min+1]);
			typedef MultiArray::index index;
			int layer=0;
			for (int layer=0;layer<MAP_LAYER;layer++)
			{
				for ( int ay = 0,cy=y_min;cy<=y_max;ay++,cy++)
				{
					for ( int ax = 0,cx=x_min;cx<=x_max;ax++,cx++)
					{
					//	fprintf(f,"%d %d ",MapX[0][cx][cy],MapY[0][cx][cy]);
						mMultiArray[layer][ax][ay].mx = MapX[layer][cx][cy];
						mMultiArray[layer][ax][ay].my =	MapY[layer][cx][cy];	
						mMultiArray[0][ax][ay].cs = mCollideArray[cx][cy] ;	
					}
			//		fprintf(f,"\n");
				}
			}	*/
	//	}
	//	fclose(f);
	//}
}

void Mapedit::DrawMouseRightKeySelectRect()
{
	if( m_EditSave )
	{ return; }
	//绘制框选轨迹矩形;	
	if( iMouseRightHitMap == PUSH_DOWN)//按下;
	{
		//if (!MouseIsAtMapEditArae())
		//{
		//	iMouseRightHitMap = PUSH_NOT;
		//	sMouseRightHitMapDownX = sMouseRightHitMapUpX =
		//	sMouseRightHitMapDownY = sMouseRightHitMapUpY = -1;		
		//	return;
		//}

		POINT mouse ;	 GetCursorPos( &mouse ) ; 			
		if ( oPlayer.GetTankFace() == UP     &&  mRollScreenY < 350   )//Y轴上方最小值;
		{ 
			iSelectPathY+= MAP_EDIT_MOVE_SPEED ; //累加	;
		}else	
		if ( oPlayer.GetTankFace() == DOWN   &&  mRollScreenY > -2500 )//Y轴下方最大值;
		{ 
			iSelectPathY -= MAP_EDIT_MOVE_SPEED ; 
		}else	
		if ( oPlayer.GetTankFace() == LEFT   &&  mRollScreenX < 650   )//X轴左方最小值;
		{ 
			iSelectPathX += MAP_EDIT_MOVE_SPEED ; 
		}else
		if ( oPlayer.GetTankFace() == RIGHT  &&  mRollScreenX > -2000 ) 
		{ 
			iSelectPathX -= MAP_EDIT_MOVE_SPEED ;  
		}  
			HDC hdc ;	DDS[SBuffer]->GetDC(&hdc);
			//SelectObject(hdc,CreatePen(PS_DOT,0,RGB(255,0,0)));
			//SelectObject(hdc,CreateSolidBrush(NULL_BRUSH));
			//Rectangle(hdc,iRightHitMapBeginX+iSelectPathX,iRightHitMapBeginY+iSelectPathY,mouse.x,mouse.y);

			SetBkMode(hdc,TRANSPARENT);
			SelectObject(hdc,CreatePen(PS_SOLID,1,RGB(250,0,0)));
			MoveToEx(hdc , iRightHitMapBeginX+iSelectPathX , iRightHitMapBeginY+iSelectPathY , NULL);
			LineTo  (hdc,mouse.x , iRightHitMapBeginY+iSelectPathY);
			LineTo  (hdc,mouse.x,mouse.y);
			LineTo  (hdc,iRightHitMapBeginX+iSelectPathX,mouse.y);
			LineTo  (hdc,iRightHitMapBeginX+iSelectPathX ,iRightHitMapBeginY+iSelectPathY);
			DDS[SBuffer]->ReleaseDC(hdc);
	}
	else
	{
		if (!bMouseLeftHitMapDownForCopy)
		iSelectPathX=iSelectPathY=0;
	}
}

void Mapedit::DrawMouseLeftKeySelectRect()
{
	//绘制框选轨迹矩形;	
	if( !m_EditSave )
	{ return; }
		
	if (bMouseLeftHitMapDownForCopy)		
	{
		POINT mouse ;	 GetCursorPos( &mouse ) ; 			
		if ( oPlayer.GetTankFace() == UP     &&  mRollScreenY < 350   )//Y轴上方最小值;
		{ 
			iSelectPathY+= MAP_EDIT_MOVE_SPEED ; //累加	;
		}else	
		if ( oPlayer.GetTankFace() == DOWN   &&  mRollScreenY > -2500 )//Y轴下方最大值;
		{ 
			iSelectPathY -= MAP_EDIT_MOVE_SPEED ; 
		}else	
		if ( oPlayer.GetTankFace() == LEFT   &&  mRollScreenX < 650   )//X轴左方最小值;
		{ 
			iSelectPathX += MAP_EDIT_MOVE_SPEED ; 
		}else
		if ( oPlayer.GetTankFace() == RIGHT  &&  mRollScreenX > -2000 ) 
		{ 
			iSelectPathX -= MAP_EDIT_MOVE_SPEED ;  
		}  
			HDC hdc ;	DDS[SBuffer]->GetDC(&hdc);
			SetBkMode(hdc,TRANSPARENT);
			SelectObject(hdc,CreatePen(PS_SOLID,1,RGB(0,0,255)));
			MoveToEx(hdc , iLeftHitMapBeginX+iSelectPathX , iLeftHitMapBeginY+iSelectPathY , NULL);
			LineTo  (hdc,mouse.x , iLeftHitMapBeginY+iSelectPathY);
			LineTo  (hdc,mouse.x,mouse.y);
			LineTo  (hdc,iLeftHitMapBeginX+iSelectPathX,mouse.y);
			LineTo  (hdc,iLeftHitMapBeginX+iSelectPathX ,iLeftHitMapBeginY+iSelectPathY);			
			DDS[SBuffer]->ReleaseDC(hdc);
	}
	else
	{	//防止左键和左键框选操作冲突;
		if (iMouseRightHitMap != PUSH_DOWN)
		{	
			iSelectPathX=iSelectPathY=0;
		}
	}
}

void Mapedit::ResetMapEdit()
{
	m_EditSave = false;
	mShowAllMapLayer = true;
	m_bTinyMap = false;
	大刷子 = false;
	m_bCollideState = false;
	图层 = 0 ;
	SetMouseTileToEmpty();
	iSelectPathX=iSelectPathY=0;
}