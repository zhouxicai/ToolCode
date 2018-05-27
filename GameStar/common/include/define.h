#ifndef _DEFINE_H
#define _DEFINE_H
 
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#define XSCREEN	GetSystemMetrics(SM_CXSCREEN)
#define YSCREEN	GetSystemMetrics(SM_CYSCREEN)
//#define XSCREEN	1024
//#define YSCREEN	768
//��ͼ�زĵĴ�С
const short BMPMAPHIGH = 704;
const short BMPMAPWIDE = 256;
//���Ŀ�͸�
const short TILE_WIDE = 32;
const short TILE_HIGH = 32;
const short JIJIA_WIDE = 64;
const short JIJIA_HIGH = 64;
const int MAP_EDIT_BOTTOM_NO_AVAIL = 64;
const int MAP_LAYER	= 3;
//��ͼ�༭����С
const int MAP_EDIT_AREA_X = XSCREEN - BMPMAPWIDE;
const int MAP_EDIT_AREA_Y = YSCREEN - MAP_EDIT_BOTTOM_NO_AVAIL;
//��ͼ��С;
const int MAP_WIDE = 3200;
const int MAP_HEIGHT = 3200;
//ai�������ķ�Χ
const int AI_ACTION_WIDE = 2000;
const int AI_ACTION_HEIGHT = 2000;
//�����������
const int SPIRIT_POOL_MAX = 100; 
//��������������
const int PLAYER_POOL_MAX = 100;
//���̷���״̬
const short UP		= 1;
const short DOWN	= 2;
const short LEFT	= 3;
const short RIGHT	= 4;
const short STOP	= 5;

//mouse����״̬
const short PUSH_DOWN	= 1;
const short PUSH_UP		= 2;		
const short PUSH_NOT	= 3;

//����
const char X = 0;
const char Y = 1;
//������ͼ�Ŀ�͸�
const short PLAYER_WIDE = 32;
const short PLAYER_HIGH = 32;
//����ƶ��ٶ�
const short PLAYER_MOVE_SPEED = 8;
const short TANK_MOVE_SPEED = 3;
const short JIJIA_MOVE_SPEED = 3;

const short MAP_EDIT_MOVE_SPEED = 50;
//�ӵ���������������Ŀ
const short BULLE_MAXNUMBER = 5;
const short BULLE_SPEED = 30;//�ӵ������ٶ�;
//��ͼ�հ�ͼ��
const short EMPTY_TILE = -1;
const int EMPTY = -1;

//��ͼ����������
const unsigned int MAPX_GRID = 100;
const unsigned int MAPY_GRID = 100;

enum ESPIRIT_STATUS
{
	BORDER = 200,		//�߽�
};
enum  //�ؿ�
{
	MAIN_BTN		=	1,	//���˵�
	MAP_EDIT		=	2,	//��ͼ�༭��
	GAME_MAP		=	3,	//��Ϸ��ͼ		
};

#endif