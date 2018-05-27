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
//地图素材的大小
const short BMPMAPHIGH = 704;
const short BMPMAPWIDE = 256;
//贴的宽和高
const short TILE_WIDE = 32;
const short TILE_HIGH = 32;
const short JIJIA_WIDE = 64;
const short JIJIA_HIGH = 64;
const int MAP_EDIT_BOTTOM_NO_AVAIL = 64;
const int MAP_LAYER	= 3;
//地图编辑区大小
const int MAP_EDIT_AREA_X = XSCREEN - BMPMAPWIDE;
const int MAP_EDIT_AREA_Y = YSCREEN - MAP_EDIT_BOTTOM_NO_AVAIL;
//地图大小;
const int MAP_WIDE = 3200;
const int MAP_HEIGHT = 3200;
//ai随机坐标的范围
const int AI_ACTION_WIDE = 2000;
const int AI_ACTION_HEIGHT = 2000;
//精灵最大数量
const int SPIRIT_POOL_MAX = 100; 
//其他玩家最大数量
const int PLAYER_POOL_MAX = 100;
//键盘方向状态
const short UP		= 1;
const short DOWN	= 2;
const short LEFT	= 3;
const short RIGHT	= 4;
const short STOP	= 5;

//mouse按下状态
const short PUSH_DOWN	= 1;
const short PUSH_UP		= 2;		
const short PUSH_NOT	= 3;

//坐标
const char X = 0;
const char Y = 1;
//精灵贴图的宽和高
const short PLAYER_WIDE = 32;
const short PLAYER_HIGH = 32;
//玩家移动速度
const short PLAYER_MOVE_SPEED = 8;
const short TANK_MOVE_SPEED = 3;
const short JIJIA_MOVE_SPEED = 3;

const short MAP_EDIT_MOVE_SPEED = 50;
//子弹连续射击的最大数目
const short BULLE_MAXNUMBER = 5;
const short BULLE_SPEED = 30;//子弹飞行速度;
//地图空白图块
const short EMPTY_TILE = -1;
const int EMPTY = -1;

//地图最大格子数量
const unsigned int MAPX_GRID = 100;
const unsigned int MAPY_GRID = 100;

enum ESPIRIT_STATUS
{
	BORDER = 200,		//边界
};
enum  //关卡
{
	MAIN_BTN		=	1,	//主菜单
	MAP_EDIT		=	2,	//地图编辑器
	GAME_MAP		=	3,	//游戏地图		
};

#endif