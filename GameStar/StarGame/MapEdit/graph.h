#ifndef _GRAPH_H
#define _GRAPH_H

class Graph  
{
private:
	int 关卡;	
	bool 截图;
	bool IsWindowed ;	
	DDSURFACEDESC2 ddsd;//DD的页面描述
	bool AddPictrue ();
public:
	Graph();	
	bool Init();					//初始化图像
	BOOL CreateFullScreenSurfaces( );
	BOOL CreateWindowedSurfaces( );
	HRESULT InitClipper();
	void GameRefresh(HINSTANCE hInstance, int nCmdShow);				//刷新屏幕
	void Restore();				//恢复丢失页面
	HRESULT Blt(int x,int y,int src_id,int dest_id,int method); //会自动剪裁的Blt
	//virtual ~Graph();
	void 设置关卡(int 关卡数);
	bool DDGameInitWindowed(THIS_ HWND hwnd);
	int 获得关卡数(){ return 关卡; }
	bool MyFlip();
	bool GetIsWindowed(){ return IsWindowed;};
	void 设置截图(bool j){ 截图 = j;};
	bool 获得截图(){ return 截图 ;};
};


#endif