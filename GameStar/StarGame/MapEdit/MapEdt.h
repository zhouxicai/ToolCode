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
	bool m_EditSave;	//�洢���ͼѡ���򿪹�;
	public:
			 Mapedit () ;
		void MapEditUpdate () ; //��ͼ�༭��;
		void GameMapUpdate () ; //������Ϸ��ͼ;
		void SetbMouseLeftHitMap ( bool zt){ bMouseLeftHitMap = zt;}	; //�趨mouse������ڵ�ͼ�༭�������»����ɿ�;	
		bool GetbMouseLeftHitMap ()	{ return bMouseLeftHitMap;};//���mouse�ڵ�ͼ�����µ�״̬; 	
		//�趨mouse�Ҽ����ڵ�ͼ�༭��������0,�ɿ�1,���������Ϊ2;
		void SetbMouseRightHitMap ( int zt){ iMouseRightHitMap = zt;}	; 		
		int  GetbMouseRightHitMap ()	{ return iMouseRightHitMap;};//���mouse�ڵ�ͼ�����µ�״̬ ;
		int  GetTileNum  () { return TileBeginX ; }//��ʽ����;
		void SetRollScreenFace ( int gun ) { RollScreenFace = gun ;};/*����������ƣ����ñ�����1��2��3��4��*/
		int  GetRollScreen( int );
		void SetRollScreen( int );
		bool GetCollideState () { return  m_bCollideState ; }
		void SetCollideState ( bool tf ){ m_bCollideState = tf  ;};
		bool GetEditSave () { return  m_EditSave ; }
		void SetEditSave ( bool es ){ m_EditSave = es  ;};

		void SaveCollide	 ( int x , int y );	//�洢��ײ����;
		void ���ô�ˢ�� ( bool ��ˢ ) {	��ˢ�� = ��ˢ ; }
		void GetBigBrush () ;	//��ô�ˢ��;	
//		void ClickMap () ;	//�����ͼ
//		void �ɿ���ͼ ();
		bool ReadMapFile () ;
		void SaveMapFile () ;


		void ����ͼ��( int tc ){ ͼ�� = tc ;} ;
