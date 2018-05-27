#include "main.h"
#include "FileOperate.h"
#include "SpecialEfficiency.h"
#include "TimeCount.h"
#include "Player.h"
#include "Spirit.h"
Mapedit oMapedit;

Mapedit::Mapedit()
{
	bMouseLeftHitMap   = false ; //mouse�ڵ�ͼ�����µ�״̬ ��Ĭ��0Ϊʲô��û����;
	iMouseRightHitMap  = PUSH_NOT ;
	TileBeginX = TileBeginY = EMPTY_TILE ;
	TileXEnd   = TileYEnd   = EMPTY_TILE ;
	sMouseLeftHitMapDownX = sMouseLeftHitMapDownY = 0 ;
	RollScreenFace = 0 ; //Ĭ�ϲ�����
	mRollScreenX = mRollScreenY  = 0 ; //(1)�����ƶ�(2)�����ƶ�(3)�����ƶ�(4)�����ƶ�;

	//��ʼ����ͼ����;
		memset( MapX, EMPTY_TILE, sizeof(int)*3*MAPX_GRID*MAPX_GRID ); 
		memset( MapY, EMPTY_TILE, sizeof(int)*3*MAPY_GRID*MAPY_GRID ); 

	m_bCollideState = false ; //Ĭ�Ϲر� ��ײ����;
	��ˢ��   = false ; //Ĭ�Ϲر�ˢ��;
	m_bRollScreenState = true ;
	//Ĭ����ʾȫͼ��;
	mShowAllMapLayer = true ;
	ͼ�� = 0 ; 

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
{	//  ����Խ���飬���Խ���򲻴洢����;
	if (x >= 0 && x <= 99 && y >= 0 && y <= 99)
	{
		if( m_bCollideState == FALSE ) 
			mCollideArray[x][y] = FALSE ;
		else 
			mCollideArray[x][y] = TRUE  ;
	}
}

void Mapedit::��ʾ�ز� ()
{
	// ��ȡmouse��ָ�������ֵ;
	POINT mouse ;	 GetCursorPos( &mouse ) ; 

	// ���Ƶ�ͼ�༭�����ز�;
	DDS[SBuffer]->BltFast( XSCREEN - 256  , 0 ,
						   DDS[STile] , NULL , DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;
	// ���Ƹ���mouse������ͼ;
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
	// ��ȡmouse��ָ�������ֵ;
	POINT mouse ;	 GetCursorPos( &mouse ) ; 

	//LONG window_y_move = 8;
	//RECT rc ; GetWindowRect(hWnd,&rc);
	////�ز���mouse��⣬������ز������;
	//if ( mouse.x > rc.right - �õ��ز����ź�ߴ�X() && 
	//	 mouse.x < rc.right && 
	//	 mouse.y - window_y_move > rc.top && 
	//	 mouse.y - window_y_move < rc.top + �õ��ز����ź�ߴ�Y() ) {
	//	  //�����û������Ƭ������������
	//	  TileXEnd = ( mouse.x - ( rc.right - �õ��ز����ź�ߴ�X() ) ) / ( TILE_WIDE/�õ��������ű���X() ) ;
	//	  TileYEnd = ( mouse.y - window_y_move ) / ( TILE_HIGH/�õ��������ű���Y() ) ;	}

	////�ز���mouse��⣬������ز����ɿ�mouse;
	if ( MouseIsNoAtTileArae() == true ) 
	{	 //�����û������Ƭ������������;
		  TileXEnd = ( mouse.x - ( XSCREEN - 256 ) ) / TILE_WIDE ;
		  TileYEnd = ( mouse.y  ) / TILE_HIGH ;	
	}
	bMouseLeftHitMap   = false ;//��ֹû��Click Map�������ͼ����ȴ����갴��״̬;
}

void Mapedit::LeftHitTileArea ()
{	
	if (m_EditSave)
	{
		return;
	}
	// ��ȡmouse��ָ�������ֵ;
	POINT mouse ;	 GetCursorPos( &mouse ) ; 

	////�ز���mouse��⣬������ز������;
	if ( mouse.x > XSCREEN - 256 &&  mouse.x < XSCREEN && 
		 mouse.y > 0 && mouse.y < 704 ) {	 
		  //�����û������Ƭ������������;
		  TileBeginX = ( mouse.x - ( XSCREEN - 256 ) ) / TILE_WIDE ;
		  TileBeginY = ( mouse.y ) / TILE_HIGH ;	}
}
void Mapedit::RightHitTileArea ()
{	// ��ȡmouse��ָ�������ֵ;
	POINT mouse ;	 GetCursorPos( &mouse ) ; 

	////�ز���mouse��⣬������ز������;
	if ( mouse.x > XSCREEN - 256 &&  mouse.x < XSCREEN && 
		mouse.y > 0 && mouse.y < 704 ) {	 
			SetMouseTileToEmpty();	}
}

void Mapedit::LeftHitMapUp()
{
	iLeftHitMapBeginX = iLeftHitMapBeginY = 0;
	if( graph.��ùؿ���() == MAP_EDIT )/*�ڵ�ͼ�༭��ҳ��;*/
	{
		bMouseLeftHitMapDownForCopy = false;
		POINT mouse ;	 GetCursorPos( &mouse ) ; 
		//�ڵ�ͼ�༭���������ͼ��mouse���;
		if ( mouse.x > 0 && mouse.x < XSCREEN - 256 && mouse.y > 0 && mouse.y < YSCREEN - 64  )
		{	 
			//�������ĵ�ͼ����������;
			sMouseLeftHitMapUpX = ( (int)mouse.x - mRollScreenX ) / TILE_WIDE ;	
			sMouseLeftHitMapUpY = ( (int)mouse.y - mRollScreenY ) / TILE_HIGH ;	
			bMouseLeftHitMap = false;

			if (GetEditSave())
			{
				if (sMouseLeftHitMapUpX == sMouseLeftHitMapDownX && sMouseLeftHitMapUpY == sMouseLeftHitMapDownY)
				{	//2016.5.21ע��
				/*	if( MessageBoxW(hWnd,L"ȷ����¡��ѡ������",L"���ƿ�ѡ����",MB_OKCANCEL)!=2 )
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
									//��ȷ������С��ͼ;
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
				return;//���׼���洢��ѡ�������ܼ����༭;
			}

			//�洢�û�����ĵ�ͼ����������;
			if (TileBeginX == EMPTY_TILE || TileBeginY == EMPTY_TILE )
			{
			//	SaveCollide ( sMouseLeftHitMapUpX , sMouseLeftHitMapUpY ) ;
				if (!m_bCollideState)
				{ return;
				}			
			}
			
			//
			if(TileBeginX <TileXEnd || TileBeginY <TileYEnd)
				�洢��ѡ�ز� (); 
		//		SetMicroMap();ÿ��ȫ���洢̫��������ֲܾ����£�Ӧ�ò��Ῠ��;
			//else
			//	�洢�����ز� () ;
		}
	}
}

void Mapedit::LeftHitMapDown()
{
	if( graph.��ùؿ���() == MAP_EDIT )/*�ڵ�ͼ�༭��ҳ��;*/
	{	
		bMouseLeftHitMapDownForCopy = true;
		if (TileBeginX == EMPTY_TILE || TileBeginY == EMPTY_TILE )
		{
				
		}
		// ��ȡmouse��ָ�������ֵ;
		POINT mouse ;	 GetCursorPos( &mouse ) ; 
		iMapEndX = mouse.x ;
		iMapEndY = mouse.y ;
		
		if (!iLeftHitMapBeginX)
		{
			iLeftHitMapBeginX = iMapEndX;
			iLeftHitMapBeginY = iMapEndY;
		}
		//�ڵ�ͼ�༭���������ͼ�������;
		if ( mouse.x > 0 && mouse.x < XSCREEN - 256 && mouse.y > 0 && mouse.y < YSCREEN - 64  )  //2016.6.13ע�ͣ�������������������ܲ�ˬ
		{	 //�������ĵ�ͼ����������;
			  sMouseLeftHitMapDownX = ( (int)mouse.x - mRollScreenX ) / TILE_WIDE ;	
			  sMouseLeftHitMapDownY = ( (int)mouse.y - mRollScreenY ) / TILE_HIGH ;	
			  if (GetEditSave())return;//���׼���洢��ѡ�������ܼ����༭;
			  bMouseLeftHitMap = true;
			 //�洢�û�����ĵ�ͼ����������;
			 //SaveCollide ( sMouseRightHitMapDownX , sMouseRightHitMapDownY ) ;
		}
	}
}

void Mapedit::RightHitMapUp ( )
{	
	if( graph.��ùؿ���() == MAP_EDIT )/*�ڵ�ͼ�༭��ҳ��;*/
	{
		// ��ȡmouse��ָ�������ֵ;
		POINT mouse ;	 GetCursorPos( &mouse ) ; 
		//�ڵ�ͼ�༭���������ͼ�������;
		if ( mouse.x > 0 && mouse.x < XSCREEN - 256 && mouse.y > 0 && mouse.y < YSCREEN - 64  )  //2016.6.13ע�ͣ�������������������ܲ�ˬ
		{	 
			//�������ĵ�ͼ����������;
			sMouseRightHitMapUpX = ( (int)mouse.x - mRollScreenX ) / TILE_WIDE ;	
			sMouseRightHitMapUpY = ( (int)mouse.y - mRollScreenY ) / TILE_HIGH ;	
			iMouseRightHitMap = PUSH_UP;
		
			if (GetEditSave())return;//���׼���洢��ѡ�������ܼ����༭;

			if( sMouseRightHitMapDownX != sMouseRightHitMapUpX ||
				sMouseRightHitMapDownY != sMouseRightHitMapUpY  )//
			{
				����ͼ();
				//�洢�û�����ĵ�ͼ����������;
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
			//mouse�ڵ�ͼ�ϰ��µı�־,����mouse�������̬�洢��ֵ;
			//if(TileBeginX <TileXEnd || TileBeginY <TileYEnd)
			//	�洢��ѡ�ز� (); 
			//else
		//	�洢�����ز� () ;
		}
	}
	
}
void Mapedit::RightHitMapDown ( )
{
	if( graph.��ùؿ���() == MAP_EDIT )/*�ڵ�ͼ�༭��ҳ��;*/
	{	// ��ȡmouse��ָ�������ֵ;
		POINT mouse ;	 GetCursorPos( &mouse ) ; 
		 iRightHitMapBeginX = mouse.x  ;
		 iRightHitMapBeginY = mouse.y  ;

		//�ڵ�ͼ�༭���������ͼ�������;
		if ( mouse.x > 0 && mouse.x < XSCREEN - 256 && mouse.y > 0 && mouse.y < YSCREEN - 64  )	//2016.6.13ע�ͣ�������������������ܲ�ˬ
		{	 //�������ĵ�ͼ����������;
			  sMouseRightHitMapDownX = ( (int)mouse.x - mRollScreenX ) / TILE_WIDE ;	
			  sMouseRightHitMapDownY = ( (int)mouse.y - mRollScreenY ) / TILE_HIGH ;	
			  iMouseRightHitMap = PUSH_DOWN;
			 //�洢�û�����ĵ�ͼ����������;
			 //SaveCollide ( sMouseRightHitMapDownX , sMouseRightHitMapDownY ) ;
			 
		}
	}
}

void Mapedit::SetMouseTileToEmpty()
{
	 TileXEnd = TileBeginX = EMPTY_TILE;
	 TileYEnd = TileBeginY = EMPTY_TILE;
}
//����Ҽ�������Ч;
inline void Mapedit::�洢��ѡ�ز� ()
{	
	//��̬�洢��ͼ���������Ӧ���ز���Ƭ���/*����Խ����*/
	if(	sMouseLeftHitMapDownX >= 0 && sMouseLeftHitMapDownX <= 99 && 
		sMouseLeftHitMapDownY >= 0 && sMouseLeftHitMapDownY <= 99 &&
		sMouseLeftHitMapUpX >= 0   && sMouseLeftHitMapUpX <= 99 &&
		sMouseLeftHitMapUpY >= 0   && sMouseLeftHitMapUpY <= 99   )	
	{	//��ͼ���½������� = ��������������+ Ҫ���Ƶ�ͼ����ʼ������;
		short tnx =	TileXEnd - TileBeginX  + sMouseLeftHitMapDownX;
		short tny =	TileYEnd - TileBeginY  + sMouseLeftHitMapDownY;			
		int x,y,t;		

		//if( MessageBoxW(hWnd,L"�Ƿ����ø�������ͨ����",L"�洢��ѡ�ز�",MB_OKCANCEL)!=2 )
		//{//ȷ��
		//	SetCollideState(true);
		//}
		//else
		//{
		//	SetCollideState(false);
		//}

		for ( y = sMouseLeftHitMapDownY ; y <= tny ;  y++ )	
		{	t = TileBeginX ;//�ڲ�ѭ��ÿִ����ϣ�����һ������λ��ʼ������;
			for ( x = sMouseLeftHitMapDownX ; x <= tnx ;  x++ )				
			{				
				MapX [ ͼ�� ][ x ][ y ] = t;
				t++;
				SaveCollide ( x , y ) ; 
			}
		}
		
		for ( x = sMouseLeftHitMapDownX ; x <= tnx ;  x++ )
		{	t = TileBeginY ;
			for ( y = sMouseLeftHitMapDownY ; y <= tny ;  y++ )				
			{			
				MapY [ ͼ�� ][ x ][ y ] = t;
				t++;
				SaveCollide ( x , y ) ; 
			}
		}
	}
}
//����Ҽ�������Ч;
void Mapedit::����ͼ()
{
	if(	sMouseRightHitMapDownX >= 0 && sMouseRightHitMapDownX <= 99 &&
		sMouseRightHitMapDownY >= 0 && sMouseRightHitMapDownY <= 99 &&
		sMouseRightHitMapUpX >= 0 && sMouseRightHitMapUpX <= 99 &&
		sMouseRightHitMapUpY >= 0 && sMouseRightHitMapUpY <= 99 
	)//&&TileBeginX != EMPTY_TILE && TileBeginY != EMPTY_TILE 	 
	{			
		int bx ,sx , by , sy;
		//�ж���갴�����ɿ�ʱX��˭��;
		if( sMouseRightHitMapDownX > sMouseRightHitMapUpX )
		{
			bx = sMouseRightHitMapDownX;
			sx = sMouseRightHitMapUpX;
		}else 
		{
			bx = sMouseRightHitMapUpX;
			sx = sMouseRightHitMapDownX;
		}
		//�ж���갴�����ɿ�ʱY��˭��;
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
	//		txt = L"ȷ������ѡ����";
	//	else txt = L"ȷ��ɾ����ѡ����";
	//	if( MessageBoxW(hWnd,txt,L"��ͼˢ��",MB_OKCANCEL)!=2 )
	//	{
			for ( int x = sx ; x <= bx;  x++ )
			for ( int y = sy ; y <= by;  y++ )
			{
				MapX [ ͼ�� ][ x ][ y ] = TileBeginX ;
				MapY [ ͼ�� ][ x ][ y ] = TileBeginY ;
				SaveCollide ( x , y ) ;
				//��ȷ������С��ͼ;
				int LeftX = MapX[ͼ��][x][y] * TILE_WIDE;  int RightX  = MapX[ͼ��][x][y] * TILE_WIDE + TILE_WIDE;
				int TopY  = MapY[ͼ��][x][y] * TILE_HIGH;  int BottomY = MapY[ͼ��][x][y] * TILE_HIGH + TILE_HIGH;
				MakeRect( LeftX , TopY ,RightX , BottomY );
				DDS[MicroMapZoom]->BltFast( x * TILE_WIDE  , y * TILE_HIGH , DDS[STile] , &rect ,  DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;
			}
	//	}
	}
}

void Mapedit::RemoveMapTile () 
{
		// ��ȡmouse��ָ�������ֵ;
	POINT mouse ;	 GetCursorPos( &mouse ) ; 

	//�ڵ�ͼ�༭���������ͼ�������;
	if ( graph.��ùؿ���() == MAP_EDIT && /*�ڵ�ͼ�༭��ҳ��;*/
		 mouse.x > 0 && mouse.x < XSCREEN - 256 && 
		 mouse.y > 0 && mouse.y < YSCREEN - 64  )
		{	 //�������ĵ�ͼ����������;
		  sMouseLeftHitMapDownX = ( mouse.x - mRollScreenX ) / TILE_WIDE ;	
		  sMouseLeftHitMapDownY = ( mouse.y - mRollScreenY ) / TILE_HIGH ;	}
	/*����Խ����;*/
	if(	sMouseLeftHitMapDownX >= 0 && sMouseLeftHitMapDownX <= 99 && sMouseLeftHitMapDownY >= 0 && sMouseLeftHitMapDownY <= 99 )	 
	{	
	//	if( MessageBoxW(hWnd,L"ȷ��ɾ��mouseָ���ͼ�����ײ��",L"ɾ��Ĭ��ͼ���ͼ��ͳ�����ײ",MB_OKCANCEL)!=2 )
	//	{//ȷ��;
			MapX [ ͼ�� ][ sMouseLeftHitMapDownX ][ sMouseLeftHitMapDownY ] = EMPTY_TILE ; //EMPTY_TILE�򲻻����;
			MapY [ ͼ�� ][ sMouseLeftHitMapDownX ][ sMouseLeftHitMapDownY ] = EMPTY_TILE ;
			mCollideArray[ sMouseLeftHitMapDownX ][ sMouseLeftHitMapDownY ] = FALSE ;  // ������������ײ���;
	//	}

	}	
	// �������ѡ���ز�;
	TileBeginX = EMPTY_TILE ; TileBeginY = EMPTY_TILE ; 
	TileXEnd = EMPTY_TILE ; TileYEnd = EMPTY_TILE ;
}

void Mapedit::�洢�����ز� () 
{
	if(	sMouseLeftHitMapDownX >= 0 && sMouseLeftHitMapDownX <= 99 &&	/*����Խ����;*/
		sMouseLeftHitMapDownY >= 0 && sMouseLeftHitMapDownY <= 99  )	 
	{	
		MapX [ ͼ�� ][ sMouseLeftHitMapDownX ][ sMouseLeftHitMapDownY ] = TileBeginX ;
		MapY [ ͼ�� ][ sMouseLeftHitMapDownX ][ sMouseLeftHitMapDownY ] = TileBeginY ;
		SaveCollide ( sMouseLeftHitMapDownX , sMouseLeftHitMapDownY ) ;
	}
}

bool Mapedit::ReadMapFile () 
{
	//::OpenFile("MapNum",(LPOFSTRUCT)(&mCollideArray),NULL);
	TCHAR szCurrentDirectory[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH,szCurrentDirectory);
	SetCurrentDirectoryW(szCurrentDirectory);
	static	TCHAR szFileName[MAX_PATH];//ȡ��static���������DEBUGʱ���ļ��Ի���ʧ�ܣ�;
	static	TCHAR szTitleName[MAX_PATH];//ȡ��static����0715
	HWND hwnd = GetForegroundWindow(); //��ȡǰ̨���ھ����
	oFileOperatr.OpenFileInitialize(hwnd);
	if( oFileOperatr.BOpenFileDialogBox(hwnd, szFileName, szTitleName) )
	{
		
		//��ȡ��ͼ�����ļ�(�ļ�·��������д�������̶�ռ���ļ����ӽ��̲��ɼ̳б�������ļ�����ģʽ���ļ����Ժͱ�־���Ƿ�ʹ��ģ������;
	//	HANDLE mapFile =CreateFile( szFileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_READONLY,NULL);
	//	DWORD dwBytesRead;
		//ReadFile( mapFile , &MapX , sizeof(MapX) , &dwBytesRead , NULL );
		//ReadFile( mapFile , &MapY , sizeof(MapY) , &dwBytesRead , NULL );	
	//	ReadFile( mapFile , &mCollideArray , sizeof(mCollideArray) , &dwBytesRead , NULL );
	//	CloseHandle(mapFile);		

		bMouseLeftHitMap = false;	//��ֹ�򿪵�ͼ�����״̬�ǰ��£�

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
  �ļ�����ģʽ;
CREATE_ALWAYS ���ָ����ļ����ڣ����ؽ����ļ�������ļ����ݺ����ԣ���������ڣ����½�һ���ļ�;
REATE_NEW �½��ļ�������ļ��Ѿ����ڣ��򷵻�ʧ��;
OPEN_ALWAYS ����ļ���������ļ�����������ڣ������CREATE_NEW;
OPEN_EXISTING �򿪴��ڵ��ļ�������ļ������ڣ���ɾ���ļ�;
TRUNCATE_EXISTING ���Ѵ��ڵ��ļ�������������գ��ļ���С��Ϊ0;
  �ļ�����
FILE_ATTRIBUTE_READONLY					ֻ���ļ�;
FILE_ATTRIBUTE_HIDDEN					�����ļ�;
FILE_ATTRIBUTE_SYSTEM					ϵͳ�ļ�;		
FILE_ATTRIBUTE_DIRECTORY				       
FILE_ATTRIBUTE_ARCHIVE					     
FILE_ATTRIBUTE_DEVICE					�浵�ļ�;     
FILE_ATTRIBUTE_NORMAL					�����������ļ����ԣ�ֻ�ܵ���ʹ��;			
FILE_ATTRIBUTE_TEMPORARY				��ʱ�ļ�;        
FILE_ATTRIBUTE_SPARSE_FILE				
FILE_ATTRIBUTE_REPARSE_POINT      
FILE_ATTRIBUTE_COMPRESSED         
FILE_ATTRIBUTE_OFFLINE					���ߴ洢�ļ�;
FILE_ATTRIBUTE_NOT_CONTENT_INDEXED		û��ʹ��������������;
FILE_ATTRIBUTE_ENCRYPTED				�����ļ�;
FILE_ATTRIBUTE_VIRTUAL					
  �ļ�������־;
FILE_FLAG_WRITE_THROUGH				�洢�ļ�ʱ��ֱ�ӶԴ��̽��в���������������;
FILE_FLAG_OVERLAPPED				���첽IO��ʽ�����ɴ��ļ�;
FILE_FLAG_NO_BUFFERING				��ʹ��ϵͳ���棬caching����ͬ��Ӳ������;
FILE_FLAG_RANDOM_ACCESS				����洢;
FILE_FLAG_SEQUENTIAL_SCAN			�ļ���ͷ��β��������;
FILE_FLAG_DELETE_ON_CLOSE			����ļ����ȫ���رգ���ɾ���ļ�;
FILE_FLAG_BACKUP_SEMANTICS			�򿪺ʹ����ļ���Ϊ�˽��б��ݺͻָ�����;
FILE_FLAG_POSIX_SEMANTICS			����POSIX�����ȡ
FILE_FLAG_OPEN_REPARSE_POINT		ϵͳ����ֹNTFS�ļ�ϵͳ�� �ٽ��� ��Ϊ;
FILE_FLAG_OPEN_NO_RECALL			Զ�̴洢;
FILE_FLAG_FIRST_PIPE_INSTANCE		
*/ 
#include <fstream>
#include <sstream> 
void Mapedit::SaveMapFile () 
{
	static TCHAR szFileName[MAX_PATH];
	static TCHAR szTitleName[MAX_PATH];// = TEXT ("save/")
	HWND hwnd = GetForegroundWindow(); //��ȡǰ̨���ھ����
	oFileOperatr.SaveFileInitialize();
	if( oFileOperatr.BSaveFileDialogBox(hwnd, szFileName, szTitleName) )
	{
		//��ȡ��ͼ�����ļ�;
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
		//	����ı���;
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
{	//��ˢ��ˢ������ͼ;
	for ( int mx = 0 ; mx < 80 ; mx ++ )
	for ( int my = 0 ; my < 80 ; my ++ ) 
	{	MapX [ ͼ�� ][ mx ][ my ] = TileBeginX ;
		MapY [ ͼ�� ][ mx ][ my ] = TileBeginY ;  }
	//ȫ������ͨ��;
	if( m_bCollideState == TRUE ) 
	{	for ( int x = 0 ; x < 80 ; x ++  )
		for ( int y = 0 ; y < 80 ; y ++  ) 
		  mCollideArray[x][y] = TRUE  ;		  
	}
	else//ȫ���ܹ�ͨ��;
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
	//��ʱ����main.cpp��ʼ��ʱ��;
	if ( timeCount.GetNowTime() > 0.001 ) //�����ʱ������X��;
	{	//���¶���;
		oPlayer.TankMove(); 	
		//oPlayer.JiJaMove(); 
		timeCount.ResetTime();//��ʱ���������ÿ�ʼʱ��Ϊ��ǰʱ�䡣;
	}			
}
void Mapedit::SetMicroMap()
{
	//��䱳��
	DDBLTFX ddBltFx;
	ddBltFx.dwSize =sizeof(DDBLTFX);//ddBltFx.dwFillPixel=0;
	ddBltFx.dwFillColor =RGB(0,0,0);//��ɫ����
	DDS[MicroMap]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	DDS[MicroMapZoom]->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	int LeftX , RightX , TopY , BottomY ;

	RECT rcRectSrc;
	SetRect(&rcRectSrc, 0, 0, 32, 32);
	
	//ѭ������С��ͼ;		 
	for( int mtc = 0 ; mtc < 3 ; mtc ++ )
		for( int mtx = 0 ; mtx < MAPX_GRID ; mtx++ )
			for( int mty = 0 ; mty < MAPY_GRID ; mty++ ) 
			{	
				if( MapX[mtc][mtx][mty] == EMPTY_TILE || MapY[mtc][mtx][mty] == EMPTY_TILE)
				{ continue; }
				//��ȷ������С��ͼ;
				LeftX = MapX[mtc][mtx][mty] * TILE_WIDE;  RightX  = MapX[mtc][mtx][mty] * TILE_WIDE + TILE_WIDE;
				TopY  = MapY[mtc][mtx][mty] * TILE_HIGH;  BottomY = MapY[mtc][mtx][mty] * TILE_HIGH + TILE_HIGH;
				MakeRect( LeftX , TopY ,RightX , BottomY );
				DDS[MicroMapZoom]->BltFast( mtx * TILE_WIDE  , mty * TILE_HIGH , DDS[STile] , &rect ,  DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;
				//С��ͼ��TILE_WIDE��ӵ������ļ������ʵ��͸����;
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
		//��ʾС��ͼ��̹���ƶ�;
	//	MakeRect(11,11,15,15);//����̹��λͼ�е�һС������;
	//	DDS[SBuffer]->BltFast( -mRollScreenX / 16 + 64 ,-mRollScreenY / 19 + 64, //����λ��ģ�ⲻ��ȷ����������Ʒ���;
	//		DDS[MM2TankB] , &rect , DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT ) ;
}

void Mapedit::InitBigMap()
{
	//ͼ����ʾ����;
	int tc1 (0) , tc2 (0) ; 
	//tcXΪѭ������tc1Ϊѭ����ʼֵ��tc2Ϊѭ������ֵ;
	if( ͼ�� == 0 ) { tc1 = 0 ; tc2 = 1 ; } 
	if( ͼ�� == 1 ) { tc1 = 1 ; tc2 = 2 ; }
	if( ͼ�� == 2 ) { tc1 = 2 ; tc2 = 3 ; }
	if( mShowAllMapLayer )  { tc1 = 0 ; tc2 = 3 ; }

	//ѭ�����Ƶ�ͼ;		
	int map_x_coordinate_tile_number = XSCREEN / TILE_WIDE + 2;//����Ļ��һȦ
	int map_y_coordinate_tile_number = YSCREEN / TILE_HIGH + 2;
//	assert(map_x_coordinate_tile_number<100);	2016.5.21ע��
//	assert(map_y_coordinate_tile_number<100);
	for( int mtc = tc1 ; mtc < tc2 ; mtc ++ )
	{
		for( int mtx = 1 ; mtx <= map_x_coordinate_tile_number; mtx++ )
		{
			for( int mty = 1 ; mty <= map_y_coordinate_tile_number; mty++ )		
			{	
				if( MapX[mtc][mtx][mty]==EMPTY_TILE )//�Ƿ����
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

	if ( RollScreenFace == UP    )//Y���Ϸ���Сֵ;
	{ 
	}	

	if ( RollScreenFace == DOWN   )//Y���·����ֵ;
	{  
	}	

	if ( RollScreenFace == LEFT  )//X������Сֵ;
	{ 

	}

	if ( RollScreenFace == RIGHT ) 
	{ 

	}  

}
#if 0
void Mapedit::ShowMap ( int ���� , int ���� , int MapXAdd , int MapYAdd )
{
	int _left = TILE_WIDE;
	int _top = TILE_HIGH;
	int _right = XSCREEN;
	int _bottom = YSCREEN;

	if ( RollScreenFace == UP    )//Y���Ϸ���Сֵ;
	{ 
	}	

	if ( RollScreenFace == DOWN   )//Y���·����ֵ;
	{  
	}	

	if ( RollScreenFace == LEFT  )//X������Сֵ;
	{ 

	}

	if ( RollScreenFace == RIGHT ) //
	{ 

	}  


	MakeRect( _left , _top ,_right , _bottom); 
	DDS[SBuffer]->BltFast( 0 + mRollScreenX ,0 + mRollScreenY, DDS[BigMap] ,  &rect , DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT ) ;	
	
	//�ڵ�0�����1��֮����ʾ̹�˾���;��ʱ����main.cpp��ʼ��ʱ��;
	if (timeCount.GetNowTime() > 0.001) //�����ʱ������X��;
	{	//���¶���;;
		oPlayer.TankMove(); 	
		oPlayer.JiJaMove(); 
		timeCount.ResetTime();//��ʱ���������ÿ�ʼʱ��Ϊ��ǰʱ�䡣;
	}
}
#endif
#if 1
void Mapedit::ShowMap ( int ���� , int ���� , int MapXAdd , int MapYAdd )
{			
	//ͼ����ʾ����;
	int tc1 (0) , tc2 (0) ; 
	//tcXΪѭ������tc1Ϊѭ����ʼֵ��tc2Ϊѭ������ֵ;
	if( ͼ�� == 0 ) { tc1 = 0 ; tc2 = 1 ; } 
	if( ͼ�� == 1 ) { tc1 = 1 ; tc2 = 2 ; }
	if( ͼ�� == 2 ) { tc1 = 2 ; tc2 = 3 ; }
	if( mShowAllMapLayer )  { tc1 = 0 ; tc2 = 3 ; }

	//ѭ�����Ƶ�ͼ;		
		int map_x_coordinate_tile_number = ( XSCREEN - mRollScreenX + MapXAdd ) / ����;
		int map_y_coordinate_tile_number = ( YSCREEN - mRollScreenY + MapYAdd ) / ����;
		int begin_x_coordinate_tile_number = map_x_coordinate_tile_number - XSCREEN  / ����;
		int begin_y_coordinate_tile_number = map_y_coordinate_tile_number - YSCREEN  / ����;
		if (begin_x_coordinate_tile_number<1) begin_x_coordinate_tile_number=1;
		if (begin_y_coordinate_tile_number<1) begin_y_coordinate_tile_number=1;
	for( int mtc = tc1 ; mtc < tc2 ; mtc ++ )
	{
		//�ڵ�0�����1��֮����ʾ̹�˾���;��ʱ����main.cpp��ʼ��ʱ��;
		if ( mtc ==2)
		{	
			if (graph.��ùؿ���() == GAME_MAP )
			{	//���¶���;;
				oPlayer.TankMove(); 
			}
		
			if (timeCount.GetNowTime() > 0.001) //�����ʱ������X��;
			{
				oSpiritManager.MoveAlloSpirit();
			}
			
			timeCount.ResetTime();//��ʱ���������ÿ�ʼʱ��Ϊ��ǰʱ�䡣;
		}	
		for( int mtx = begin_x_coordinate_tile_number ; mtx < map_x_coordinate_tile_number; mtx++ )
		{
			for( int mty = begin_y_coordinate_tile_number ; mty < map_y_coordinate_tile_number; mty++ )		
			{	
				//	if(mtx>100)MessageBoxW(hWnd,L"��ͼ���ƴ���",L"mtxֵ����100",MB_OK);
				if( MapX[mtc][mtx][mty]==EMPTY_TILE )//�Ƿ����
				{	continue;
				}

				MakeRect( MapX[mtc][mtx][mty] * ���� , MapY[mtc][mtx][mty] * ���� , MapX[mtc][mtx][mty] * ���� + ���� , MapY[mtc][mtx][mty] * ���� + ���� );
				DDS[SBuffer]->BltFast( mtx*���� + mRollScreenX , mty*���� + mRollScreenY, DDS[STile] , &rect , DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT );
			}
		}
	}	
}
#endif
void Mapedit::��ʾ��ײ��()
{
	for( int mtx= 1 ; mtx < ( XSCREEN - 256 - mRollScreenX ) / TILE_WIDE  ; mtx++ )
	for( int mty= 1 ; mty < ( YSCREEN - 64  - mRollScreenY ) / TILE_HIGH  ; mty++ )
	{		
		if(mCollideArray[mtx][mty]) //������ײ����;
		DDS[SBuffer]->BltFast( mtx * TILE_WIDE  + mRollScreenX , mty * TILE_HIGH + mRollScreenY , DDS[SXbmp] , 
							   NULL , DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;		
	}
}

void Mapedit::MapEditBottomLine()
{
	//���Ƶ�ͼ�༭����Ч����ײ����ߣ�ֱ�ߣ�
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
		SetRollScreen ( nReverseRollScreen ) ;//��ײ��ͼ�߽���	
		bCollide = false;
	//��ͼ��̹����ײ���;	
	for( int mtx = 1 ; mtx < ( XSCREEN - mRollScreenX ) / TILE_WIDE ; mtx++ )
	for( int mty = 1 ; mty < ( YSCREEN - mRollScreenY ) / TILE_HIGH ; mty++ )
	{	static const int zoom_cs = 5;
		if ( mCollideArray[mtx][mty]	 /*������ײ��Χ; */			  &&
			 oPlayer.GetTankXY( X ) + TILE_WIDE + -zoom_cs > mtx * TILE_WIDE + mRollScreenX  && 
			 oPlayer.GetTankXY( X ) + zoom_cs  < mtx * TILE_WIDE + mRollScreenX + TILE_WIDE  &&
			 oPlayer.GetTankXY( Y ) + zoom_cs  < mty * TILE_HIGH + mRollScreenY + TILE_HIGH  &&	
			 oPlayer.GetTankXY( Y ) + TILE_HIGH + -zoom_cs > mty * TILE_HIGH + mRollScreenY	 ) 	
			{	bCollide = true;
				if( oPlayer.GetTankFace() == UP    ) 
				{ 
					 mRollScreenY -= nReverseRollScreen ; 
					 oPlayer.SetPlayerMapY(+nReverseRollScreen);
				} // �˺�X����;
				if( oPlayer.GetTankFace() == DOWN  ) 
				{ 
					 mRollScreenY += nReverseRollScreen ; 
					 oPlayer.SetPlayerMapY(-nReverseRollScreen);
				} // �˺�X����;
				if( oPlayer.GetTankFace() == LEFT  ) 
				{ 
					 mRollScreenX -= nReverseRollScreen ; 
					 oPlayer.SetPlayerMapX(+nReverseRollScreen);
				} // �˺�X����;
				if( oPlayer.GetTankFace() == RIGHT ) 
				{ 
					 mRollScreenX += nReverseRollScreen ;
					 oPlayer.SetPlayerMapX(-nReverseRollScreen); 
				} // �˺�X����;		 		
			}//m_bRollScreenState = false ;
		
	}// m_bRollScreenState = true ;
		
		static short bc;
		if( bCollide == true ) bc = 0;//��ֹ�ӵ�����;
		else bc = PLAYER_MOVE_SPEED;		
		oPlayer.ShootLoop(bc);//�������;
}

/**************************************************
* �������ܣ�SetRollScreen,�����ƶ��������ٶȺ� ��ײ��ͼ�߽��⣨20140815ע�͵��ˣ�;
* ���������moveSpeed ,�ƶ��ٶ�,ֵ����1-30֮��;
* ���ز�������;
**************************************************/
inline void Mapedit::SetRollScreen ( int moveSpeed )
{	   	//û��ײ�ķ���		  ������ �߽�;	
	if ( RollScreenFace == UP    )// &&  mRollScreenY < 350   )//Y���Ϸ���Сֵ;
	{ 
		mRollScreenY += moveSpeed ; //�ۼ�	;
		oPlayer.SetPlayerMapY(-moveSpeed);  
	}	

	if ( RollScreenFace == DOWN  )// &&  mRollScreenY > -2500 )//Y���·����ֵ;
	{ 
		mRollScreenY -= moveSpeed ; 
		oPlayer.SetPlayerMapY(+moveSpeed);  
	}	

	if ( RollScreenFace == LEFT  )// &&  mRollScreenX < 650   )//X������Сֵ;
	{ 
		mRollScreenX += moveSpeed ; 
		oPlayer.SetPlayerMapX(-moveSpeed); 
	}

	if ( RollScreenFace == RIGHT )// &&  mRollScreenX > -2000 ) 
	{ 
		mRollScreenX -= moveSpeed ; 
		oPlayer.SetPlayerMapX(+moveSpeed);  
	}  

	RollScreenFace = 0 ; //ֹͣ����  ;
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
	// ��ȡ�����ָ�������ֵ;
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
	//��̬�洢��ͼ���������Ӧ���ز���Ƭ���/*����Խ����*/
	if(	sMouseLeftHitMapDownX<0 || sMouseLeftHitMapDownY<0 || sMouseLeftHitMapUpX<0 || sMouseLeftHitMapUpY<0 )
	{ return;
	}
	
	if (abs(sMouseLeftHitMapDownX - sMouseLeftHitMapUpX)<2 || abs(sMouseLeftHitMapDownY - sMouseLeftHitMapUpY)<2 )
	{ return;
	}

 	if( MessageBoxW(hWnd,L"�Ƿ���ѡ������",L"���ƿ�ѡ��ͼ",MB_OKCANCEL)==2 )
 		return;
//	static TCHAR file_name[MAX_PATH];
//	static TCHAR title_name[MAX_PATH];// = TEXT ("save/")
//	HWND hwnd = GetForegroundWindow(); //��ȡǰ̨���ھ����
//	oFileOperatr.SaveFileInitialize();
//	if( oFileOperatr.BSaveFileDialogBox(hwnd, file_name, title_name) )
//	{	
	
	//	FILE * f =_wfopen(file_name,L"w+");
	//	if (f) 
	//	{ 	//	����ı���;
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
/*2016.5.21ע��
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
	//���ƿ�ѡ�켣����;	
	if( iMouseRightHitMap == PUSH_DOWN)//����;
	{
		//if (!MouseIsAtMapEditArae())
		//{
		//	iMouseRightHitMap = PUSH_NOT;
		//	sMouseRightHitMapDownX = sMouseRightHitMapUpX =
		//	sMouseRightHitMapDownY = sMouseRightHitMapUpY = -1;		
		//	return;
		//}

		POINT mouse ;	 GetCursorPos( &mouse ) ; 			
		if ( oPlayer.GetTankFace() == UP     &&  mRollScreenY < 350   )//Y���Ϸ���Сֵ;
		{ 
			iSelectPathY+= MAP_EDIT_MOVE_SPEED ; //�ۼ�	;
		}else	
		if ( oPlayer.GetTankFace() == DOWN   &&  mRollScreenY > -2500 )//Y���·����ֵ;
		{ 
			iSelectPathY -= MAP_EDIT_MOVE_SPEED ; 
		}else	
		if ( oPlayer.GetTankFace() == LEFT   &&  mRollScreenX < 650   )//X������Сֵ;
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
	//���ƿ�ѡ�켣����;	
	if( !m_EditSave )
	{ return; }
		
	if (bMouseLeftHitMapDownForCopy)		
	{
		POINT mouse ;	 GetCursorPos( &mouse ) ; 			
		if ( oPlayer.GetTankFace() == UP     &&  mRollScreenY < 350   )//Y���Ϸ���Сֵ;
		{ 
			iSelectPathY+= MAP_EDIT_MOVE_SPEED ; //�ۼ�	;
		}else	
		if ( oPlayer.GetTankFace() == DOWN   &&  mRollScreenY > -2500 )//Y���·����ֵ;
		{ 
			iSelectPathY -= MAP_EDIT_MOVE_SPEED ; 
		}else	
		if ( oPlayer.GetTankFace() == LEFT   &&  mRollScreenX < 650   )//X������Сֵ;
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
	{	//��ֹ����������ѡ������ͻ;
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
	��ˢ�� = false;
	m_bCollideState = false;
	ͼ�� = 0 ;
	SetMouseTileToEmpty();
	iSelectPathX=iSelectPathY=0;
}