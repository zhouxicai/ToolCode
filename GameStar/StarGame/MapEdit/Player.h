#ifndef _CPLAYER_H
#define _CPLAYER_H
#include "../../include/define.h"
#include <vector>
//ǹ����
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
//	bool CanMove();	//�����ײ;
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
//	int jijaMove ;//���׶���;
//	int mNewX ;//��������
//	int	mNewY ;
//	int mOldX ;
//	int	mOldY ;
//	short face_state;//����AI״̬;
//	bool mIsUseShowing;	//�Ƿ�����ʾʹ����;
//	bool mIsStop;	//�Ƿ�ֹͣ����;
//};
class CPlayer //:public CNetManager
{
private:
	int life;		//����ֵ
	int leave;		//�ȼ�
	short tankFace;		//̹�˳���
	
	int �ӵ�Xֵ , �ӵ�Yֵ;
	bool �Ƿ񹥻�;
	int tankMove; 
	//short jijaFace ;
	//int jijaMove ;//���׶���

	//̹������,λ����Ļ�м䣬�̶�������ϵ
	int tankX , tankY;
	//̹�˵�ͼ����,����ڵ�ͼ������ϵ
	int iPlayerMapX,iPlayerMapY;//���ͼ�߼�����

	//int jijaX ;
	//int	jijaY ;
	int zidanX;
	int	zidanY;
	//short jj;//����AI״̬

	int iPlayerID; //�����������ID

	short sLastFace;//��������ɿ��ķ���
public:
	void SetLastFace(short lf){ sLastFace = lf;};
	short  GetLastFace(){ return sLastFace;};
public:
	 CPlayer();
	~CPlayer();
	void SetPlayerID(int pid){ iPlayerID = pid;};
	int  GetPlayerID(){ return iPlayerID;};

	CPlayer(int x,int y)//��ʼ���������;
	{
		tankX = x;
		tankY = y;
	}
	//void JiJaMove() ;
	void TankMove()	;	  /*��Ϸˢ��ʱ�����ñ�����*/
	void SetTankFace(short f); /*������������ʱ��DXInput���ñ���������̹�˳����ĸ�����*/
	//void SetJiJaFace(short f)	;
	int  GetTankXY(int XY);  //���̹��λ��
	int  GetTankFace(){ return tankFace ; } //���̹�˳����־
	void �ӵ����ж��� ();
	int  ����ӵ�ֵ ();
	bool ����Ƿ񹥻� (){ return �Ƿ񹥻� ;}
	void �����Ƿ񹥻� ( bool TF ) { �Ƿ񹥻� = TF ; }

	//��ҵ�ͼ�������
	void SetPlayerMapCoord(int mx,int my){iPlayerMapY = my;iPlayerMapX = mx;};
	void SetPlayerMapX(int pmx){iPlayerMapX += pmx;};
	void SetPlayerMapY(int pmy){iPlayerMapY += pmy;};
	int  GetPlayerMapX(){return iPlayerMapX;};
	int  GetPlayerMapY(){return iPlayerMapY;};

//	CGun *bulle;//�ӵ�
	std::vector<CGun *> m_bullePool;
	void BeginShoot();
	void ShootLoop(short collide);
private:
	short sBulleNumber ;//�ӵ��ؿ��ƶ������ //�ӵ�����
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
	static const int PLAYER_POOL_MAX = 100;	//����������;
	std::vector<CPlayer *> m_PlayerPool;
};

extern  CPlayer oPlayer;
extern  CPlayerManager oPlayerMgr;
#endif