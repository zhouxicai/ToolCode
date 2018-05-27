#include "SpecialEfficiency.h"
#include <math.h>
//#include <dmusicc.h>//DMUS_SEG_REPEAT_INFINITE
#include "DirectXAudio.h"
//#include "Core_Global.h"
#include "SoundMgr.h"

#include "../../include/define.h"

CSpecialEfficiency cse;

#include "TimeCount.h"
//按键计时器
TimeCount gRainKeepTime;	//下雨持续时间;
TimeCount gSnowKeepTime;	//下雪持续时间;
CSpecialEfficiency::CSpecialEfficiency():nr(1),round_x(1),round_y(100)
,mWindFace(0),mWindAngle(0),mRainCount(0),mRainKeepTime(30),mRainCountChange(false)
{
	gRainKeepTime.InitTime();
	gSnowKeepTime.InitTime();
};
void CSpecialEfficiency::InitRain()
{  
	mWindFace = rand()%2;; 
	mWindAngle = rand()%10; 
	mRainCount = rand()%2300 + 200; 
	if (XSCREEN > 1500)
	{	//超高分辨率下，雨滴数量增加;
		mRainCount += 1000;
	}
	mRainKeepTime = rand()%60 + 20; 
	mRainCountChange = true;
	b_rain = true;
	
	gRainKeepTime.ResetTime();
};
void CSpecialEfficiency::StopRain()
{
	oDirectXAudio.SetWavState(false);
	oDirectXAudio.StopWav();
//	oDirectXAudio.PlayMicMidiWav();
	//	oMusicChannel.Stop();
	//	oSoundMgr.StopSounds();
}
void CSpecialEfficiency::RainRandom()
{	
	if (gRainKeepTime.GetNowTime() > mRainKeepTime)
	{	//每次下雨的时间-秒数;
		gRainKeepTime.InitTime();
		RainSwitch(false);
		return;
	}
	//音效;	
	if (!oDirectXAudio.GetWavState())
	{
		oDirectXAudio.PlayAudio(1);//DMUS_SEG_REPEAT_INFINITE
		oDirectXAudio.SetWavState(true);
	//	oDirectXAudio.StopMicMidiWav();//停止播放背景音乐;
	//	oMusicChannel.Play();
	//	oSoundMgr.PlaySounds(1);
	}
	

	//static_cast （没有类型检查）dynamic_case(进行类型检查) 
	//类型转换示例
	//float f = 1.3; int x =2;
	//x = static_cast<int>(f);
	
	//时间过半的话，改变雨量;
	if (mRainCountChange && gRainKeepTime.GetNowTime() > mRainKeepTime/2)
	{	
		if ( mRainCount < 1500)
		{
			mRainCount+=1000; //增大雨量;
		}
		else
		{
			mRainCount-=1000;
		}
		mRainCountChange = false;
	} 

	//绘制雨滴;
	HDC hdc ;	DDS[SBuffer]->GetDC(&hdc);
	SelectObject(hdc,CreatePen(PS_SOLID,1,RGB(250,250,250)));
	int x(0),y(0); 
	for( short index = 0 ; index<mRainCount ;index++)
	{   
		x = rand()%XSCREEN;
		y = rand()%YSCREEN;
		MoveToEx(hdc,x,y,NULL);		
		//设置风向	
		switch (mWindFace)
		{
		case EAST:
			LineTo  (hdc,x-mWindAngle ,y+6);
			break;
		case WEST:
			LineTo  (hdc,x+mWindAngle ,y+6);
			break;
		default:
			LineTo  (hdc,x ,y+6);
		}
	}
	DDS[SBuffer]->ReleaseDC(hdc);
}

void CSpecialEfficiency::SnowRandom(UINT count)
{
	if (gSnowKeepTime.GetNowTime() > 20)
	{
		SnowSwitch(false);
		return;
	}
	//绘制随机圆球，模拟下雪效果
	HDC hDC ;	DDS[SBuffer]->GetDC(&hDC);
	SelectObject(hDC,CreatePen(PS_SOLID,1,RGB(255,255,255)));
	///COLORREF crCol = ::GetPixel(hDC,200, 200); //取得（200, 200）处的颜色值
	///RECT rc ;GetWindowRect(hWnd,&rc);	
	int x ,y ,rx,ry,mix; 
	rx=ry=5;//圆大小
	mix=6;//最小直径
	for( UINT index = 0 ; index<count ;index++ )
	{
		x = rand()%XSCREEN;
		y = rand()%YSCREEN;
		rx = rand()%ry;
	//	COLORREF color = RGB( rand()%255,rand()%255,rand()%255 );
	//	::SetPixel(hDC,x, y, RGB( 155,155,155 ));//绘制随机粒子
		::Ellipse(hDC , x , y , x+mix+rx , y+mix+rx);//绘制随机小圆球
	}
	DDS[SBuffer]->ReleaseDC(hDC);   //别忘了释放DC
}

void CSpecialEfficiency::fire()
{
	//初始化颜色索引值
    //for(int i=10;i<255;i++)
    //{

    //    color_r[i]=256*((i/200.0));
    //    if(color_r[i]>255)
    //        color_r[i]=255;
    //    color_g[i]=256*((i/220.0))*((i/220.0));
    //    color_b[i]=256*((i/220.0))*((i/220.0));//10;
    //    if(color_b[i]>255)
    //        color_b[i]=255;
    //    if(color_g[i]>255)
    //        color_g[i]=255;
    //}
}

