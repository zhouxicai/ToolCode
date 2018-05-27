//#include "netbase\NetManager.h"
#include "DXInput.h"
#include "SpecialEfficiency.h"
#include "Player.h"
#include "TimeCount.h"

//#include "packets\CSPlayerCoordinate.h"
TimeCount gSwitchTime;		//各开关开阖间隔;
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
//---------------------------初始化DirectIput---------------------------


	result = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void * *)&pInput,
		NULL);
	if(result != DI_OK) MessageBoxW(hWnd,L"建立DirectInput对象失败！",L"出错！",MB_OK);
	
	result = pInput->CreateDevice(GUID_SysKeyboard,&pDev,NULL);
	if(result != DI_OK) MessageBoxW(hWnd,L"建立键盘输入装置失败！",L"出错！",MB_OK);
	result = pDev->SetDataFormat (&c_dfDIKeyboard);
	if(result != DI_OK) MessageBoxW(hWnd,L"设定数据格式失败！",L"出错！",MB_OK);
	result = pDev->SetCooperativeLevel (hWnd,DISCL_EXCLUSIVE|DISCL_FOREGROUND);
	if(result != DI_OK) MessageBoxW(hWnd,L"设定程序协调层级失败！",L"出错！",MB_OK);
	result = pDev->Acquire(); 
//	if(result != DI_OK) MessageBoxW(hWnd,L"取用输入设备失败！",L"出错！",MB_OK);
	graph.设置截图(false);
//	hpc = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)MSG_Thread,NULL,CREATE_SUSPENDED,NULL);
}

short DxInput::DXInputRefresh()
{	if(pDev == NULL)
	{ DXInputInit();}

	result = pDev->GetDeviceState(sizeof(buffer),(LPVOID)& buffer);//获得键盘数据
	if(result != DI_OK)
	{
		DXInputInit();
		result = pDev->GetDeviceState(sizeof(buffer),(LPVOID)& buffer);//获得键盘数据
	//	MessageBoxW(hWnd,L"取得键盘状态失败",L"出错！",MB_OK);
	}
	//处理键盘消息
	if(KEYDOWN(DIK_ESCAPE))//如果**健被按下
	{	
		if( graph.获得关卡数() == MAIN_BTN )
		{
			if( MessageBoxW(hWnd,L"是否退出游戏？",L"dinput msg",MB_OKCANCEL)!=2 )
			DestroyWindow( hWnd ) ; //退出
		}
		//( graph.获得关卡数() == 3 )
		//{
			graph.设置关卡(MAIN_BTN);
			//回主菜单后用标准键盘消息控制退出，进入游戏后再启用本消息
			//pDev->Unacquire();	
			//pDev->Release();  
			//pInput->Release();
			//return 0;
			//goto EXIT;
		//}
		//else
		//{
		//	MessageBoxW(hWnd,L"退出游戏！",L"dinput msg",MB_OK);
		//	DestroyWindow( hWnd ) ; //退出
		//}
	}//EXIT:;

	if(KEYDOWN(DIK_UP))	      
	{	
		oPlayer.SetTankFace ( 1 ) ; //坦克向右移动	
		oMapedit.SetRollScreenFace( 1 ) ; //地图向下滚动
	}
	else if(KEYDOWN(DIK_DOWN))	      
	{					      
		oPlayer.SetTankFace ( 2 ) ; //坦克向右移动
		oMapedit.SetRollScreenFace( 2 ) ; //地图向下滚动
	}
	else if(KEYDOWN(DIK_LEFT))	      
	{					      
		oPlayer.SetTankFace ( 3 ) ; //坦克向右移动
		oMapedit.SetRollScreenFace( 3 ) ; //地图向下滚动
	}
	else if(KEYDOWN(DIK_RIGHT))	      
	{					      
		oPlayer.SetTankFace ( 4 ) ; //坦克向右移动
		oMapedit.SetRollScreenFace( 4 ) ; //地图向下滚动
	}
	else oPlayer.SetTankFace ( 0 ) ;//停止移动

	//功能快捷键
	if(KEYDOWN(DIK_TAB))// TAB 键
	{	
		oMapedit.SetCollideState(true);
	}
	if(KEYDOWN(DIK_Q))
	{
		oMapedit.SetCollideState(false);
	}
	if(KEYDOWN(DIK_LSHIFT))
	{
		oMapedit.设置大刷子( TRUE ) ; //打开全地图刷子		
	}
	if(KEYDOWN(DIK_Z))
	{
		oMapedit.设置大刷子( FALSE ) ; //关闭全地图刷子
	}
	if (KEYDOWN(DIK_CAPSLOCK))
	{
		if( graph.获得关卡数() != MAP_EDIT )return 0;
		oMapedit.SetEditSave(true);
		oMapedit.SetMouseTileToEmpty();
		MessageBoxW(hWnd,L"开启[存储框选区域]功能！",L"Key:CAPSLOCK-A",MB_OK);
	}
	if (KEYDOWN(DIK_A))
	{
		if( graph.获得关卡数() != MAP_EDIT )return 0;
		oMapedit.SetEditSave(false);
		MessageBoxW(hWnd,L"关闭[存储框选区域]功能！",L"Key:CAPSLOCK-A",MB_OK);
	}

	if(KEYDOWN(DIK_1))
	{
		oMapedit.设置图层( 0 ) ;
	//	MessageBoxW(hWnd,L"即将编辑第 1 层图",L"提示",MB_OKCANCEL);
	}
	if(KEYDOWN(DIK_2))
	{
		oMapedit.设置图层( 1 ) ;
	}
	if(KEYDOWN(DIK_3))
	{
		oMapedit.设置图层( 2 ) ;
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

		if(graph.获得截图())
		{
			graph.设置截图(false);
			DXInputInit();
		}
		else
		{
			graph.设置截图(true);
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
	{	//小地图开关;	
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
