#if 0
#include <windows.h>
#include <ddraw.h>
#include <mmsystem.h>
#include "main.h"
#include "SpecialDefine.h"

　　//初始化Gamma控制以便应用; 
　　LPDIRECTDRAWGAMMACONTROL   lpDDGammaControl   =   NULL; 
　　//这个是我们将修改的斜坡值(ramp); 
　　DDGAMMARAMP   DDGammaRamp; 
　　//这个结构用来保存原来的gamma值，以便淡出完成后恢复我们gamma值; 
　　DDGAMMARAMP   DDGammaOld; 
//完成了这些之后我们需要查明显示是否支持gamma控制（尽管如果显卡硬件不支持它的话，DX将会用软件模拟它），所以来查询主表面： 
　　lpddsprimary-> QueryInterface(IID_IDirectDrawGammaControl,(void   **)&   lpDDGammaControl); 
//然后看显卡当前的gamma设置是否正确，再存储它到DDGAMMAOLD结构里; 
　　lpDDGammaControl-> GetGammaRamp(0,&DDGammaOld); 
//让我们来做一下这个，并且保存值到DDGAMMARAMP结构里，以便我们修改它的值： 
　　lpDDGammaControl-> GetGammaRamp(0,&DDGammaRamp); 
/*
现在除非一个用户改变他们计算机上的GAMMA设定值，应当把你的DDGammaRamp结构的值增加到第256个。现在，因为每个Red,Green和Blue的;

值可以是任何0到65535的值，我们不想把它们值改到1。所以，我决定写下尽可能快的代码把所有的256的值到0然后每次刷新屏幕。下面是代码实现：

（这里有些说不明白，附原文：Now   unless   a   user   changes   the   values   of   the   gamma   on   their   computer   the   values   should   

go   up   as   you   reach   the   256th   value   in   your   DDGammaRamp   structure.   Now   because   each   value   of   Red,   Blue   and   

Green   can   be   anywhere   from   0   to   65535   we   wouldn 't   want   to   decrement   our   values   by   1.   Instead   I   decided   to   

make   the   code   as   fast   as   possible   so   I   set   all   256   values   to   0   and   update   the   screen   after   each.   Here   is   how   the 

  code   looks) 
*/
for(int   blackloop=0;blackloop <256;blackloop++) 
{ 
	//如果一个值大于0的话，就把它设成0; 
	if(DDGammaRamp.red[blackloop]   >   0)   
	{ 
		//set   the   current   value   of   DDGammaRamp.Red   to   0. 
		DDGammaRamp.red[blackloop]=0; 
		//now   let 's   update   our   primary 
		lpDDGammaControl-> SetGammaRamp(0,   &DDGammaRamp); 
		//surface   with   the   new   gamma   setting 
	} 
	//这个程序有点太快了，所以让它慢一点？ 
	Sleep(1); 
	if(DDGammaRamp.green[blackloop]   >   0) 
	{ 
		//设当前DDGammaRamp.yellow的值到0.; 
		DDGammaRamp.green[blackloop]=0; 
		lpDDGammaControl-> SetGammaRamp(DDSGR_CALIBRATE,   &DDGammaRamp); 
	}   
	Sleep(1); 
	if(DDGammaRamp.blue[blackloop]   >   0) 
	{ 
		//设当前DDGammaRamp.Blue的值到0. 
		DDGammaRamp.   blue   [blackloop]=0; 
		lpDDGammaControl-> SetGammaRamp(DDSGR_CALIBRATE,   &DDGammaRamp); 
	}   
	Sleep(1); 
}   //结束 

//现在fade完成了，我们需要恢复所有原来的gamma值，否则屏幕一直是黑的：; 
　　lpDDGammaControl-> SetGammaRamp(0,   &DDGammaOld); 
#endif