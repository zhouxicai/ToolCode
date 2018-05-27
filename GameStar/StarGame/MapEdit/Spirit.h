
#ifndef SPIRIT_H
#define SPIRIT_H
#include <vector> //for rand()
#include "../../include/define.h"

class CSpirit
{
public:
	CSpirit():jijaFace(2),jijaMove(0),mIsUseShowing(false),mIsStop(false)
	{
		mNewX  = rand()%MAP_WIDE;
		mNewY  = rand()%MAP_HEIGHT;
		face_state = rand()&4;

	};
	CSpirit(int x,int y)
	{
		mNewX = x;
		mNewY = y;
	};
	void SpiritInit(int x,int y);
	void JiJaMove();
	bool CanMove();	//�����ײ;
	bool IsNoMove();
	bool IsOutside();
	void RandPos();
	int  RandFace(int before_face);
	void SetJiJaFace(short f)	{ jijaFace = f ;}
	void SetUseShow(bool is_show){ mIsUseShowing = is_show;};
	bool GetUseShow(){ return mIsUseShowing;};

	void SetJiX(short x)	{ mNewX = x ;}
	void SetJiY(short y)	{ mNewY = y ;}
private:
	short jijaFace ;
	int jijaMove ;//���׶���;
	int mNewX ;//��������
	int	mNewY ;
	int mOldX ;
	int	mOldY ;
	short face_state;//����AI״̬;
	bool mIsUseShowing;	//�Ƿ�����ʾʹ����;
	bool mIsStop;	//�Ƿ�ֹͣ����;
};

class CSpiritManager
{
public:
	CSpiritManager();

	CSpirit * GetSpirit();
	void SpiritInit(int pos,int x,int y);
	void MoveAlloSpirit();
private:
	//static const int MAX_SPIRIT_CNT = 100;	//���������;
	CSpirit m_SpiritPool[SPIRIT_POOL_MAX];
};

extern  CSpiritManager oSpiritManager;

#endif