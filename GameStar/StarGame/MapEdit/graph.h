#ifndef _GRAPH_H
#define _GRAPH_H

class Graph  
{
private:
	int �ؿ�;	
	bool ��ͼ;
	bool IsWindowed ;	
	DDSURFACEDESC2 ddsd;//DD��ҳ������
	bool AddPictrue ();
public:
	Graph();	
	bool Init();					//��ʼ��ͼ��
	BOOL CreateFullScreenSurfaces( );
	BOOL CreateWindowedSurfaces( );
	HRESULT InitClipper();
	void GameRefresh(HINSTANCE hInstance, int nCmdShow);				//ˢ����Ļ
	void Restore();				//�ָ���ʧҳ��
	HRESULT Blt(int x,int y,int src_id,int dest_id,int method); //���Զ����õ�Blt
	//virtual ~Graph();
	void ���ùؿ�(int �ؿ���);
	bool DDGameInitWindowed(THIS_ HWND hwnd);
	int ��ùؿ���(){ return �ؿ�; }
	bool MyFlip();
	bool GetIsWindowed(){ return IsWindowed;};
	void ���ý�ͼ(bool j){ ��ͼ = j;};
	bool ��ý�ͼ(){ return ��ͼ ;};
};


#endif