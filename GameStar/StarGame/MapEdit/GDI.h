#include "main.h"

int Draw_Text_GDI(char *text, int x,int y,
                  COLORREF color, LPDIRECTDRAWSURFACE7 lpdds)
{
// this function draws the sent text on the sent surface 
// using color index as the color in the palette

HDC xdc; // the working dc

// get the dc from surface
if (FAILED(lpdds->GetDC(&xdc)))
   return(0);

// set the colors for the text up
SetTextColor(xdc,color);

// set background mode to transparent so black isn't copied
SetBkMode(xdc, TRANSPARENT);

// draw the text a
TextOutW(xdc,x,y,LPCWSTR(text),strlen(text));

// release the dc
lpdds->ReleaseDC(xdc);

// return success
return(1);
}; // end Draw_Text_GDI

// first print shadow
Draw_Text_GDI("DirectX Working with GDI!", x+4,y+4, 
              RGB(64,64,64), lpddsprimary);