//#include <windows.h>
#ifndef CSPECIAL_EFFICIENCY_H
#define CSPECIAL_EFFICIENCY_H

#include "main.h"
#include "TimeCount.h"

//按键计时器
extern TimeCount gSnowKeepTime;	//下雪持续时间;
extern TimeCount gRainKeepTime;	//下雨持续时间
const short EAST=0,WEST=1,NORTH=2;

class CSpecialEfficiency
{
private:
	bool b_rain;
	bool b_snow;
	bool b_light;
	double nr;
	double round_x,round_y;//圆坐标;
	short mWindFace;	//风方向;
	short mWindAngle;	//风细微角度;
	short mRainCount;	//雨滴数量;
	short mRainKeepTime;//下雨持续的时间;
	bool mRainCountChange;//雨量变化控制开关;
	
public:
	CSpecialEfficiency();
	void InitRain();
	void RainRandom();
	void StopRain();
	void SnowRandom(UINT count);
	void fire();
	void LightIntensity();
	void light_asm();
	void transparent();
	void TestYuan(double r);

	void RainSwitch(bool rs){ b_rain = rs;};
	void SnowSwitch(bool ss){ b_snow = ss;};
	void LightSwitch(bool ls){ b_light = ls;};
	bool GetRainBool(){ return b_rain;};
	bool GetSnowBool(){ return b_snow;};
	short GetWindFace(){ return mWindFace;};
	
	short GetRainKeepTime(){ return mRainKeepTime;}
	bool GetLightBool(){ return b_light;};

};
extern CSpecialEfficiency cse;


#endif