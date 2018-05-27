//#include "TextFont.h"
//头文件整理好，再处理这里
//void CTextFont::ShowText()
//{
	//	static HDC hdc; 
	//if (DDS[SBuffer]->GetDC(&hdc) == DD_OK)
	//{	static HFONT ht;
	//	static LOGFONT lf; 
	//	SetBkMode(hdc,TRANSPARENT);//设置背景模式透明
	//	SetTextColor(hdc, RGB(230, 230, 230));
	//	SetTextCharacterExtra (hdc, 1) ;//设置行间距
	//	
	//	memset(&lf,   0,   sizeof(LOGFONT)); 
	//	lf.lfHeight   =   28;//设置字体高度
	//	lf.lfWidth	  =	  26;//设置字体宽度
	//	lf.lfWeight	  =	  900;//粗体、0默认、从100-900，每次加100；
	//	ht = CreateFontIndirectW(&lf); 
	//	ht = (HFONT)SelectObject(hdc,ht);
	//	static TCHAR text[8];
	//	wsprintfW(text,L"当前图层 %d" , 图层+1);
	//	TabbedTextOutW(hdc,555 ,YSCREEN-35,text, wcslen(text),NULL,NULL,NULL );
	//	DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

	////	SetTextAlign(hdc,TA_RIGHT);//文字居中
	//	memset(&lf,   0,   sizeof(LOGFONT)); 
	//	lf.lfHeight   =   12;//设置字体高度
	//	lf.lfWidth	  =	  10;//设置字体宽度
	//	lf.lfWeight	  =	  900;
	//	ht = CreateFontIndirectW(&lf); 
	//	ht = (HFONT)SelectObject(hdc,ht);
	//	static wchar_t* txt = L"迷你坦克地图编辑器";
	//	TextOutW(hdc,10,10, txt, wcslen(txt) ); //多字符集用strlen代替wcslen				
	//	DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

	//	DDS[SBuffer]->ReleaseDC(hdc);
	//}
//}