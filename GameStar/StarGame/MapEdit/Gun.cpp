#include "Gun.h"
#include "main.h"
#include "player.h"
void CGun::Shooting(int gun)
{	//子弹在屏幕范围内
//	if( fBulletDrawPositionY > 0 && fBulletDrawPositionY < YSCREEN &&
//		fBulletDrawPositionX > 0 && fBulletDrawPositionX < XSCREEN /*&&
//		timeCount.GetNowTime() > 1 */)
//	{	//子弹移动 1234上下左右;
		if( sDirection == 1 )
		{	
			fBulletDrawPositionY -=BULLE_SPEED;
		}else
		if( sDirection == 2 )
		{
			fBulletDrawPositionY +=BULLE_SPEED ;
		}else
		if( sDirection == 3 )
		{
			fBulletDrawPositionX -=BULLE_SPEED ;
		}else
		if( sDirection == 4 )
		{
			fBulletDrawPositionX +=BULLE_SPEED ;
		} 

		DDS[SBuffer]->BltFast ( fBulletDrawPositionX , fBulletDrawPositionY , DDS[BaseBulle] , NULL ,
								DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT);
		
		//处理滚屏子弹偏移;
		if( oPlayer.GetTankFace() == 1 && sDirection != 1  )//貌似效果正确，逻辑可能错误;
		{												  
			fBulletDrawPositionY +=gun ;				  
		}else											  
		if( oPlayer.GetTankFace() == 2 && sDirection != 2 )
		{												  
			fBulletDrawPositionY -=gun ;				  
		}else											  
		if( oPlayer.GetTankFace() == 3 && sDirection != 3  )
 		{												  
			fBulletDrawPositionX +=gun ;				  
		}else											  
		if( oPlayer.GetTankFace() == 4 && sDirection != 4 )
		{
			fBulletDrawPositionX -=gun ;
		} 

		if( fBulletDrawPositionY > 0 && fBulletDrawPositionY < YSCREEN &&
			fBulletDrawPositionX > 0 && fBulletDrawPositionX < XSCREEN  )
		{
				bShootSwitch = true;
				bUseSwitch = true; //如果子弹正在使用中，则处于不可使用状态
				sBulletSurplusNumber ++;
		}
		else
		{
			bShootSwitch = false;
			bUseSwitch = false;
			sBulletSurplusNumber --;
		//	if(sBulletSurplusNumber <1)sBulletSurplusNumber=10;
			fBulletDrawPositionX = XSCREEN / 2;
			fBulletDrawPositionY = YSCREEN / 2;
			CGun::CGun();
		}
			
//	}
}

void CGun::BulletInitialization()
{
	//初始化子弹地图坐标和绘制坐标
	fBulletMapPositionX = XSCREEN / 2 - TILE_WIDE+10;
	fBulletMapPositionY = YSCREEN / 2 - TILE_HIGH+10;
	
	fBulletDrawPositionX = XSCREEN / 2+10;
	fBulletDrawPositionY = YSCREEN / 2+10;
	//bShootSwitch = false;
	//sDirection = 0;
}
void CGun::BulletFinal()
{

}

short CGun::sBulletSurplusNumber = BULLE_MAXNUMBER;