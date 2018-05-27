#include "Spirit.h"
#include "Player.h"
#include "main.h"
#include "../../include/define.h"

CSpiritManager oSpiritManager;
CSpiritManager::CSpiritManager()
{
	//for (short c = 0; c < SPIRIT_POOL_MAX; ++ c)//测试
	//{ 
	//	m_SpiritPool[c].SpiritInit( rand()%XSCREEN, rand()%YSCREEN);
	//}
}

void CSpirit::SpiritInit(int x,int y)
{
	//碰撞检测;
	int cs_x = x / TILE_WIDE;
	int cs_y = y / TILE_HIGH;
	if ( oMapedit.mCollideArray[cs_x][cs_y] ||
		oMapedit.mCollideArray[cs_x + 1][cs_y] ||
		oMapedit.mCollideArray[cs_x][cs_y + 1] ||
		oMapedit.mCollideArray[cs_x + 1][cs_y + 1]  ) /*锁定64*64碰撞范围; */	
	{
		SpiritInit(rand()%XSCREEN, rand()%YSCREEN);
		//如果全是碰撞，就会陷入无限递归;
	}
	mNewX = x;
	mNewY = y;
};

//碰撞检测;
bool CSpirit::CanMove()
{
	//计算机甲所在的当前格子
	int cs_x = mNewX / TILE_WIDE;
	int cs_y = mNewY / TILE_HIGH;
	/*如果下面没有注释掉这三行，就是锁定64*64碰撞范围; 注释掉是 64*32了，就是只检测机甲的腿部是否碰撞
	*/	
	if (//oMapedit.mCollideArray[cs_x][cs_y] ||
		oMapedit.mCollideArray[cs_x][cs_y + 1] ||
		oMapedit.mCollideArray[cs_x][cs_y + 2] ||
		//oMapedit.mCollideArray[cs_x + 1][cs_y] ||
		//oMapedit.mCollideArray[cs_x + 2][cs_y] ||		
		oMapedit.mCollideArray[cs_x + 1][cs_y + 1] ||
		oMapedit.mCollideArray[cs_x + 1][cs_y + 2] ||
		oMapedit.mCollideArray[cs_x + 2][cs_y + 1] ||	
		oMapedit.mCollideArray[cs_x + 2][cs_y + 2] )
	{	
		return false;
	}
	return true;	
}