void CSpecialEfficiency::LightIntensity()
{
		DDSURFACEDESC2 dds2; 
//		RtlZeroMemory(&dds,sizeof(dds));
//		dds.dwSize = sizeof(dds);
		RtlZeroMemory(&dds2,sizeof(dds2));
		dds2.dwSize = sizeof(dds2);

		DDS[SBuffer]->Lock(NULL,&dds2,DDLOCK_WAIT,NULL);
		BYTE * Bitmap = (BYTE*)dds2.lpSurface;//锁定后的页面信息存储在这里，每次LOCK信息都可能不一样

		int pos(0);
		for( int y(0) ; y<100 ;y++ )
		{
			for( int x(0) ; x<200 ;x++ )
			{
				Bitmap[pos] = Bitmap[pos]>>1; pos++;  //R
				Bitmap[pos] = Bitmap[pos]>>1; pos++;  //G
				Bitmap[pos] = Bitmap[pos]>>1; pos+=2; //B
			}
			pos += (dds2.lPitch - 200*4);
		}
		DDS[SBuffer]->Unlock(NULL);
}

void CSpecialEfficiency::light_asm()
{	DDSURFACEDESC2 dds2; 
	RtlZeroMemory(&dds2,sizeof(dds2));
	dds2.dwSize = sizeof(dds2);
//	DDS[SBuffer]->Lock(NULL,&dds2,DDLOCK_WAIT,NULL);
	BYTE * Bitmap = (BYTE*)dds2.lpSurface;//锁定后的页面信息存储在这里，每次LOCK信息都可能不一样;

	LPDIRECTDRAWSURFACE7 lps = DDS[SBuffer] - 8;
	__int64 mask = 0x4040404040404040;
	int tt = 10*dds2.lPitch + 10*4; 
	int hight = YSCREEN/3;
	int wide = XSCREEN/3;
	_asm
	{
		movq mm1 ,mask;
		mov eax,lps;//后台缓存的指针减8;
		add eax,tt;
		mov ecx,hight;//要处理的高度;
outloop:
		push eax;
		mov ebx,wide;//要处理的宽度/2;
innloop:
		movq mm0,[eax+ebx*8];
		psubusb mm0,mm1;//如果要加亮，请把psubusb改成paddusb;
		movq[eax+ebx*8],mm0;
		dec ebx;
		jnz innloop;
		pop eax;
		add eax,dds2.lPitch;
		dec ecx;
		jnz outloop;
		emms;

	}

//	DDS[SBuffer]->Unlock(NULL);
}

void CSpecialEfficiency::transparent()
{
	DDSURFACEDESC2 dds; 
	RtlZeroMemory(&dds,sizeof(dds));
	dds.dwSize = sizeof(dds);
	DDS[SBuffer]->Lock(NULL,&dds,DDLOCK_WAIT,NULL);

	DDSURFACEDESC2 dds2; 
	RtlZeroMemory(&dds2,sizeof(dds2));
	dds2.dwSize = sizeof(dds2);
	DDS[STile]->Lock(NULL,&dds2,DDLOCK_WAIT,NULL);


	BYTE * Bitmap = (BYTE*)dds2.lpSurface;//锁定后的页面信息存储在这里，每次LOCK信息都可能不一样
	LPDIRECTDRAWSURFACE7 lps = DDS[SBuffer];
	LPDIRECTDRAWSURFACE7 lpb = DDS[STile];
	
	__int64 mask = 0x7F7F7F7F7F7F7F7F;
	int tt = 0*dds2.lPitch + 0*4;
	int hight = YSCREEN;
	int wide = XSCREEN/2;

	__asm
	{
//		movq edx ,dds2;
		mov eax,dds;
		add eax,tt;
		mov ecx,hight;
outloop:
		push eax;
		push edx;
		mov ebx,wide;
innloop:
		movq mm0 ,[eax];
		psrlw mm0,1;
//		movq mmq,[edx];
		pand mm0,mask;
		paddusb mm0,mm1;
		movq[eax],mm0;
		add eax,8;
		add edx,8;
		dec ebx;
		jnz innloop;
		pop edx;
		pop eax;
		add eax,dds.lPitch;
		add edx,dds2.lPitch;
		dec ecx;
		jnz outloop;
		emms;
	}

	DDS[SBuffer]->Unlock(NULL);

}

void CSpecialEfficiency::TestYuan(double r)
{
	HDC hDC ;	DDS[SBuffer]->GetDC(&hDC);
	//x = rand()%XSCREEN;
	//y = rand()%YSCREEN;

	rand();
	for (double i=0; i<360; i+=2)
	{
		round_x+= nr* sin(i);
		round_y+= nr* cos(i);
		::SetPixel(hDC,(int)round_x, (int)round_y, RGB( 255,55,55 ));//绘制随机粒子
	}
	nr=60;
#if 1
	round_x+=3;
	if (round_x>200)
	{
		round_x=10;
	}
#endif
	DDS[SBuffer]->ReleaseDC(hDC); 
}