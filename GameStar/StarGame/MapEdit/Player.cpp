#include "Player.h"
#include "main.h"
#include "TimeCount.h"
#include "Gun.h"

CPlayer oPlayer;
CPlayerManager oPlayerMgr;

CPlayer::CPlayer():tankFace(2),sLastFace(2),life(10),leave(0),是否攻击(false),tankMove(0),zidanX(0),zidanY(0),sBulleNumber(0)
{
/*	tankFace  = 2 ;
	sLastFace = 2 ;
	life  = 10	;
	leave = 0	*/;
	tankX = XSCREEN / 2 ; //固定不变
	tankY = YSCREEN / 2 ; //屏幕中央
	iPlayerMapX = XSCREEN / 2 - TILE_WIDE;//初始坐标
	iPlayerMapY = YSCREEN / 2 - TILE_HIGH;//地图是从屏幕32*32处开始绘制的
	//是否攻击 = false ;
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
{	tankMove++ ;//更新动画位置			
	if ( tankMove > 1 ) tankMove = 0 ;
			// 键盘按下时的方向    ||  松开按键的临时方向
		 if ( tankFace == UP    || sLastFace == UP   ) { MakeRect( tankMove*PLAYER_HIGH , PLAYER_HIGH*3 , tankMove*PLAYER_HIGH+PLAYER_HIGH , PLAYER_HIGH*4 ) ; }//向上tankY-- ; 
	else if ( tankFace == DOWN  || sLastFace == DOWN ) { MakeRect( tankMove*PLAYER_HIGH , 0				, tankMove*PLAYER_HIGH+PLAYER_HIGH , PLAYER_HIGH   ) ; }//向下tankY++ ; 
	else if ( tankFace == LEFT  || sLastFace == LEFT ) { MakeRect( tankMove*PLAYER_WIDE , PLAYER_WIDE   , tankMove*PLAYER_WIDE+PLAYER_WIDE , PLAYER_WIDE*2 ) ; }//向左tankX-- ; 
	else if ( tankFace == RIGHT || sLastFace == RIGHT) { MakeRect( tankMove*PLAYER_WIDE , PLAYER_WIDE*2 , tankMove*PLAYER_WIDE+PLAYER_WIDE , PLAYER_WIDE*3 ) ; }//向右tankX++ ; 	
	

	DDS[SBuffer]->BltFast ( tankX ,tankY , DDS[MM2TankB] , &rect , DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT );

	//DDS[SBuffer]->BltFast ( tankX+32 ,tankY+32 , DDS[MM2TankB] , &rect , DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT );
	//DDS[SPrimary]->Blt (&rect,DDS[MM2TankB],&rect,NULL,NULL); 
	/*1.动画效果 2.放大图像*/

}

//void CPlayer::JiJaMove()
//{	jijaMove++ ;//更新动画位置		
	//if ( jijaMove > 3 ) jijaMove = 0 ;
	//if ( jijaFace == UP    ) { MakeRect( jijaMove*64 , 64*3 , jijaMove*64+64 , 64*4 ) ;  } //向上
	//if ( jijaFace == DOWN  ) { MakeRect( jijaMove*64 , 0    , jijaMove*64+64 , 64   ) ;  } //向下
	//if ( jijaFace == LEFT  ) { MakeRect( jijaMove*64 , 64   , jijaMove*64+64 , 64*2 ) ;  } //向左
	//if ( jijaFace == RIGHT ) { MakeRect( jijaMove*64 , 64*2 , jijaMove*64+64 , 64*3 ) ;  } //向右
	//
	////巡逻模式
	//	 if ( jj == 0 ) { jijaFace = RIGHT; jijaX +=3; if( jijaX>700 )jj=1;}
	//else if ( jj == 1 ) { jijaFace = LEFT; jijaX -=3; if( jijaX<500 )jj=0;}

	//DDS[SBuffer]->BltFast ( jijaX + oMapedit.GetRollScreen(0),jijaY  + oMapedit.GetRollScreen(1) , DDS[机甲] , &rect ,
	//						 DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT);
//}

//void CPlayer :: SetJiJaFace( short f )
//{
//	jijaFace = f ;
//}

void CPlayer :: SetTankFace( short f )
{/*按下键盘上下左右时，DXInput和mian函数调用本函数设置坦克朝向哪个方向*/
	tankFace = f ;
	if(f!=0){ sLastFace = f ;}
}

int CPlayer :: GetTankXY( int XY )
{
	if ( XY == 0 ) return tankX ;
	else		   return tankY ;
}

void CPlayer :: 子弹飞行动画 (  )
{
	// 获取mouse所指向的坐标值
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