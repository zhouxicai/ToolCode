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

//��ʾ��Ϸ��ͼ;
void Mapedit::GameMapUpdate()
{		
	ShowMap ( TILE_WIDE , TILE_HIGH , 0 , 0 ) ;
	CollideCheck ( PLAYER_MOVE_SPEED ) ;

	if (m_bTinyMap) 
	{
		ShowMicroMap ( ) ; //��M�������ƿ���	
	}
	//��Ч;
	if(cse.GetRainBool()) 
	{
		cse.RainRandom();
	}
	else if(gRainKeepTime.GetNowTime() > (cse.GetRainKeepTime()+(rand()%120)))
	{ //���ֹͣһ��ʱ�䣬�ٳ�ʼ������ʼ��������Ϳ�ʼ������;
		cse.InitRain();
	}
	else
	{
		cse.StopRain();//ֹͣ������Ч
	//	oDirectXAudio.PlayMicMidiWav();//���ű�������
	}

	if( cse.GetSnowBool() ) { cse.SnowRandom(200);oSnowMgr.Snowing(200);}
	if( cse.GetLightBool() ) {/*cse.LightIntensity();*/ cse.light_asm();}
	

	//���ƽ�ɫ����
	HDC hdc(NULL);
	if (DDS[SBuffer]->GetDC(&hdc) == DD_OK)
	{ 
		TCHAR text[128];
		wsprintfW(text,L"%s:X:%d Y:%d + RollScreenX:%d RollScreenY:%d = x:%d ,y:%d" ,szMapName, oPlayer.GetPlayerMapX(),oPlayer.GetPlayerMapY(),mRollScreenX,mRollScreenY,
			(oPlayer.GetPlayerMapX()+ mRollScreenX),(oPlayer.GetPlayerMapY()+ mRollScreenY));
		SetBkMode(hdc,TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOutW(hdc,TILE_WIDE,TILE_HIGH,text, wcslen(text) ); //���ַ�����strlen����wcslen;
		DDS[SBuffer]->ReleaseDC(hdc);
	}

	//���߿�Ϊ��ɫ,��Ϸ����;
	DDBLTFX ddBltFx;
	ddBltFx.dwSize =sizeof(DDBLTFX);
	ddBltFx.dwFillPixel=0;//���ú�ɫ;
	//�������	����;
	MakeRect(0,0,XSCREEN,TILE_HIGH);		
	DDS[SBuffer]->Blt(&rect,NULL,&rect,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	//�������	�ײ�;	
	MakeRect(0,YSCREEN-TILE_HIGH,XSCREEN,YSCREEN);
	DDS[SBuffer]->Blt(&rect,NULL,&rect,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	//�������	��;		
	MakeRect(0,0,TILE_WIDE,YSCREEN);
	DDS[SBuffer]->Blt(&rect,NULL,&rect,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
	//�������	�Ҳ�;	
	MakeRect(XSCREEN-TILE_WIDE,0,XSCREEN,YSCREEN);
	DDS[SBuffer]->Blt(&rect,NULL,&rect,DDBLT_WAIT|DDBLT_COLORFILL,&ddBltFx);
}

/*��ͼ�༭��;*/
void Mapedit::MapEditUpdate()
{
	//���Ƶ�ͼ�༭������;
	HDC hDC;	DDS[SBuffer]->GetDC(&hDC);
	//COLORREF crCol = ::GetPixel(hDC,200, 200); //ȡ�ã�200, 200��������ɫֵ;
	for(int line = 0 ; line <= MAP_EDIT_AREA_Y ; line += TILE_WIDE )
		for(int law = 0 ; law <= MAP_EDIT_AREA_X ; law  += TILE_HIGH )
			::SetPixel(hDC, law, line, RGB(255,255,255)); //���ư�ɫ����;
	DDS[SBuffer]->ReleaseDC(hDC);   //�������ͷ�DC;

	//�������Ƿ��ڵ�ͼ������&�Ƿ�ѡ�񵥸�����&�Ƿ��ڵ�ͼ�༭��;
	if( !m_EditSave && bMouseLeftHitMap && IsNoSelectSingleTile() /*&& MouseIsAtMapEditArae()*/ )	
	{	//������갴��ʱ���ƶ��켣������,����̬�洢��Tile;
		�洢�����ز� ();
	}
	if( iMouseRightHitMap == PUSH_DOWN )//����;
	{
		//if(TileBeginX <TileXEnd || TileBeginY <TileYEnd)
		//�洢��ѡ�ز� (); 
	}
	else
		if( iMouseRightHitMap == PUSH_UP )//�ɿ�;
		{
			//if( sMouseRightHitMapDownX != sMouseRightHitMapUpX ||
			//	sMouseRightHitMapDownY != sMouseRightHitMapUpY  )
			//����ͼ();
			iMouseRightHitMap = PUSH_NOT;//��ɲ���;
		}
	
		ShowMap   ( TILE_WIDE , TILE_HIGH , -256 , -64 ) ;	
		//RefreshMap(0,0);
		//	if( m_bCollideState != false )
		��ʾ��ײ�� ( ) ;
		if (m_bTinyMap)
		{
			ShowMicroMap () ;
		}		
		��ʾ�ز�   ( ) ;
		SetRollScreen ( MAP_EDIT_MOVE_SPEED ) ;

		if( ��ˢ�� ) 
		{	//�����ˢ�ӹ��ܴ򿪣����õ�ͼ��һɫ;
			if( MessageBoxW(hWnd,L"�Ƿ����������ͼ��",L"ˢ��",MB_OKCANCEL)!=2 )
			{//ȷ��
				GetBigBrush () ; 
			}
			��ˢ�� = false;
		}

		gameGUI.SetMapBtn(); /*��ͼ�༭����ťGUI;*/

		//���Ƶ�ͼ�༭����������;
		static HDC hdc; 
		if (DDS[SBuffer]->GetDC(&hdc) == DD_OK)
		{	
			static HFONT ht;
			static LOGFONT lf; 
			SetBkMode(hdc,TRANSPARENT);//���ñ���ģʽ͸��;
			SetTextColor(hdc, RGB(200, 0, 0));//����������ɫ;
			SetTextCharacterExtra (hdc, 1) ;//�����м��;

			memset(&lf,   0,   sizeof(LOGFONT)); 
			lf.lfHeight   =   28;//��������߶�;
			lf.lfWidth	  =	  26;//����������;
			lf.lfWeight	  =	  900;//���塢0Ĭ�ϡ���100-900��ÿ�μ�100��
			ht = CreateFontIndirectW(&lf); 
			ht = (HFONT)SelectObject(hdc,ht);
			static TCHAR text[32];
			if (m_bCollideState)
			{
				wsprintfW(text,L"�༭�� %d �� ��ײ:��" , ͼ��+1);
			} 
			else
			{
				wsprintfW(text,L"�༭�� %d �� ��ײ:�رգ�" , ͼ��+1);

			}				
			TabbedTextOutW(hdc,555 ,YSCREEN-35,text, wcslen(text),NULL,NULL,NULL );
			DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

			//	SetTextAlign(hdc,TA_RIGHT);//���־���;
			memset(&lf,   0,   sizeof(LOGFONT)); 
			lf.lfHeight   =   12;//��������߶�;
			lf.lfWidth	  =	  10;//����������;
			lf.lfWeight	  =	  900;
			ht = CreateFontIndirectW(&lf); 
			ht = (HFONT)SelectObject(hdc,ht);
			SetTextColor(hdc, RGB(255, 255, 0));
			static TCHAR txt[MAX_PATH];// = L"�Ǽʵ�ͼ�༭��";
			wsprintfW(txt,L"�Ǽʵ�ͼ�༭�� - %s" ,szMapName);

			TextOutW(hdc,10,10, txt, wcslen(txt) ); //���ַ�����strlen����wcslen;				
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
		if (FILE * f = _wfopen(L"map//���Ƴ�.dat",L"r"))
		{ 	
			fread(MapX,sizeof(int),30000,f);
			fread(MapY,sizeof(int),30000,f);
			fread(mCollideArray,sizeof(bool),10000,f);
			wcscpy_s(szMapName,L"���Ƴ�");
			SetMonster(SPIRIT_POOL_MAX);
			fclose(f);
		}	
	}
}

void Mapedit::SetMonster(unsigned int cnt)
{
	for (unsigned int c = 0; c < cnt; ++ c)//����
	{ 
		oSpiritManager.SpiritInit(c,rand()%AI_ACTION_WIDE, rand()%AI_ACTION_HEIGHT);
	}
}

void Mapedit::SetTinyMapStatus(bool is_open)
{
	m_bTinyMap = is_open;
	if( graph.��ùؿ���() == MAP_EDIT )//��Ϸ��ͼ��ʱ������С��ͼ;
	SetMicroMap();
}