#ifndef _MAP_DEFINE_H_
#define _MAP_DEFINE_H_
#include "InorganicBase.h"
#include "OrganismsBase.h"

class CBotany		//植物
{
	int mFlower;
	int mGeology;

};

class CAnimal	//动物类
{
	//食肉动物
	int tiger;		//虎
	int lion;		//狮
	int leopard;	//豹
	int bear;		//熊
	//草食动物

	//爬虫

	//飞虫

	//蛇类

	//蜥蜴冷血动物

	//恐龙

	//神兽

	//鸟类	

	//鱼类

	//虾类

	//鲸类
};

class CFlower		//花类
{
	int chrysanthemum;//菊花
	int sunflower	;//向日葵
	int tulip		;//郁金香
	int rose		;//玫瑰
	int peony		;//牡丹
	int grass		;//小草
};
class CTree		//树木
{
	int spruce;		//云杉

};
class CLand : public CInorganic
{
public:
private:
};


class CMapDefine
{
public:
	void SetMap()
	{

	}
private:
	int mTileGUID;		//贴编号
	int mx,my,mz;		//x,y坐标,z:高度
	int temperature;	//温度;
	int humidity;		//湿度;
	int luminance;		//亮度;
	int mSmell;			//气味;
	int mTaste;			//味道;
	int mVisibility;	//可见度;
	int	mWindSpeed;		//风速;				
	int mWindOrientation;//风向;
	int animal;		//动态物体
	CLand mLand;	//土地类型

};
#endif