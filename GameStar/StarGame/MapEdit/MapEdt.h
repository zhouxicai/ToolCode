#ifndef MAPEDT_H
#define MAPEDT_H
#include <map>
#include <vector>
#include "../../include/define.h"
//#include "../../common/boost_1_55_0/boost/multi_array.hpp"
//#include <boost/multi_array.hpp>

class Mapedit
{
private:
	bool m_EditSave;	//存储框地图选区域开关;
	public:
			 Mapedit () ;
		void MapEditUpdate () ; //地图编辑器;
		void GameMapUpdate () ; //绘制游戏地图;
		void SetbMouseLeftHitMap ( bool zt){ bMouseLeftHitMap = zt;}	; //设定mouse左键，在地图编辑区，按下还是松开;	
		bool GetbMouseLeftHitMap ()	{ return bMouseLeftHitMap;};//获得mouse在地图区按下的状态; 	
		//设定mouse右键，在地图编辑区，按下0,松开1,动作完毕设为2;
		void SetbMouseRightHitMap ( int zt){ iMouseRightHitMap = zt;}	; 		
		int  GetbMouseRightHitMap ()	{ return iMouseRightHitMap;};//获得mouse在地图区按下的状态 ;
		int  GetTileNum  () { return TileBeginX ; }//隐式内联;
		void SetRollScreenFace ( int gun ) { RollScreenFace = gun ;};/*键盘输入控制，调用本函数1上2下3左4右*/
		int  GetRollScreen( int );
		void SetRollScreen( int );
		bool GetCollideState () { return  m_bCollideState ; }
		void SetCollideState ( bool tf ){ m_bCollideState = tf  ;};
		bool GetEditSave () { return  m_EditSave ; }
		void SetEditSave ( bool es ){ m_EditSave = es  ;};

		void SaveCollide	 ( int x , int y );	//存储碰撞设置;
		void 设置大刷子 ( bool 大刷 ) {	大刷子 = 大刷 ; }
		void GetBigBrush () ;	//获得大刷子;	
//		void ClickMap () ;	//点击地图
//		void 松开地图 ();
		bool ReadMapFile () ;
		void SaveMapFile () ;


		void 设置图层( int tc ){ 图层 = tc ;} ;
//		void SetShowAllMapLayer ( bool xs){ mShowAllMapLayer = xs ;} ;
		void RemoveMapTile () ;//删除地图素材;
		void ShowMap ( int 贴宽 , int 贴高 , int MapXAdd , int MapYAdd ) ;
		void RefreshMap( int MapXAdd , int MapYAdd );	//废弃;

	public:
		//点击地图区域事件;
		void RightHitMapDown();
		void RightHitMapUp();
		void LeftHitMapDown();
		void LeftHitMapUp();

		//点击素材区事件
		void LeftHitTileAreaUp () ; //左击松开素材区
		void LeftHitTileArea () ;
		void RightHitTileArea () ;

		//设置mouse选中的帖为空，即取消所选的贴;
		void SetMouseTileToEmpty();

		//获取mouse所在区域;
		bool MouseIsAtMapEditArae();
		bool MouseIsNoAtTileArae();
		//是否选中的单个素材;
		bool IsNoSelectSingleTile();
		//绘制底部界线
		void MapEditBottomLine();
		
		void SetMicroMap();	//设置小地图;		
		void SetBigMap();	//设置大地图;
		void InitBigMap();	//初始化大地图;

		void DrawMouseRightKeySelectRect();	//绘制右键框选矩形;
		void DrawMouseLeftKeySelectRect();	//绘制左键框选矩形;

		//地图格子能不能通过的记录;
		bool mCollideArray[MAPX_GRID][MAPY_GRID] ;

	private:
		//mouse右击地图的行列数;
		int sMouseRightHitMapDownX;
		int sMouseRightHitMapDownY;
		int sMouseRightHitMapUpX;
		int sMouseRightHitMapUpY;

		//mouse左击地图的行列数;
		int sMouseLeftHitMapDownX;
		int sMouseLeftHitMapDownY;
		int sMouseLeftHitMapUpX;
		int sMouseLeftHitMapUpY;
		
		int RollScreenFace;		//滚屏方向;
				
		typedef struct ST_MAP_XY
		{
			int mx;
			int my;
			bool cs;
		}MAP_XY;
		//typedef boost::multi_array<MAP_XY, 3> MultiArray;2016.5.21注释
		//MultiArray mMultiArray;
		//MultiArray::extent_gen extents;

		/*隐藏内部成员函数*///MapX(Y)Add是地图编辑器区显示范围的裁剪，游戏区则不用，直接设为0即可;
		
		void ShowMicroMap () ;	//显示小地图
		
		void 存储框选素材 () ;
		void 存储单个素材 () ;
		void 填充地图();

		void 显示碰撞点 ();
		void CollideCheck ( int ) ;		//碰撞检测;
		void 显示素材 () ;


		//地图数组;
		int MapX[MAP_LAYER][MAPX_GRID][MAPX_GRID] ; 
		int MapY[MAP_LAYER][MAPY_GRID][MAPY_GRID] ; 

		
		//mouse是否在地图编辑区按下的值;
		bool bMouseLeftHitMap ; 
		bool bMouseLeftHitMapDownForCopy;//鼠标是否在地图上按下，用于地图克隆;
		int iMouseRightHitMap ; 
		//MOUSEDOWN选定素材的列行数;
		int TileBeginX ;	
		int TileBeginY ;
		//MOUSEUP框选素材mouse松开后的贴数;
		int TileXEnd ;	
		int TileYEnd ;

		//mouse右键按下-选定地图的列行数;
		int iRightHitMapBeginX ;	
		int iRightHitMapBeginY ;
		int iLeftHitMapBeginX ;	
		int iLeftHitMapBeginY ;
		//mouse右键松开-松开地图的行数;
		int iMapEndX ;	
		int iMapEndY ;

		//用户mouse选定(点击)地图的列行数废弃;
		//int sMouseLeftHitMapDownX ;	
		//int sMouseLeftHitMapDownY ; 
		//用户mouse选定(松开)地图的列行数废弃;
		int MouseUpMapX ;	
		int MouseUpMapY ; 

		//0，1，2，3，4 - 停，上，下，左，右;
		int mRollScreenX  ;	//滚屏值
		int mRollScreenY  ;
		int 图层 ;
		bool mShowAllMapLayer ;//是否显示全部图层;
		
		bool m_bCollideState ; //地图编辑器用于编辑碰撞的开关;
		bool show_x_flag;//显示X碰撞标记;
		bool m_bRollScreenState ;	//滚屏开关
		bool 大刷子 ;
		bool m_bTinyMap;	//小地图开关
		bool bCollide; //游戏当前是否处于碰撞状态;
		int iSelectPathX; 
		int iSelectPathY;

		TCHAR szMapName[MAX_PATH-100];
public://设置碰撞标志;
			void SetXFlag(bool isopen){show_x_flag=isopen;};
			void SetShowAllMapLayer(bool is_show){ mShowAllMapLayer = is_show;};
			void SetTinyMapStatus(bool is_open);
			bool GetTinyMapStatus(){ return m_bTinyMap;}
		void SaveMouseSelectRectangleToFile();//存储鼠标选中的矩形区域到文件中;
		void LoadMouseSelectRectangleFromFile();//从文件中读取鼠标选中的矩形区域;

		void LoadDefaultMap();
		void ResetMapEdit();	//重置地图编辑器;
		void SetMonster(unsigned int cnt);	//生成指定数量的怪物;
};

#endif