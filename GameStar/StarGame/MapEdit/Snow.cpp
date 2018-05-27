#include <windows.h>
#include "../../include/define.h"
#include "main.h"
#include "Snow.h"

CSnowMgr oSnowMgr;

CSnowMgr::CSnowMgr() 
{
	Init();
};

void CSnowMgr::Init()
{
	for (size_t i=0;i<MAX_SNOW_COUNT;i++)
	{
		mSnow[i].SetPosition(rand()%XSCREEN,rand()%YSCREEN);
		mSnow[i].SetSize(rand()%SNOW_SIZE);
	}
}


void CSnowMgr::Snowing(int count)
{
	//绘制随机圆球，模拟下雪效果;
	HDC hDC ;	DDS[SBuffer]->GetDC(&hDC);
	SelectObject(hDC,CreatePen(PS_SOLID,1,RGB(255,255,255)));
	///COLORREF crCol = ::GetPixel(hDC,200, 200); //取得（200, 200）处的颜色值
	///RECT rc ;GetWindowRect(hWnd,&rc);	
	int  mix=5;//最小直径;
	int base  = 5;
	int wind_face = rand()%2;
	int i = 0;
	for( ; i<count ;i++ )
	{
		//if (mSnow[i].GetX() < 0)
		//{
		//	mSnow[i].SetPosition(XSCREEN+rand()%10,rand()%YSCREEN);
		//}
		//if (mSnow[i].GetX() > XSCREEN)
		//{
		//	mSnow[i].SetPosition(-rand()%10,rand()%YSCREEN);
		//}
		
		if (wind_face)
		{
			mSnow[i].AddX();
		}
		else mSnow[i].DelX();

		if (base>rand()%10)
		{
			mSnow[i].AddX();
		}
		else mSnow[i].DelX();

		mSnow[i].SetY(mSnow[i].GetY()+3);

		//	COLORREF color = RGB( rand()%255,rand()%255,rand()%255 );
		//	::SetPixel(hDC,x, y, RGB( 155,155,155 ));//绘制随机粒子
		//绘制随机小圆球;
		::Ellipse(hDC , 
			mSnow[i].GetX() + oMapedit.GetRollScreen(0), mSnow[i].GetY() + oMapedit.GetRollScreen(1), 
			mSnow[i].GetX() + mix + mSnow[i].GetSize() + oMapedit.GetRollScreen(0) ,  
			mSnow[i].GetY() + mix + mSnow[i].GetSize() + oMapedit.GetRollScreen(1) );
		
		if (mSnow[i].GetY() > YSCREEN - oMapedit.GetRollScreen(1))
		{
			mSnow[i].SetPosition(rand()%XSCREEN,-rand()%YSCREEN);
		}
	}
	DDS[SBuffer]->ReleaseDC(hDC);
}