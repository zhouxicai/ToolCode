#ifndef _DXINPUT_H
#define _DXINPUT_H
#include <dinput.h>

class DxInput  
{
private:
	#define KEYDOWN(key)(buffer[key]& 0x80)//����һ���꣬�����������
	char buffer[256];
	HRESULT result;  
		LPDIRECTINPUT8 pInput;
		LPDIRECTINPUTDEVICE8 pDev;
public:
	DxInput();
	~DxInput();
	void DXInputInit();
	short DXInputRefresh();
};
extern  DxInput dxinput;
#endif

