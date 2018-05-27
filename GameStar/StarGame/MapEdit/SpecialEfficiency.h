//#include <windows.h>
#ifndef CSPECIAL_EFFICIENCY_H
#define CSPECIAL_EFFICIENCY_H

#include "main.h"
#include "TimeCount.h"

//������ʱ��
extern TimeCount gSnowKeepTime;	//��ѩ����ʱ��;
extern TimeCount gRainKeepTime;	//�������ʱ��
const short EAST=0,WEST=1,NORTH=2;

class CSpecialEfficiency
{
private:
	bool b_rain;
	bool b_snow;
	bool b_light;
	double nr;
	double round_x,round_y;//Բ����;
	short mWindFace;	//�緽��;
	short mWindAngle;	//��ϸ΢�Ƕ�;
	short mRainCount;	//�������;
	short mRainKeepTime;//���������ʱ��;
	bool mRainCountChange;//�����仯���ƿ���;
	
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