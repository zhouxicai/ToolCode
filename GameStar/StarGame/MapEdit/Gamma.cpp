#if 0
#include <windows.h>
#include <ddraw.h>
#include <mmsystem.h>
#include "main.h"
#include "SpecialDefine.h"

����//��ʼ��Gamma�����Ա�Ӧ��; 
����LPDIRECTDRAWGAMMACONTROL   lpDDGammaControl   =   NULL; 
����//��������ǽ��޸ĵ�б��ֵ(ramp); 
����DDGAMMARAMP   DDGammaRamp; 
����//����ṹ��������ԭ����gammaֵ���Ա㵭����ɺ�ָ�����gammaֵ; 
����DDGAMMARAMP   DDGammaOld; 
//�������Щ֮��������Ҫ������ʾ�Ƿ�֧��gamma���ƣ���������Կ�Ӳ����֧�����Ļ���DX���������ģ����������������ѯ�����棺 
����lpddsprimary-> QueryInterface(IID_IDirectDrawGammaControl,(void   **)&   lpDDGammaControl); 
//Ȼ���Կ���ǰ��gamma�����Ƿ���ȷ���ٴ洢����DDGAMMAOLD�ṹ��; 
����lpDDGammaControl-> GetGammaRamp(0,&DDGammaOld); 
//����������һ����������ұ���ֵ��DDGAMMARAMP�ṹ��Ա������޸�����ֵ�� 
����lpDDGammaControl-> GetGammaRamp(0,&DDGammaRamp); 
/*
���ڳ���һ���û��ı����Ǽ�����ϵ�GAMMA�趨ֵ��Ӧ�������DDGammaRamp�ṹ��ֵ���ӵ���256�������ڣ���Ϊÿ��Red,Green��Blue��;

ֵ�������κ�0��65535��ֵ�����ǲ��������ֵ�ĵ�1�����ԣ��Ҿ���д�¾����ܿ�Ĵ�������е�256��ֵ��0Ȼ��ÿ��ˢ����Ļ�������Ǵ���ʵ�֣�

��������Щ˵�����ף���ԭ�ģ�Now   unless   a   user   changes   the   values   of   the   gamma   on   their   computer   the   values   should   

go   up   as   you   reach   the   256th   value   in   your   DDGammaRamp   structure.   Now   because   each   value   of   Red,   Blue   and   

Green   can   be   anywhere   from   0   to   65535   we   wouldn 't   want   to   decrement   our   values   by   1.   Instead   I   decided   to   

make   the   code   as   fast   as   possible   so   I   set   all   256   values   to   0   and   update   the   screen   after   each.   Here   is   how   the 

  code   looks) 
*/
for(int   blackloop=0;blackloop <256;blackloop++) 
{ 
	//���һ��ֵ����0�Ļ����Ͱ������0; 
	if(DDGammaRamp.red[blackloop]   >   0)   
	{ 
		//set   the   current   value   of   DDGammaRamp.Red   to   0. 
		DDGammaRamp.red[blackloop]=0; 
		//now   let 's   update   our   primary 
		lpDDGammaControl-> SetGammaRamp(0,   &DDGammaRamp); 
		//surface   with   the   new   gamma   setting 
	} 
	//��������е�̫���ˣ�����������һ�㣿 
	Sleep(1); 
	if(DDGammaRamp.green[blackloop]   >   0) 
	{ 
		//�赱ǰDDGammaRamp.yellow��ֵ��0.; 
		DDGammaRamp.green[blackloop]=0; 
		lpDDGammaControl-> SetGammaRamp(DDSGR_CALIBRATE,   &DDGammaRamp); 
	}   
	Sleep(1); 
	if(DDGammaRamp.blue[blackloop]   >   0) 
	{ 
		//�赱ǰDDGammaRamp.Blue��ֵ��0. 
		DDGammaRamp.   blue   [blackloop]=0; 
		lpDDGammaControl-> SetGammaRamp(DDSGR_CALIBRATE,   &DDGammaRamp); 
	}   
	Sleep(1); 
}   //���� 

//����fade����ˣ�������Ҫ�ָ�����ԭ����gammaֵ��������Ļһֱ�Ǻڵģ�; 
����lpDDGammaControl-> SetGammaRamp(0,   &DDGammaOld); 
#endif