//		void SetShowAllMapLayer ( bool xs){ mShowAllMapLayer = xs ;} ;
		void RemoveMapTile () ;//ɾ����ͼ�ز�;
		void ShowMap ( int ���� , int ���� , int MapXAdd , int MapYAdd ) ;
		void RefreshMap( int MapXAdd , int MapYAdd );	//����;

	public:
		//�����ͼ�����¼�;
		void RightHitMapDown();
		void RightHitMapUp();
		void LeftHitMapDown();
		void LeftHitMapUp();

		//����ز����¼�
		void LeftHitTileAreaUp () ; //����ɿ��ز���
		void LeftHitTileArea () ;
		void RightHitTileArea () ;

		//����mouseѡ�е���Ϊ�գ���ȡ����ѡ����;
		void SetMouseTileToEmpty();

		//��ȡmouse��������;
		bool MouseIsAtMapEditArae();
		bool MouseIsNoAtTileArae();
		//�Ƿ�ѡ�еĵ����ز�;
		bool IsNoSelectSingleTile();
		//���Ƶײ�����
		void MapEditBottomLine();
		
		void SetMicroMap();	//����С��ͼ;		
		void SetBigMap();	//���ô��ͼ;
		void InitBigMap();	//��ʼ�����ͼ;

		void DrawMouseRightKeySelectRect();	//�����Ҽ���ѡ����;
		void DrawMouseLeftKeySelectRect();	//���������ѡ����;

		//��ͼ�����ܲ���ͨ���ļ�¼;
		bool mCollideArray[MAPX_GRID][MAPY_GRID] ;

	private:
		//mouse�һ���ͼ��������;
		int sMouseRightHitMapDownX;
		int sMouseRightHitMapDownY;
		int sMouseRightHitMapUpX;
		int sMouseRightHitMapUpY;

		//mouse�����ͼ��������;
		int sMouseLeftHitMapDownX;
		int sMouseLeftHitMapDownY;
		int sMouseLeftHitMapUpX;
		int sMouseLeftHitMapUpY;
		
		int RollScreenFace;		//��������;
				
		typedef struct ST_MAP_XY
		{
			int mx;
			int my;
			bool cs;
		}MAP_XY;
		//typedef boost::multi_array<MAP_XY, 3> MultiArray;2016.5.21ע��
		//MultiArray mMultiArray;
		//MultiArray::extent_gen extents;

		/*�����ڲ���Ա����*///MapX(Y)Add�ǵ�ͼ�༭������ʾ��Χ�Ĳü�����Ϸ�����ã�ֱ����Ϊ0����;
		
		void ShowMicroMap () ;	//��ʾС��ͼ
		
		void �洢��ѡ�ز� () ;
		void �洢�����ز� () ;
		void ����ͼ();

		void ��ʾ��ײ�� ();
		void CollideCheck ( int ) ;		//��ײ���;
		void ��ʾ�ز� () ;


		//��ͼ����;
		int MapX[MAP_LAYER][MAPX_GRID][MAPX_GRID] ; 
		int MapY[MAP_LAYER][MAPY_GRID][MAPY_GRID] ; 

		
		//mouse�Ƿ��ڵ�ͼ�༭�����µ�ֵ;
		bool bMouseLeftHitMap ; 
		bool bMouseLeftHitMapDownForCopy;//����Ƿ��ڵ�ͼ�ϰ��£����ڵ�ͼ��¡;
		int iMouseRightHitMap ; 
		//MOUSEDOWNѡ���زĵ�������;
		int TileBeginX ;	
		int TileBeginY ;
		//MOUSEUP��ѡ�ز�mouse�ɿ��������;
		int TileXEnd ;	
		int TileYEnd ;

		//mouse�Ҽ�����-ѡ����ͼ��������;
		int iRightHitMapBeginX ;	
		int iRightHitMapBeginY ;
		int iLeftHitMapBeginX ;	
		int iLeftHitMapBeginY ;
		//mouse�Ҽ��ɿ�-�ɿ���ͼ������;
		int iMapEndX ;	
		int iMapEndY ;

		//�û�mouseѡ��(���)��ͼ������������;
		//int sMouseLeftHitMapDownX ;	
		//int sMouseLeftHitMapDownY ; 
		//�û�mouseѡ��(�ɿ�)��ͼ������������;
		int MouseUpMapX ;	
		int MouseUpMapY ; 

		//0��1��2��3��4 - ͣ���ϣ��£�����;
		int mRollScreenX  ;	//����ֵ
		int mRollScreenY  ;
		int ͼ�� ;
		bool mShowAllMapLayer ;//�Ƿ���ʾȫ��ͼ��;
		
		bool m_bCollideState ; //��ͼ�༭�����ڱ༭��ײ�Ŀ���;
		bool show_x_flag;//��ʾX��ײ���;
		bool m_bRollScreenState ;	//��������
		bool ��ˢ�� ;
		bool m_bTinyMap;	//С��ͼ����
		bool bCollide; //��Ϸ��ǰ�Ƿ�����ײ״̬;
		int iSelectPathX; 
		int iSelectPathY;

		TCHAR szMapName[MAX_PATH-100];
public://������ײ��־;
			void SetXFlag(bool isopen){show_x_flag=isopen;};
			void SetShowAllMapLayer(bool is_show){ mShowAllMapLayer = is_show;};
			void SetTinyMapStatus(bool is_open);
			bool GetTinyMapStatus(){ return m_bTinyMap;}
		void SaveMouseSelectRectangleToFile();//�洢���ѡ�еľ��������ļ���;
		void LoadMouseSelectRectangleFromFile();//���ļ��ж�ȡ���ѡ�еľ�������;

		void LoadDefaultMap();
		void ResetMapEdit();	//���õ�ͼ�༭��;
		void SetMonster(unsigned int cnt);	//����ָ�������Ĺ���;
};

#endif