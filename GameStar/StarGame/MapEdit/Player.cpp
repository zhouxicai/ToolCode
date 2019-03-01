#include "Player.h"
#include "main.h"
#include "TimeCount.h"
#include "Gun.h"

CPlayer oPlayer;
CPlayerManager oPlayerMgr;

CPlayer::CPlayer():tankFace(2),sLastFace(2),life(10),leave(0),�Ƿ񹥻�(false),tankMove(0),zidanX(0),zidanY(0),sBulleNumber(0)
{
/*	tankFace  = 2 ;
	sLastFace = 2 ;
	life  = 10	;
	leave = 0	*/;
	tankX = XSCREEN / 2 ; //�̶�����
	tankY = YSCREEN / 2 ; //��Ļ����
	iPlayerMapX = XSCREEN / 2 - TILE_WIDE;//��ʼ����
	iPlayerMapY = YSCREEN / 2 - TILE_HIGH;//��ͼ�Ǵ���Ļ32*32����ʼ���Ƶ�
	//�Ƿ񹥻� = false ;
	//tankMove = 0 ;
	//zidanX = 0 ;
	//zidanY = 0 ;
	//sBulleNumber = 0;
	CGun::CGun();

	for (short unIdx = 0; unIdx < MAX_BULLE_NUMBER; ++ unIdx)
	{ m_bullePool.push_back(new CGun);}

};


CPlayer::~CPlayer()
{
	m_bullePool.clear();
	//delete [] bulle;
}
void CPlayer :: TankMove()
{	tankMove++ ;//���¶���λ��			
	if ( tankMove > 1 ) tankMove = 0 ;
			// ���̰���ʱ�ķ���    ||  �ɿ���������ʱ����
		 if ( tankFace == UP    || sLastFace == UP   ) { MakeRect( tankMove*PLAYER_HIGH , PLAYER_HIGH*3 , tankMove*PLAYER_HIGH+PLAYER_HIGH , PLAYER_HIGH*4 ) ; }//����tankY-- ; 
	else if ( tankFace == DOWN  || sLastFace == DOWN ) { MakeRect( tankMove*PLAYER_HIGH , 0				, tankMove*PLAYER_HIGH+PLAYER_HIGH , PLAYER_HIGH   ) ; }//����tankY++ ; 
	else if ( tankFace == LEFT  || sLastFace == LEFT ) { MakeRect( tankMove*PLAYER_WIDE , PLAYER_WIDE   , tankMove*PLAYER_WIDE+PLAYER_WIDE , PLAYER_WIDE*2 ) ; }//����tankX-- ; 
	else if ( tankFace == RIGHT || sLastFace == RIGHT) { MakeRect( tankMove*PLAYER_WIDE , PLAYER_WIDE*2 , tankMove*PLAYER_WIDE+PLAYER_WIDE , PLAYER_WIDE*3 ) ; }//����tankX++ ; 	
	

	DDS[SBuffer]->BltFast ( tankX ,tankY , DDS[MM2TankB] , &rect , DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT );

	//DDS[SBuffer]->BltFast ( tankX+32 ,tankY+32 , DDS[MM2TankB] , &rect , DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT );
	//DDS[SPrimary]->Blt (&rect,DDS[MM2TankB],&rect,NULL,NULL); 
	/*1.����Ч�� 2.�Ŵ�ͼ��*/

}

//void CPlayer::JiJaMove()
//{	jijaMove++ ;//���¶���λ��		
	//if ( jijaMove > 3 ) jijaMove = 0 ;
	//if ( jijaFace == UP    ) { MakeRect( jijaMove*64 , 64*3 , jijaMove*64+64 , 64*4 ) ;  } //����
	//if ( jijaFace == DOWN  ) { MakeRect( jijaMove*64 , 0    , jijaMove*64+64 , 64   ) ;  } //����
	//if ( jijaFace == LEFT  ) { MakeRect( jijaMove*64 , 64   , jijaMove*64+64 , 64*2 ) ;  } //����
	//if ( jijaFace == RIGHT ) { MakeRect( jijaMove*64 , 64*2 , jijaMove*64+64 , 64*3 ) ;  } //����
	//
	////Ѳ��ģʽ
	//	 if ( jj == 0 ) { jijaFace = RIGHT; jijaX +=3; if( jijaX>700 )jj=1;}
	//else if ( jj == 1 ) { jijaFace = LEFT; jijaX -=3; if( jijaX<500 )jj=0;}

	//DDS[SBuffer]->BltFast ( jijaX + oMapedit.GetRollScreen(0),jijaY  + oMapedit.GetRollScreen(1) , DDS[����] , &rect ,
	//						 DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT);
//}

//void CPlayer :: SetJiJaFace( short f )
//{
//	jijaFace = f ;
//}

void CPlayer :: SetTankFace( short f )
{/*���¼�����������ʱ��DXInput��mian�������ñ���������̹�˳����ĸ�����*/
	tankFace = f ;
	if(f!=0){ sLastFace = f ;}
}

int CPlayer :: GetTankXY( int XY )
{
	if ( XY == 0 ) return tankX ;
	else		   return tankY ;
}

void CPlayer :: �ӵ����ж��� (  )
{
	// ��ȡmouse��ָ�������ֵ
	POINT mouse ;	 GetCursorPos( &mouse ) ;
	if( timeCount.GetNowTime() > 1) tankX++;

	DDS[SBuffer]->BltFast ( tankX + zidanX , tankY + zidanY , DDS[BaseBulle] , NULL ,
							DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
}
void CPlayer :: BeginShoot()
{
	if( !m_bullePool.at(sBulleNumber)->GetShootSwitch())
	{
		m_bullePool.at(sBulleNumber)->BulletInitialization();
		m_bullePool.at(sBulleNumber)->SetDirection(oPlayer.GetLastFace());
		m_bullePool.at(sBulleNumber)->SetShootSwitch(true);
	}
	sBulleNumber++;
	if(sBulleNumber>=MAX_BULLE_NUMBER)sBulleNumber=0;
}

void CPlayer::ShootLoop(short collide)
{
	for(short i=0; i<MAX_BULLE_NUMBER; i++)
	{
		if( m_bullePool.at(i)->GetShootSwitch() )
			m_bullePool.at(i)->Shooting(collide);
	}
}


CPlayer * CPlayerManager::GetPlayer(int player_id)
{
	unsigned int i=0;
	for(;i<m_PlayerPool.size();i++)
	{
		if(m_PlayerPool.at(i)->GetPlayerID() == player_id)
		{
			return m_PlayerPool.at(i);
		}
	}
	return NULL;
}

CPlayer * CPlayerManager::AddPlayer(int player_id)
{
	auto it = m_PlayerPool.begin();
	for(;it<m_PlayerPool.end();it++)
	{
		if((*it)->GetPlayerID() == player_id)
		{			
			return *it;
		}
	}
	CPlayer *p = new CPlayer(); 
	p->SetPlayerID(player_id);
	m_PlayerPool.push_back(p);
	return p;
}

bool CPlayerManager::DelPlayer(int player_id)
{
	auto it = m_PlayerPool.begin();
	for(;it<m_PlayerPool.end();it++)
	{
		if((*it)->GetPlayerID() == player_id)
		{			
			delete *it;
			m_PlayerPool.erase(it);
			return true;
		}
	}
	return false;
}