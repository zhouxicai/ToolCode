//��Բ;
#pragma hdrstop 
#include <windows.h>
#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> /*�õ���time����������Ҫ�����ͷ�ļ�*/

//--------------------------------------------------------------------------- 
//#pragma argsused ;
using namespace std;
void _draw_circle_8(HDC hdc, int xc, int yc, int x, int y);
void draw_circle(HDC hdc, int xc, int yc, int r, int fill);
void vdvdv(HDC hdc,HWND hwnd);
bool DrawCircle(int px,int py,int radius,HDC hdc);
void DrawRoundness(HDC hdc,double centre_x, double centre_y ,int w ,int h);
int main(int argc, char* argv[])
{         
	HWND hWnd=FindWindowA(NULL,argv[0]); //�ҵ��������д��ڵľ��;       
	HDC hDC=GetDC(hWnd);//ͨ�����ھ���õ��ô��ڵ��豸�������;        
	//HPEN hPen; //����;       	         
	//       
	//hPen=CreatePen(PS_DASH,2,0x00ff00);//������ɫ����;         
	//SelectObject(hDC,hPen);//�ѻ��������豸���� ;   
	//Arc(hDC,100,100,300,300,350,500,350,500);//��Բ ; 
	//SelectObject(hDC,hPen);//��ԭ ;  

	//for(int i=0;i<500;++i)            
	//	SetPixel(hDC,10+i,10+i,0x0000ff);//�û���İ취��һ����,���һ����������ɫ��32λ��; 
	//	MoveToEx(hDC,20,50,NULL); //���û������;        
	//	LineTo(hDC,520,550);      //�����յ�;         	       


	//����ǻ�Բ�εĺ���;
	//	HDC pdc=GetDC(hWnd);
	//	Ellipse(pdc,50,50,100,100);
	srand((unsigned) time(NULL)); /*������*/

	while (1)
	{
		int x = rand() % 500;
		int y = rand() % 1000; 
		for (int i=1;i<5;i++)
		{
			DrawRoundness(hDC,x,y,i,i);
		}
		Sleep(10);
	}
	
	//DrawCircle(288,288,100,hDC);
	//draw_circle(hDC,290,290,100,0);
	//vdvdv(hDC,hWnd);
	system("pause");      
	return 0; 

} 
void DrawRoundness(HDC hdc,double centre_x, double centre_y ,int w ,int h)
{
	for (double i=0;i<360;i++)
	{		
		centre_x += sin(i)*w;
		centre_y += cos(i)*h;			
		//	SetPixel(hdc,x,y,(COLORREF)0x00000000);		
		SetPixel(hdc,(int)centre_x,(int)centre_y,RGB(200,255,255));		
	}	
}

// �˶Գ���;
void _draw_circle_8(HDC hdc, int xc, int yc, int x, int y) 
{
	// ���� c Ϊ��ɫֵ;
	SetPixel(hdc, xc + x, yc + y, RGB(255,0,0));
	SetPixel(hdc, xc - x, yc + y, RGB(255,0,0));
	SetPixel(hdc, xc + x, yc - y, RGB(255,0,0));
	SetPixel(hdc, xc - x, yc - y, RGB(255,0,0));
	SetPixel(hdc, xc + y, yc + x, RGB(255,0,0));
	SetPixel(hdc, xc - y, yc + x, RGB(255,0,0));
	SetPixel(hdc, xc + y, yc - x, RGB(255,0,0));
	SetPixel(hdc, xc - y, yc - x, RGB(255,0,0));
}

