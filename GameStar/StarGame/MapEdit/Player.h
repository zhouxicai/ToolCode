#ifndef _CPLAYER_H
#define _CPLAYER_H
#include "../../include/define.h"
#include <vector>
//枪炮类
class CGun;
//class CSpirit;
//class CSpirit
//{
//public:
//	CSpirit():jijaFace(2),jijaMove(0),mIsUseShowing(false),mIsStop(false)
//	{
//		mNewX  = rand()%MAP_WIDE;
//		mNewY  = rand()%MAP_HEIGHT;
//		face_state = rand()&4;
//
//	};
//	CSpirit(int x,int y)
//	{
//		mNewX = x;
//		mNewY = y;
//	};
//	void SpiritInit(int x,int y);
//	void JiJaMove();
//	bool CanMove();	//检测碰撞;
//	bool IsNoMove();
//	bool IsOutside();
//	void RandPos();
//	int  RandFace(int before_face);
//	void SetJiJaFace(short f)	{ jijaFace = f ;}
//	void SetUseShow(bool is_show){ mIsUseShowing = is_show;};
//	bool GetUseShow(){ return mIsUseShowing;};
//
//	void SetJiX(short x)	{ mNewX = x ;}
//	void SetJiY(short y)	{ mNewY = y ;}
//private:
//	short jijaFace ;
//	int jijaMove ;//机甲动画;
//	int mNewX ;//机甲坐标
//	int	mNewY ;
//	int mOldX ;
//	int	mOldY ;
//	short face_state;//机甲AI状态;
//	bool mIsUseShowing;	//是否在显示使用中;
//	bool mIsStop;	//是否停止不动;
//};
class CPlayer //:public CNetManager
{
private:
	int life;		//生命值
	int leave;		//等级
	short tankFace;		//坦克朝向
	
	int 子弹X值 , 子弹Y值;
	bool 是否攻击;
	int tankMove; 
	//short jijaFace ;
	//int jijaMove ;//机甲动画

	//坦克坐标,位于屏幕中间，固定的坐标系
	int tankX , tankY;
	//坦克地图坐标,相对于地图的坐标系
	int iPlayerMapX,iPlayerMapY;//大地图逻辑坐标

	//int jijaX ;
	//int	jijaY ;
	int zidanX;
	int	zidanY;
	//short jj;//机甲AI状态

	int iPlayerID; //服务器分配的ID

	short sLastFace;//按键最后松开的方向
public:
	void SetLastFace(short lf){ sLastFace = lf;};
	short  GetLastFace(){ return sLastFace;};
public:
	 CPlayer();
	~CPlayer();
	void SetPlayerID(int pid){ iPlayerID = pid;};
	int  GetPlayerID(){ return iPlayerID;};

	CPlayer(int x,int y)//初始化玩家坐标;
	{
		tankX = x;
		tankY = y;
	}
	//void JiJaMove() ;
	void TankMove()	;	  /*游戏刷新时，调用本函数*/
	void SetTankFace(short f); /*按下上下左右时，DXInput调用本函数设置坦克朝向哪个方向*/
	//void SetJiJaFace(short f)	;
	int  GetTankXY(int XY);  //获得坦克位置
	int  GetTankFace(){ return tankFace ; } //获得坦克朝向标志
	void 子弹飞行动画 ();
	int  获得子弹值 ();
	bool 获得是否攻击 (){ return 是否攻击 ;}
	void 设置是否攻击 ( bool TF ) { 是否攻击 = TF ; }

	//玩家地图坐标控制
	void SetPlayerMapCoord(int mx,int my){iPlayerMapY = my;iPlayerMapX = mx;};
	void SetPlayerMapX(int pmx){iPlayerMapX += pmx;};
	void SetPlayerMapY(int pmy){iPlayerMapY += pmy;};
	int  GetPlayerMapX(){return iPlayerMapX;};
	int  GetPlayerMapY(){return iPlayerMapY;};

//	CGun *bulle;//子弹
	std::vector<CGun *> m_bullePool;
	void BeginShoot();
	void ShootLoop(short collide);
private:
	short sBulleNumber ;//子弹池控制对象变量 //子弹数量
	static const short MAX_BULLE_NUMBER = 6;
};

class CPlayerManager
{
public:
	void SpiritInit(int pos,int x,int y);

	CPlayer * GetPlayer(int player_id);
	CPlayer * AddPlayer(int player_id);
	bool DelPlayer(int player_id);
	
private:
	static const int PLAYER_POOL_MAX = 100;	//最大玩家数量;
	std::vector<CPlayer *> m_PlayerPool;
};

extern  CPlayer oPlayer;
extern  CPlayerManager oPlayerMgr;
#endif