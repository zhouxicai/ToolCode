#include "Gun.h"
#include "main.h"
#include "player.h"
void CGun::Shooting(int gun)
{	//�ӵ�����Ļ��Χ��
//	if( fBulletDrawPositionY > 0 && fBulletDrawPositionY < YSCREEN &&
//		fBulletDrawPositionX > 0 && fBulletDrawPositionX < XSCREEN /*&&
//		timeCount.GetNowTime() > 1 */)
//	{	//�ӵ��ƶ� 1234��������;
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
		
		//��������ӵ�ƫ��;
		if( oPlayer.GetTankFace() == 1 && sDirection != 1  )//ò��Ч����ȷ���߼����ܴ���;
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
				bUseSwitch = true; //����ӵ�����ʹ���У����ڲ���ʹ��״̬
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
	//��ʼ���ӵ���ͼ����ͻ�������
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