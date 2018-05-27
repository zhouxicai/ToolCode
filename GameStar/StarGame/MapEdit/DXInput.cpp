//#include "netbase\NetManager.h"
#include "DXInput.h"
#include "SpecialEfficiency.h"
#include "Player.h"
#include "TimeCount.h"

//#include "packets\CSPlayerCoordinate.h"
TimeCount gSwitchTime;		//�����ؿ��ؼ��;
DxInput dxinput;
//void WINAPI MSG_Thread();
//CSPlayerCoordinate pc_msg;
//HANDLE hpc;

DxInput::DxInput()
{
	gSwitchTime.InitTime();
}
DxInput::~DxInput()
{	
//	pDev->Unacquire();	
//	delete pDev;pDev =NULL;
//	pDev->Release();  
	

//	delete pInput;pInput =NULL;
//	pInput->Release();

//	DXInputInit();
//	SAFE_RELEASE(pDev);

}
void DxInput::DXInputInit()
{
//---------------------------��ʼ��DirectIput---------------------------


	result = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void * *)&pInput,
		NULL);
	if(result != DI_OK) MessageBoxW(hWnd,L"����DirectInput����ʧ�ܣ�",L"����",MB_OK);
	
	result = pInput->CreateDevice(GUID_SysKeyboard,&pDev,NULL);
	if(result != DI_OK) MessageBoxW(hWnd,L"������������װ��ʧ�ܣ�",L"����",MB_OK);
	result = pDev->SetDataFormat (&c_dfDIKeyboard);
	if(result != DI_OK) MessageBoxW(hWnd,L"�趨���ݸ�ʽʧ�ܣ�",L"����",MB_OK);
	result = pDev->SetCooperativeLevel (hWnd,DISCL_EXCLUSIVE|DISCL_FOREGROUND);
	if(result != DI_OK) MessageBoxW(hWnd,L"�趨����Э���㼶ʧ�ܣ�",L"����",MB_OK);
	result = pDev->Acquire(); 
//	if(result != DI_OK) MessageBoxW(hWnd,L"ȡ�������豸ʧ�ܣ�",L"����",MB_OK);
	graph.���ý�ͼ(false);
//	hpc = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)MSG_Thread,NULL,CREATE_SUSPENDED,NULL);
}

