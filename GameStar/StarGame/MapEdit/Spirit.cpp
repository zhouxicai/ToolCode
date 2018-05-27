#include "Spirit.h"
#include "Player.h"
#include "main.h"
#include "../../include/define.h"

CSpiritManager oSpiritManager;
CSpiritManager::CSpiritManager()
{
	//for (short c = 0; c < SPIRIT_POOL_MAX; ++ c)//����
	//{ 
	//	m_SpiritPool[c].SpiritInit( rand()%XSCREEN, rand()%YSCREEN);
	//}
}

void CSpirit::SpiritInit(int x,int y)
{
	//��ײ���;
	int cs_x = x / TILE_WIDE;
	int cs_y = y / TILE_HIGH;
	if ( oMapedit.mCollideArray[cs_x][cs_y] ||
		oMapedit.mCollideArray[cs_x + 1][cs_y] ||
		oMapedit.mCollideArray[cs_x][cs_y + 1] ||
		oMapedit.mCollideArray[cs_x + 1][cs_y + 1]  ) /*����64*64��ײ��Χ; */	
	{
		SpiritInit(rand()%XSCREEN, rand()%YSCREEN);
		//���ȫ����ײ���ͻ��������޵ݹ�;
	}
	mNewX = x;
	mNewY = y;
};

//��ײ���;
bool CSpirit::CanMove()
{
	//����������ڵĵ�ǰ����
	int cs_x = mNewX / TILE_WIDE;
	int cs_y = mNewY / TILE_HIGH;
	/*�������û��ע�͵������У���������64*64��ײ��Χ; ע�͵��� 64*32�ˣ�����ֻ�����׵��Ȳ��Ƿ���ײ
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
	//��ײ���;
	int cs_x = mNewX / TILE_WIDE;
	int cs_y = mNewY / TILE_HIGH;
	/*����64*64��ײ��Χ;
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
	//���Ѳ��ģʽ;
	if ( CanMove()) /*��ײ���,����64*64��ײ��Χ; */	
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
	{	//��ײ����;
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
			jijaMove = 0 ;//����ֹͣ����;
		}
		else
		{
			jijaMove++ ;//���¶���֡pos;	
			if ( jijaMove > 3 ) jijaMove = 0 ;
		}
		
			//��ʼ�ƶ�;
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

		DDS[SBuffer]->BltFast ( mNewX + oMapedit.GetRollScreen(0),mNewY  + oMapedit.GetRollScreen(1) , DDS[����] , &rect ,
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
	//��ײ���;
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