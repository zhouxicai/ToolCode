#ifndef _CGUN_H
#define _CGUN_H
#include "../../include/define.h"
//#include "netbase\NetManager.h"
//#include <vector>
//枪炮类
class CGun 
{
public:
	CGun()
	{	//初始化子弹地图坐标和绘制坐标
		fBulletMapPositionX = XSCREEN / 2 - 32+10;
		fBulletMapPositionY = YSCREEN / 2 - 32+10;

		fBulletDrawPositionX = XSCREEN / 2+10;
		fBulletDrawPositionY = YSCREEN / 2+10;
		bShootSwitch = false;
		bUseSwitch = false;
		sDirection = 0;
	};
	//子弹的开枪和终止
	void Shooting(int gun);//开枪射击(滚屏值)
	void BulletFinal();//子弹到达终点，销毁子弹。
	//设置子弹地图坐标和绘制坐标
	void SetBulletMapPositionX(int px){ fBulletMapPositionX+=px;};
	void SetBulletMapPositionY(int py){ fBulletMapPositionY+=py;};
	void SetBulletDrawPositionX(int px){ fBulletDrawPositionX+=px;};
	void SetBulletDrawPositionY(int py){ fBulletDrawPositionY+=py;};
	//得到子弹地图坐标和绘制坐标
	int GetBulletMapPositionX( ){ return fBulletMapPositionX;};
	int GetBulletMapPositionY( ){ return fBulletMapPositionY;};
	int GetBulletDrawPositionX( ){ return fBulletDrawPositionX;};
	int GetBulletDrawPositionY( ){ return fBulletDrawPositionY;};
	//剩余子弹
	static void SetBulletSurplusNumber(short num){ sBulletSurplusNumber+=num;};
	static short GetBulletSurplusNumber( ){ return sBulletSurplusNumber;};

	void SetShootSwitch(bool ss){ bShootSwitch=ss;};
	bool GetShootSwitch( ){ return bShootSwitch;};
	void SetDirection(short d){ sDirection=d;};
	short GetDirection( ){ return sDirection;};

//	short GetBulletMaxNumber( ){ return sBulletMaxNumber;};
	void BulletInitialization();

	bool GetUseSwitch( ){ return bUseSwitch;};
private:
	//子弹地图坐标
	int fBulletMapPositionX;
	int fBulletMapPositionY;
	//子弹绘制坐标
	int fBulletDrawPositionX;
	int fBulletDrawPositionY;

//	static const short sBulletMaxNumber = BULLE_MAXNUMBER;//最大子弹数量
	static short sBulletSurplusNumber;//剩余子弹数量
	
	bool bShootSwitch;//貌似与bUseSwitch功能重合
	bool bUseSwitch;  //子弹是否正在使用
	short sDirection; //子弹方向
};

#endif