//Bresenham's circle algorithm
void draw_circle(HDC hdc, int xc, int yc, int r, int fill) {
	// (xc, yc) ΪԲ�ģ�r Ϊ�뾶;
	// fill Ϊ�Ƿ����;
	// c Ϊ��ɫֵ;

	// ���Բ��ͼƬ�ɼ������⣬ֱ���˳�;
	//if (xc + r &lt; 0 || xc - r &gt;= hdc-&gt;w ||
	//	yc + r &lt; 0 || yc - r &gt;= hdc-&gt;h) return;

	int x = 0, y = r, yi, d;
	d = 3 - 2 * r;

	if (fill) 
	{
		// �����䣨��ʵ��Բ��;
		while (x <= y) 
		{
			for (yi = x; yi <= y; yi ++)
				_draw_circle_8(hdc, xc, yc, x, yi);

			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y --;
			}
			x++;
		}
	} 
	else 
	{
		// �������䣨������Բ��;
		while (x <= y) {
			_draw_circle_8(hdc, xc, yc, x, y);

			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y --;
			}
			x ++;
		}
	}
}
void vdvdv(HDC hdc,HWND hwnd)
{
	//HDC hdc=BeginPaint(hwnd,&scPaint);
	if (hdc)
	{
		//����ı�;
		SetTextColor(hdc,RGB(255,0,0));
		SetBkColor(hdc,RGB(0,255,0));
		SetBkMode(hdc,TRANSPARENT);
		TextOutA(hdc,10,100,"Welcome!",8);
		//����;
		SetPixel(hdc,10,10,RGB(255,0,0));
		//����,������;
		HPEN gPen=CreatePen(PS_SOLID,1,RGB(0,255,0));
		HPEN oPen=(HPEN)SelectObject(hdc,gPen);
		MoveToEx(hdc,20,20,NULL);
		LineTo(hdc,100,100);
		LineTo(hdc,400,20);
		LineTo(hdc,20,20);
		//������
		gPen=CreatePen(PS_SOLID,1,RGB(0,255,0));
		HBRUSH bBrush=CreateSolidBrush(RGB(0,0,255));
		oPen=(HPEN)SelectObject(hdc,gPen);
		SelectObject(hdc,bBrush);
		Rectangle(hdc,50,150,150,250);
		//FillRect
		RECT rect;
		rect.left=50;
		rect.top=270;
		rect.right=150;
		rect.bottom=370;
		FillRect(hdc,&rect,CreateSolidBrush(RGB(0,0,255)));
		//FrameRect
		rect.left=350;
		rect.top=80;
		rect.right=450;
		rect.bottom=180;
		FrameRect(hdc,&rect,CreateSolidBrush(RGB(255,0,0)));

		//��Բ;
		Ellipse(hdc,200,150,300,250);
		//����Բ;
		Ellipse(hdc,200,270,340,370);
		//�������;
		POINT gPoint[5]={{420,10},{540,140},{600,100},{550,200},{420,10}};
		Polygon(hdc,gPoint,5);

		SelectObject(hdc,oPen);
		DeleteObject(gPen);
		DeleteObject(bBrush);

		//	EndPaint(hwnd,&scPaint);
		ReleaseDC(hwnd,hdc);
	}

}

bool DrawCircle(int px,int py,int radius,HDC hdc)
{
	if (!hdc)
		return false;

	int mx=px,my=py;
	int x=0,y=radius;

	int r=0,g=255,b=0;

	int d=1-radius;    //���(0,R),��һ���е�(1,R-0.5),d=1*1+(R-0.5)*(R-0.5)-R*R=1.25-R,dֻ�����������㣬����С�����ֿ�ʡ��

	while (y>x)    // y>x����һ���޵ĵ�1���˷�Բ
	{
		SetPixel(hdc,x+mx,y+my,		RGB(255,0,0));
		SetPixel(hdc,y+mx,x+my,		RGB(255,0,0));
		SetPixel(hdc,-x+mx,y+my,	RGB(255,0,0));
		SetPixel(hdc,-y+mx,x+my,	RGB(255,0,0));
		SetPixel(hdc,-x+mx,-y+my,	RGB(255,0,0));
		SetPixel(hdc,-y+mx,-x+my,	RGB(255,0,0));
		SetPixel(hdc,x+mx,-y+my,	RGB(255,0,0));
		SetPixel(hdc,y+mx,-x+my,	RGB(255,0,0));
		if (d<0)
		{
			d=d+2*x+3;
		}
		else
		{
			d=d+2*(x-y)+5;
			y--;
		}
		x++;
	}


	return true;
}