#include "main.h"
#include "SpecialEfficiency.h"
#include "../../include/define.h"
GameGUI gameGUI ;

void GameGUI::MainBtn ()
{	// ��ȡmouse��ָ�������ֵ;
	POINT mouse ;	 GetCursorPos( &mouse ) ;

	// ��Ϸ��ʼ�ı���ͼ;
	DDS[SBuffer]->BltFast ( 0 , 0 , DDS[GameBack] , NULL ,
							DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT ) ;	
	// ������Ϸ���˵���ťĬ��Ч��;
		MakeRect( 0 , 0 , 90 , 100 ) ; 
	DDS[SBuffer]->BltFast(	XSCREEN / 2 - 45 , YSCREEN / 2 ,
							DDS[���˵�] , &rect , 
							DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;
	RECT rc ;GetWindowRect(hWnd,&rc);
	//��Ϸ��Ļ����;
	long bx = ( rc.right-rc.left )/2+rc.left;
	long by = ( rc.bottom-rc.top )/2+rc.top;
	// mouse���������˵�����Ϸ��ʼ����ť����ĽӴ����	;
	if ( mouse.x > bx - 45			 && 
		 mouse.x < bx + 180 / 2 - 45 && 
		 mouse.y > by 				 && 
		 mouse.y < by + 100 / 4		 )
		{	// ����ʼ��Ϸ����ť��̬��Ӧmouse����Ч������;
			MakeRect( 90 , 0 , 180 , 25 ) ; 
		 DDS[SBuffer]->BltFast( XSCREEN / 2 - 45 , YSCREEN / 2 ,
		 						DDS[���˵�] , &rect ,
		 						DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT ) ;
		}
	// mouse���������˵�����ͼ�༭������ť����ĽӴ����;	
	if ( mouse.x > bx - 45			&& 
		 mouse.x < bx + 180 / 2 - 45&& 
		 mouse.y > by + 100 / 4		&& 
		 mouse.y < by + 100 / 2		)
		{	//����ͼ�༭������ť��̬��Ӧmouse����Ч������;
			MakeRect( 90 , 25 , 180 , 50 ) ;
		 DDS[SBuffer]->BltFast( XSCREEN / 2 - 45 , YSCREEN / 2 + 25 ,
								DDS[���˵�] , &rect ,
								DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT);
		}
	//cse.transparent();

		// ������Ϸ���˵�����
		//HDC hdc=NULL;	wchar_t* text =L"���Ŷݼ�֮����̹��";
		//DDS[SBuffer]->GetDC(&hdc);
		//SetBkMode(hdc,TRANSPARENT);
		//SetTextColor(hdc, RGB(200, 250, 100));
		//TextOut(hdc,10,10, text, wcslen(text) );
		//DDS[SBuffer]->ReleaseDC(hdc);	
}
//#include "DirectXAudio.h"
short GameGUI::SetMainBtn ()
{
	if ( graph.��ùؿ���() != MAIN_BTN) return false; /*�����˵�����÷�Χ����Ч*/
	// ��ȡmouse��ָ�������ֵ
	POINT mouse ;	 GetCursorPos( &mouse ) ; 
	RECT rc ; GetWindowRect(hWnd,&rc);
	long bx = ( rc.right-rc.left )/2+rc.left;
	long by = ( rc.bottom-rc.top )/2+rc.top;

	//mouse�����롰��ͼ�༭������ť����Ӵ����
	if ( mouse.x > bx-45		&& 
		 mouse.x < bx+180/2-45  && 
		 mouse.y > by+100/4	   && 
		 mouse.y < by+100/2		)
	{	
		return MAP_EDIT;
	}
	//mouse�����롰��ʼ��Ϸ����ť����Ӵ����/
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

/*��ͼ�༭����ť*/
void GameGUI::SetMapBtn () 
{
	// ��ȡmouse��ָ�������ֵ
	POINT mouse ;	 
	GetCursorPos( &mouse ) ; 

	RECT rc ; GetWindowRect(hWnd,&rc);
	double bx = rc.right-rc.left;
	double by = rc.bottom-rc.top;

	const long btn_bmp_x_size = 540;
	//double ���� = ;
	double ��ͼ��ť���ŵ�ʵ�ʳߴ� = btn_bmp_x_size/(XSCREEN/bx);

	/*��ͼ�༭����ťĬ��Ч��*/
	MakeRect( 0 , 0 , 540 , 43 ) ; 
	DDS[SBuffer]->BltFast( 0 , YSCREEN - 43,DDS[MapBtn] , &rect ,
							DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT );
	
	/*��ͼ�༭����ť,��̬��ӦmouseЧ��*/
	if ( mouse.x > rc.left && mouse.x < rc.left + ��ͼ��ť���ŵ�ʵ�ʳߴ� / 4   && 
		 mouse.y > by - 43 &&
		 mouse.y < by - 10 )
		{	MakeRect( 0 , 43 , 540 / 4 , 86 ) ; //ָ�� �½���ͼ Ч��
			DDS[SBuffer]->BltFast( 0 , YSCREEN - 43,DDS[MapBtn] , &rect , 
								DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT ) ;	
		}
	else if ( mouse.x > rc.left + ��ͼ��ť���ŵ�ʵ�ʳߴ�  / 4  && 
			  mouse.x < rc.left + ��ͼ��ť���ŵ�ʵ�ʳߴ�  / 2  && 
			  mouse.y > by - 43  &&
			  mouse.y < by - 15 		  )	
		{	MakeRect( 540 / 4 , 43 , 540 / 2 , 86 ) ; //ָ�� �򿪵�ͼ Ч��
			DDS[SBuffer]->BltFast( 540 / 4 , YSCREEN - 43,DDS[MapBtn] , &rect , 
								DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT ) ;	
		}
	else if ( mouse.x > rc.left + ��ͼ��ť���ŵ�ʵ�ʳߴ� / 2   && 
			  mouse.x < rc.left + ��ͼ��ť���ŵ�ʵ�ʳߴ� - ��ͼ��ť���ŵ�ʵ�ʳߴ� / 4  && 
			  mouse.y > by - 43 &&
			  mouse.y < by - 15		  )	
		{	MakeRect( 540 / 2 , 43 , 540 - 540 / 4 , 86 ) ; //ָ�� �����ͼ Ч��
			DDS[SBuffer]->BltFast( 540 / 2 , YSCREEN - 43,DDS[MapBtn] , &rect , 
								DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT ) ;	
		}
	else if ( mouse.x > rc.left + ��ͼ��ť���ŵ�ʵ�ʳߴ� - ��ͼ��ť���ŵ�ʵ�ʳߴ� / 4  && 
			  mouse.x < rc.left + ��ͼ��ť���ŵ�ʵ�ʳߴ�	&&
			  mouse.y > by - 43 &&
			  mouse.y < by - 15		  )	
		{	MakeRect( 540 - 540 / 4 , 43 , 540 , 86 ) ; //ָ�� �����˵� Ч��
			DDS[SBuffer]->BltFast( 540 - 540 / 4 , YSCREEN - 43,DDS[MapBtn] , &rect , 
								DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT) ;
		}
}