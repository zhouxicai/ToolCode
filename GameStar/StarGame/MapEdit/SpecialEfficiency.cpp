#include "SpecialEfficiency.h"
#include <math.h>
//#include <dmusicc.h>//DMUS_SEG_REPEAT_INFINITE
#include "DirectXAudio.h"
//#include "Core_Global.h"
#include "SoundMgr.h"

#include "../../include/define.h"

CSpecialEfficiency cse;

#include "TimeCount.h"
//������ʱ��
TimeCount gRainKeepTime;	//�������ʱ��;
TimeCount gSnowKeepTime;	//��ѩ����ʱ��;
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
	{	//���߷ֱ����£������������;
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
	{	//ÿ�������ʱ��-����;
		gRainKeepTime.InitTime();
		RainSwitch(false);
		return;
	}
	//��Ч;	
	if (!oDirectXAudio.GetWavState())
	{
		oDirectXAudio.PlayAudio(1);//DMUS_SEG_REPEAT_INFINITE
		oDirectXAudio.SetWavState(true);
	//	oDirectXAudio.StopMicMidiWav();//ֹͣ���ű�������;
	//	oMusicChannel.Play();
	//	oSoundMgr.PlaySounds(1);
	}
	

	//static_cast ��û�����ͼ�飩dynamic_case(�������ͼ��) 
	//����ת��ʾ��
	//float f = 1.3; int x =2;
	//x = static_cast<int>(f);
	
	//ʱ�����Ļ����ı�����;
	if (mRainCountChange && gRainKeepTime.GetNowTime() > mRainKeepTime/2)
	{	
		if ( mRainCount < 1500)
		{
			mRainCount+=1000; //��������;
		}
		else
		{
			mRainCount-=1000;
		}
		mRainCountChange = false;
	} 

	//�������;
	HDC hdc ;	DDS[SBuffer]->GetDC(&hdc);
	SelectObject(hdc,CreatePen(PS_SOLID,1,RGB(250,250,250)));
	int x(0),y(0); 
	for( short index = 0 ; index<mRainCount ;index++)
	{   
		x = rand()%XSCREEN;
		y = rand()%YSCREEN;
		MoveToEx(hdc,x,y,NULL);		
		//���÷���	
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
	//�������Բ��ģ����ѩЧ��
	HDC hDC ;	DDS[SBuffer]->GetDC(&hDC);
	SelectObject(hDC,CreatePen(PS_SOLID,1,RGB(255,255,255)));
	///COLORREF crCol = ::GetPixel(hDC,200, 200); //ȡ�ã�200, 200��������ɫֵ
	///RECT rc ;GetWindowRect(hWnd,&rc);	
	int x ,y ,rx,ry,mix; 
	rx=ry=5;//Բ��С
	mix=6;//��Сֱ��
	for( UINT index = 0 ; index<count ;index++ )
	{
		x = rand()%XSCREEN;
		y = rand()%YSCREEN;
		rx = rand()%ry;
	//	COLORREF color = RGB( rand()%255,rand()%255,rand()%255 );
	//	::SetPixel(hDC,x, y, RGB( 155,155,155 ));//�����������
		::Ellipse(hDC , x , y , x+mix+rx , y+mix+rx);//�������СԲ��
	}
	DDS[SBuffer]->ReleaseDC(hDC);   //�������ͷ�DC
}

void CSpecialEfficiency::fire()
{
	//��ʼ����ɫ����ֵ
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
		BYTE * Bitmap = (BYTE*)dds2.lpSurface;//�������ҳ����Ϣ�洢�����ÿ��LOCK��Ϣ�����ܲ�һ��

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
	BYTE * Bitmap = (BYTE*)dds2.lpSurface;//�������ҳ����Ϣ�洢�����ÿ��LOCK��Ϣ�����ܲ�һ��;

	LPDIRECTDRAWSURFACE7 lps = DDS[SBuffer] - 8;
	__int64 mask = 0x4040404040404040;
	int tt = 10*dds2.lPitch + 10*4; 
	int hight = YSCREEN/3;
	int wide = XSCREEN/3;
	_asm
	{
		movq mm1 ,mask;
		mov eax,lps;//��̨�����ָ���8;
		add eax,tt;
		mov ecx,hight;//Ҫ����ĸ߶�;
outloop:
		push eax;
		mov ebx,wide;//Ҫ����Ŀ��/2;
innloop:
		movq mm0,[eax+ebx*8];
		psubusb mm0,mm1;//���Ҫ���������psubusb�ĳ�paddusb;
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


	BYTE * Bitmap = (BYTE*)dds2.lpSurface;//�������ҳ����Ϣ�洢�����ÿ��LOCK��Ϣ�����ܲ�һ��
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
		::SetPixel(hDC,(int)round_x, (int)round_y, RGB( 255,55,55 ));//�����������
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