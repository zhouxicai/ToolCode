
#ifndef  _SPECIAL_DEFINE_H
#define  _SPECIAL_DEFINE_H

#include <Windows.h>
/*
使用DirectDraw的Gamma控制形成淡出效果 

　　为什么要使用DDRAW中的Gamma控制功能来做淡出呢？有两个主要原因：第一个是因为简单；第二是因为使用Gamma淡出，你不会丢失任何存;
  储在主表面中的信息。; 
  　　既然这样，在实现这种技术之前，有些不显眼的小事情我们必须给予注意。首先，你的主表面必须是16Bit色或更高；第二个是这种淡出只能在你的;
	主表面上来做，因为这是在调整你的显卡的gamma设置。 ;
	　　让我们认真考虑一下：在DirectDraw库中包含一个结构DDGAMMARAMP。这个结构由3个包含256个字的数组组成，分别是Red,Green和Blue。;
	  例如：; 
*/
typedef   struct   DDGAMMARAMP 
{ 
	WORD   red[256]; 
	WORD   green[256]; 
	WORD   blue[256]; 
}DDGAMMARAMP,FAR   *LPDDGRAMMARAMP; 
//这个结构保存着我们的显示卡当前的Gamma设定值。那么，来声明几个我们程序中使用的变量 ;
#endif