void CSpirit::RandPos()
{
	mNewX = rand()%AI_ACTION_WIDE;
	mNewY = rand()%AI_ACTION_HEIGHT;
	if (IsOutside() || IsNoMove())
	{
		RandPos();
	}
}
bool CSpirit::IsNoMove()
{
	//碰撞检测;
	int cs_x = mNewX / TILE_WIDE;
	int cs_y = mNewY / TILE_HIGH;
	/*锁定64*64碰撞范围;
		0,0 0,1 0,2
		1,0 1,1 1,2
		2,0 2,1 2,2
	*/	
	if (oMapedit.mCollideArray[cs_x][cs_y] ||
		oMapedit.mCollideArray[cs_x + 1][cs_y] ||
		oMapedit.mCollideArray[cs_x + 2][cs_y] ||
		oMapedit.mCollideArray[cs_x][cs_y + 1] ||
		oMapedit.mCollideArray[cs_x][cs_y + 2] ||
		oMapedit.mCollideArray[cs_x + 1][cs_y + 1] ||		
		oMapedit.mCollideArray[cs_x + 2][cs_y + 2]  ) 
	{
		return true;
	}
	return false;
}
bool CSpirit::IsOutside()
{
	if( mNewY>(AI_ACTION_HEIGHT-BORDER) ||mNewX>(AI_ACTION_WIDE-BORDER) ||mNewY < BORDER ||mNewX < BORDER )
	{
		return true;			
	}
	return false;
}
void CSpirit::JiJaMove()
{
	//随机巡逻模式;
	if ( CanMove()) /*碰撞检测,锁定64*64碰撞范围; */	
	{
		int r( rand()%100 );
		if ( r == UP    ) 
		{
			face_state = jijaFace =  UP   ;
			mIsStop =  false;
		}
		else if ( r == DOWN  ) 
		{
			face_state = jijaFace =  DOWN ;
			mIsStop =  false;
		}
		else if ( r == LEFT  ) 
		{
			face_state = jijaFace =  LEFT ;
			mIsStop =  false;
		}
		else if ( r == RIGHT ) 
		{
			face_state = jijaFace =  RIGHT;
			mIsStop =  false;
		}
		else if ( r == STOP ) 
		{
			face_state = STOP;
			mIsStop =  true;
		}
	}
	else
	{	//碰撞处理;
		if( jijaFace == RIGHT) 
		{
			mNewX -= JIJIA_MOVE_SPEED ; 
		}
		else if( jijaFace == LEFT) 
		{	
			mNewX += JIJIA_MOVE_SPEED ; 
		}
		else if( jijaFace == UP)
		{
			mNewY += JIJIA_MOVE_SPEED ; 
		}
		else if( jijaFace == DOWN)
		{
			mNewY -= JIJIA_MOVE_SPEED ; 
		}	
		int r( RandFace(jijaFace) );
		if (r == STOP )
		{
			mIsStop =  true;
		}
		else
		{
			mIsStop =  false;
			jijaFace = r;
		}
	}

			
		if (mIsStop)
		{
			jijaMove = 0 ;//精灵停止不动;
		}
		else
		{
			jijaMove++ ;//更新动画帧pos;	
			if ( jijaMove > 3 ) jijaMove = 0 ;
		}
		
			//开始移动;
			if ( jijaFace == UP    )
			{ 
				if (!mIsStop) mNewY -=  JIJIA_MOVE_SPEED; 
				MakeRect( jijaMove*64 , 64*3 , jijaMove*64+64 , 64*4 ) ;  
			}
			else if ( jijaFace == DOWN  ) 
			{ 
				if (!mIsStop) mNewY += JIJIA_MOVE_SPEED; 
				MakeRect( jijaMove*64 , 0    , jijaMove*64+64 , 64   ) ;  
			}
			else if ( jijaFace == LEFT  ) 
			{ 
				if (!mIsStop) mNewX -= JIJIA_MOVE_SPEED; 
				MakeRect( jijaMove*64 , 64   , jijaMove*64+64 , 64*2 ) ;  
			} 
			else if ( jijaFace == RIGHT ) 
			{ 
				if (!mIsStop) mNewX += JIJIA_MOVE_SPEED;
				MakeRect( jijaMove*64 , 64*2 , jijaMove*64+64 , 64*3 ) ;  
			}			

		DDS[SBuffer]->BltFast ( mNewX + oMapedit.GetRollScreen(0),mNewY  + oMapedit.GetRollScreen(1) , DDS[机甲] , &rect ,
			DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT);
}

int CSpirit::RandFace(int before_face)
{
	int r( rand()%5+1 );
	if (r == before_face)
	{
		RandFace(before_face);
	}
	return r;
}


void CSpiritManager::SpiritInit(int pos,int x,int y)
{
	//碰撞检测;
	int cs_x = x / TILE_WIDE;
	int cs_y = y / TILE_HIGH;
	{
		m_SpiritPool[pos].SetJiX(x);
		m_SpiritPool[pos].SetJiX(y);
	}	
	if (m_SpiritPool[pos].IsOutside() || m_SpiritPool[pos].IsNoMove())
	{
		m_SpiritPool[pos].RandPos();
	}
};

CSpirit * CSpiritManager::GetSpirit()
{
	for (auto c = 0; c < SPIRIT_POOL_MAX; ++ c)
	{ 
		if (!m_SpiritPool[c].GetUseShow())
		{
			m_SpiritPool[c].SetUseShow(true);
			return &m_SpiritPool[c];
		}
	}
	return NULL;
}

void CSpiritManager::MoveAlloSpirit()
{
	for (auto c = 0; c < SPIRIT_POOL_MAX; ++ c)
	{ 
		m_SpiritPool[c].JiJaMove();
	}
}