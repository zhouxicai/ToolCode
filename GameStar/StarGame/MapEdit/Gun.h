#ifndef _CGUN_H
#define _CGUN_H
#include "../../include/define.h"
//#include "netbase\NetManager.h"
//#include <vector>
//ǹ����
class CGun 
{
public:
	CGun()
	{	//��ʼ���ӵ���ͼ����ͻ�������
		fBulletMapPositionX = XSCREEN / 2 - 32+10;
		fBulletMapPositionY = YSCREEN / 2 - 32+10;

		fBulletDrawPositionX = XSCREEN / 2+10;
		fBulletDrawPositionY = YSCREEN / 2+10;
		bShootSwitch = false;
		bUseSwitch = false;
		sDirection = 0;
	};
	//�ӵ��Ŀ�ǹ����ֹ
	void Shooting(int gun);//��ǹ���(����ֵ)
	void BulletFinal();//�ӵ������յ㣬�����ӵ���
	//�����ӵ���ͼ����ͻ�������
	void SetBulletMapPositionX(int px){ fBulletMapPositionX+=px;};
	void SetBulletMapPositionY(int py){ fBulletMapPositionY+=py;};
	void SetBulletDrawPositionX(int px){ fBulletDrawPositionX+=px;};
	void SetBulletDrawPositionY(int py){ fBulletDrawPositionY+=py;};
	//�õ��ӵ���ͼ����ͻ�������
	int GetBulletMapPositionX( ){ return fBulletMapPositionX;};
	int GetBulletMapPositionY( ){ return fBulletMapPositionY;};
	int GetBulletDrawPositionX( ){ return fBulletDrawPositionX;};
	int GetBulletDrawPositionY( ){ return fBulletDrawPositionY;};
	//ʣ���ӵ�
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
	//�ӵ���ͼ����
	int fBulletMapPositionX;
	int fBulletMapPositionY;
	//�ӵ���������
	int fBulletDrawPositionX;
	int fBulletDrawPositionY;

//	static const short sBulletMaxNumber = BULLE_MAXNUMBER;//����ӵ�����
	static short sBulletSurplusNumber;//ʣ���ӵ�����
	
	bool bShootSwitch;//ò����bUseSwitch�����غ�
	bool bUseSwitch;  //�ӵ��Ƿ�����ʹ��
	short sDirection; //�ӵ�����
};

#endif