#ifndef _MAP_DEFINE_H_
#define _MAP_DEFINE_H_
#include "InorganicBase.h"
#include "OrganismsBase.h"

class CBotany		//ֲ��
{
	int mFlower;
	int mGeology;

};

class CAnimal	//������
{
	//ʳ�⶯��
	int tiger;		//��
	int lion;		//ʨ
	int leopard;	//��
	int bear;		//��
	//��ʳ����

	//����

	//�ɳ�

	//����

	//������Ѫ����

	//����

	//����

	//����	

	//����

	//Ϻ��

	//����
};

class CFlower		//����
{
	int chrysanthemum;//�ջ�
	int sunflower	;//���տ�
	int tulip		;//������
	int rose		;//õ��
	int peony		;//ĵ��
	int grass		;//С��
};
class CTree		//��ľ
{
	int spruce;		//��ɼ

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
	int mTileGUID;		//�����
	int mx,my,mz;		//x,y����,z:�߶�
	int temperature;	//�¶�;
	int humidity;		//ʪ��;
	int luminance;		//����;
	int mSmell;			//��ζ;
	int mTaste;			//ζ��;
	int mVisibility;	//�ɼ���;
	int	mWindSpeed;		//����;				
	int mWindOrientation;//����;
	int animal;		//��̬����
	CLand mLand;	//��������

};
#endif