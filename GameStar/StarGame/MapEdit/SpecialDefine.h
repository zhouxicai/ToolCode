
#ifndef  _SPECIAL_DEFINE_H
#define  _SPECIAL_DEFINE_H

#include <Windows.h>
/*
ʹ��DirectDraw��Gamma�����γɵ���Ч�� 

����ΪʲôҪʹ��DDRAW�е�Gamma���ƹ������������أ���������Ҫԭ�򣺵�һ������Ϊ�򵥣��ڶ�����Ϊʹ��Gamma�������㲻�ᶪʧ�κδ�;
  �����������е���Ϣ��; 
  ������Ȼ��������ʵ�����ּ���֮ǰ����Щ�����۵�С�������Ǳ������ע�⡣���ȣ���������������16Bitɫ����ߣ��ڶ��������ֵ���ֻ�������;
	����������������Ϊ�����ڵ�������Կ���gamma���á� ;
	�������������濼��һ�£���DirectDraw���а���һ���ṹDDGAMMARAMP������ṹ��3������256���ֵ�������ɣ��ֱ���Red,Green��Blue��;
	  ���磺; 
*/
typedef   struct   DDGAMMARAMP 
{ 
	WORD   red[256]; 
	WORD   green[256]; 
	WORD   blue[256]; 
}DDGAMMARAMP,FAR   *LPDDGRAMMARAMP; 
//����ṹ���������ǵ���ʾ����ǰ��Gamma�趨ֵ����ô���������������ǳ�����ʹ�õı��� ;
#endif