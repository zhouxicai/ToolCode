//#include "TextFont.h"
//ͷ�ļ�����ã��ٴ�������
//void CTextFont::ShowText()
//{
	//	static HDC hdc; 
	//if (DDS[SBuffer]->GetDC(&hdc) == DD_OK)
	//{	static HFONT ht;
	//	static LOGFONT lf; 
	//	SetBkMode(hdc,TRANSPARENT);//���ñ���ģʽ͸��
	//	SetTextColor(hdc, RGB(230, 230, 230));
	//	SetTextCharacterExtra (hdc, 1) ;//�����м��
	//	
	//	memset(&lf,   0,   sizeof(LOGFONT)); 
	//	lf.lfHeight   =   28;//��������߶�
	//	lf.lfWidth	  =	  26;//����������
	//	lf.lfWeight	  =	  900;//���塢0Ĭ�ϡ���100-900��ÿ�μ�100��
	//	ht = CreateFontIndirectW(&lf); 
	//	ht = (HFONT)SelectObject(hdc,ht);
	//	static TCHAR text[8];
	//	wsprintfW(text,L"��ǰͼ�� %d" , ͼ��+1);
	//	TabbedTextOutW(hdc,555 ,YSCREEN-35,text, wcslen(text),NULL,NULL,NULL );
	//	DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

	////	SetTextAlign(hdc,TA_RIGHT);//���־���
	//	memset(&lf,   0,   sizeof(LOGFONT)); 
	//	lf.lfHeight   =   12;//��������߶�
	//	lf.lfWidth	  =	  10;//����������
	//	lf.lfWeight	  =	  900;
	//	ht = CreateFontIndirectW(&lf); 
	//	ht = (HFONT)SelectObject(hdc,ht);
	//	static wchar_t* txt = L"����̹�˵�ͼ�༭��";
	//	TextOutW(hdc,10,10, txt, wcslen(txt) ); //���ַ�����strlen����wcslen				
	//	DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

	//	DDS[SBuffer]->ReleaseDC(hdc);
	//}
//}