short DxInput::DXInputRefresh()
{	if(pDev == NULL)
	{ DXInputInit();}

	result = pDev->GetDeviceState(sizeof(buffer),(LPVOID)& buffer);//��ü�������
	if(result != DI_OK)
	{
		DXInputInit();
		result = pDev->GetDeviceState(sizeof(buffer),(LPVOID)& buffer);//��ü�������
	//	MessageBoxW(hWnd,L"ȡ�ü���״̬ʧ��",L"����",MB_OK);
	}
	//���������Ϣ
	if(KEYDOWN(DIK_ESCAPE))//���**��������
	{	
		if( graph.��ùؿ���() == MAIN_BTN )
		{
			if( MessageBoxW(hWnd,L"�Ƿ��˳���Ϸ��",L"dinput msg",MB_OKCANCEL)!=2 )
			DestroyWindow( hWnd ) ; //�˳�
		}
		//( graph.��ùؿ���() == 3 )
		//{
			graph.���ùؿ�(MAIN_BTN);
			//�����˵����ñ�׼������Ϣ�����˳���������Ϸ�������ñ���Ϣ
			//pDev->Unacquire();	
			//pDev->Release();  
			//pInput->Release();
			//return 0;
			//goto EXIT;
		//}
		//else
		//{
		//	MessageBoxW(hWnd,L"�˳���Ϸ��",L"dinput msg",MB_OK);
		//	DestroyWindow( hWnd ) ; //�˳�
		//}
	}//EXIT:;

	if(KEYDOWN(DIK_UP))	      
	{	
		oPlayer.SetTankFace ( 1 ) ; //̹�������ƶ�	
		oMapedit.SetRollScreenFace( 1 ) ; //��ͼ���¹���
	}
	else if(KEYDOWN(DIK_DOWN))	      
	{					      
		oPlayer.SetTankFace ( 2 ) ; //̹�������ƶ�
		oMapedit.SetRollScreenFace( 2 ) ; //��ͼ���¹���
	}
	else if(KEYDOWN(DIK_LEFT))	      
	{					      
		oPlayer.SetTankFace ( 3 ) ; //̹�������ƶ�
		oMapedit.SetRollScreenFace( 3 ) ; //��ͼ���¹���
	}
	else if(KEYDOWN(DIK_RIGHT))	      
	{					      
		oPlayer.SetTankFace ( 4 ) ; //̹�������ƶ�
		oMapedit.SetRollScreenFace( 4 ) ; //��ͼ���¹���
	}
	else oPlayer.SetTankFace ( 0 ) ;//ֹͣ�ƶ�

	//���ܿ�ݼ�
	if(KEYDOWN(DIK_TAB))// TAB ��
	{	
		oMapedit.SetCollideState(true);
	}
	if(KEYDOWN(DIK_Q))
	{
		oMapedit.SetCollideState(false);
	}
	if(KEYDOWN(DIK_LSHIFT))
	{
		oMapedit.���ô�ˢ��( TRUE ) ; //��ȫ��ͼˢ��		
	}
	if(KEYDOWN(DIK_Z))
	{
		oMapedit.���ô�ˢ��( FALSE ) ; //�ر�ȫ��ͼˢ��
	}
	if (KEYDOWN(DIK_CAPSLOCK))
	{
		if( graph.��ùؿ���() != MAP_EDIT )return 0;
		oMapedit.SetEditSave(true);
		oMapedit.SetMouseTileToEmpty();
		MessageBoxW(hWnd,L"����[�洢��ѡ����]���ܣ�",L"Key:CAPSLOCK-A",MB_OK);
	}
	if (KEYDOWN(DIK_A))
	{
		if( graph.��ùؿ���() != MAP_EDIT )return 0;
		oMapedit.SetEditSave(false);
		MessageBoxW(hWnd,L"�ر�[�洢��ѡ����]���ܣ�",L"Key:CAPSLOCK-A",MB_OK);
	}

	if(KEYDOWN(DIK_1))
	{
		oMapedit.����ͼ��( 0 ) ;
	//	MessageBoxW(hWnd,L"�����༭�� 1 ��ͼ",L"��ʾ",MB_OKCANCEL);
	}
	if(KEYDOWN(DIK_2))
	{
		oMapedit.����ͼ��( 1 ) ;
	}
	if(KEYDOWN(DIK_3))
	{
		oMapedit.����ͼ��( 2 ) ;
	}
	if(KEYDOWN(DIK_8))
	{
		oMapedit.SetShowAllMapLayer( false ) ;
	}
	if(KEYDOWN(DIK_9))
	{		
		oMapedit.SetShowAllMapLayer( true ) ;
	}
	if(KEYDOWN(DIK_7))
	{
		if (gSwitchTime.GetNowTime() < 1)
		{
			return 0;
		}
		gSwitchTime.ResetTime();

		if(graph.��ý�ͼ())
		{
			graph.���ý�ͼ(false);
			DXInputInit();
		}
		else
		{
			graph.���ý�ͼ(true);
			pDev->Unacquire();	
			pDev->Release();  
			pInput->Release();
		}	
	}
	if(KEYDOWN(DIK_SPACE))
	{
		//int inu = oPlayer.m_bullePool.at(0)->GetBulletSurplusNumber(); 
	//	//oPlayer.m_bullePool.at(0)->SetShootSwitch(true);
		//if(inu > 0)
		//	oPlayer.m_bullePool.at(0)->SetBulletSurplusNumber(-1);
		//else
		//	oPlayer.m_bullePool.at(0)->SetBulletSurplusNumber(10);
		
		oPlayer.BeginShoot();	
	}
	if(KEYDOWN(DIK_M))
	{	//С��ͼ����;	
		if (gSwitchTime.GetNowTime() < 1)
		{
			return 0;
		}
		gSwitchTime.ResetTime();

		if (oMapedit.GetTinyMapStatus())
		{
			oMapedit.SetTinyMapStatus(false);
		} 
		else
		{
			oMapedit.SetTinyMapStatus( true ) ; 
		}		
	}
	if(KEYDOWN(DIK_R))
	{
		if (gRainKeepTime.GetNowTime()<cse.GetRainKeepTime())
		{
			return 0;
		}
		cse.InitRain();
	}
	if(KEYDOWN(DIK_S))
	{
		if (gSnowKeepTime.GetNowTime() < 30)
		{
			return 0;
		}
		gSnowKeepTime.ResetTime();
		cse.SnowSwitch(true);
	}
	if(KEYDOWN(DIK_L))
	{
		if( cse.GetLightBool() == true)
			cse.LightSwitch(false);
		else
			cse.LightSwitch(true);
	}
	return 0;
}
