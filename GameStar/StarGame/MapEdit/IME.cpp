#include "IME.h"
CIME cime;
BOOL CIME::InitInstance(HINSTANCE hInstance, int nCmdShow , HWND hwnd)
{
 //   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
 //       0, 0, 200, 400, NULL, NULL, hInstance, NULL);
	g_hWnd = hwnd;
    g_hText = CreateWindowW(L"EDIT", L"Text", WS_POPUPWINDOW | ES_MULTILINE,
        0, 0, 200, 50, g_hWnd, 0, g_hInstance, 0);
    g_hWndComposition = CreateWindowW(L"EDIT", L"Composition", WS_POPUPWINDOW | ES_MULTILINE,
        205, 50, 200, 50, g_hWnd, 0, g_hInstance, 0);
    g_hWndCandidate = CreateWindowW(L"LISTBOX", L"Candidate", WS_POPUPWINDOW,
        205, 100, 200, 250, g_hWnd, 0, g_hInstance, 0);
    g_hWndStatus = CreateWindowW(L"EDIT", L"Status", WS_POPUPWINDOW | ES_MULTILINE,
        205, 350, 200, 50, g_hWnd, 0, g_hInstance, 0);

    ShowWindow(g_hText, nCmdShow);
    UpdateWindow(g_hText);
    return TRUE;
}

void CIME::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
//	int         wmId, wmEvent;
    DWORD       dwConversion, dwSentence;
    HIMC        hIMC;
    int         len;

	switch (message)
	{
    case WM_CREATE:
        HandleChangeLanguage(g_szLanguageName, 200);
		hIMC = ImmCreateContext();
		hIMC = ImmAssociateContext(hWnd,hIMC);
        SetWindowLong(hWnd,0,(LONG)hIMC);
		CreateWindowW(L"Ime", L"", WS_POPUP | WS_DISABLED, 0,0,0,0, hWnd, NULL, g_hInstance, NULL);
        g_szBuf[0] = 0;
        break;

	case WM_DESTROY:
		hIMC = (HIMC)GetWindowLong(hWnd,0);
		hIMC = ImmAssociateContext(hWnd,hIMC);
		ImmDestroyContext(hIMC);
		PostQuitMessage(0);
        break;

    case WM_SETFOCUS:
        HandleChangeLanguage(g_szLanguageName, 200);
        break;

    case WM_INPUTLANGCHANGE:
        HandleChangeLanguage(g_szLanguageName, 200);
        break;

    case WM_CHAR:
        len = sizeof(g_szBuf);
        if (len<1023)
        {
            if (wParam==8)//退格键
            {
                if (len>0)  g_szBuf[len-1] = 0;
            }else
            {
                g_szBuf[len] = (char)wParam;
                g_szBuf[len+1] = 0;
            }
            ::SetWindowText(g_hText, g_szBuf);
        }
        break;

	case WM_IME_NOTIFY:
		switch (wParam)
		{
        // IMN Open Candidate
		case IMN_OPENCANDIDATE:
			OutputDebugString(L"\nIMN Open Candidate");
            ::ShowWindow(g_hWndCandidate, SW_SHOW);
            ::UpdateWindow(g_hWndCandidate);
            ::SetFocus(g_hWnd);
			HandleCandidate(hWnd);
			break;
        // IMN Close Candidate
		case IMN_CLOSECANDIDATE:
			OutputDebugString(L"\nIMN Close Candidate");
            ::ShowWindow(g_hWndCandidate, SW_HIDE);
			break;
        // IMN Change Candidate
		case IMN_CHANGECANDIDATE:
			HandleCandidate(hWnd);
			break;
        // IMN Set Candidate Pos
		case IMN_SETCANDIDATEPOS:
			OutputDebugString(L"\nIMN Set Candidate Pos");
			HandleCandidate(hWnd);
			break;
        // IMN Set Conversion Mode
		case IMN_SETCONVERSIONMODE:
			OutputDebugString(L"\nIMN Set Conversion Mode");
            HandleConversion(hWnd, &dwConversion, &dwSentence);
			break;
        // IMN Set Sentence Mode
		case IMN_SETSENTENCEMODE:
			OutputDebugString(L"\nIMN Set Sentence Mode");
            HandleConversion(hWnd, &dwConversion, &dwSentence);
			break;
        // IMN Open Status Window
		case IMN_OPENSTATUSWINDOW:
			OutputDebugString(L"\nIMN Open Status Window");
            HandleGetOpenStatus(hWnd);
            HandleConversion(hWnd, &dwConversion, &dwSentence);
			break;
        // IMN Close Status Window
		case IMN_CLOSESTATUSWINDOW:
			OutputDebugString(L"\nIMN Close Status Window");
            HandleGetOpenStatus(hWnd);
			break;
        // IMN Set Open Status
		case IMN_SETOPENSTATUS:
			OutputDebugString(L"\nIMN Set Open Status");
            HandleGetOpenStatus(hWnd);
			break;

        // IMN Set Composition Window
		case IMN_SETCOMPOSITIONWINDOW:
			OutputDebugString(L"\nIMN Set Composition Window");
			break;
		}
		break;
    case WM_IME_STARTCOMPOSITION:
		OutputDebugString(L"\nIME Composition Start");
        ::ShowWindow(g_hWndComposition, SW_SHOW);
        ::UpdateWindow(g_hWndComposition);
        ::SetFocus(g_hWnd);
        HandleComposition(hWnd);
        break;
    case WM_IME_ENDCOMPOSITION:
		OutputDebugString(L"\nIME Composition End");
        ::ShowWindow(g_hWndComposition, SW_HIDE);
        break;
    case WM_IME_COMPOSITION:
        wchar_t buf[20];
        buf[0] = '\n';
        buf[1] = '-';
        buf[3] = wParam&0x0FF;
        buf[2] = (wParam&0x0FF00)>>8;
        buf[4] = 0;
		OutputDebugString(buf);
        HandleComposition(hWnd);
        break;
	//case WM_COMMAND:
	//	wmId    = LOWORD(wParam); 
	//	wmEvent = HIWORD(wParam); 

	//	break;
	//	return DefWindowProc(hWnd, message, wParam, lParam);
   }
	//return DefWindowProc(hWnd, message, wParam, lParam);
 //  return 0;
}

BOOL CIME::HandleGetOpenStatus(HWND hWnd)
{
    HIMC    hIMC;
    hIMC = ::ImmGetContext(hWnd);
    BOOL ret = ::ImmGetOpenStatus(hIMC);
    ::ImmReleaseContext(hWnd,hIMC);
#ifdef  _DEBUG
    char    pOutputBuf[40];
    sprintf_s(pOutputBuf, "\nIME Status is %s", ret?"Open":"Close");
    ::OutputDebugString(LPCWSTR(pOutputBuf));
#endif
    return ret;
}

BOOL CIME::HandleConversion(HWND hWnd, LPDWORD lpfdwConversion, LPDWORD lpfdwSentence)
{
    HIMC    hIMC;
    hIMC = ::ImmGetContext(hWnd);
    BOOL ret = ::ImmGetConversionStatus(hIMC, lpfdwConversion, lpfdwSentence);
    ::ImmReleaseContext(hWnd,hIMC);
    char    pOutputBuf[200];
    sprintf_s(pOutputBuf, "%s\r\n模式:", g_szLanguageName);
    if (*lpfdwConversion & 0x01)    strcat_s(pOutputBuf, " 中文");
    else                            strcat_s(pOutputBuf, " 英文");
    if (*lpfdwConversion & 0x08)    strcat_s(pOutputBuf, " 全角");
    else                            strcat_s(pOutputBuf, " 半角");
    if (*lpfdwConversion & 0x400)   strcat_s(pOutputBuf, " 中文标点");
    else                            strcat_s(pOutputBuf, " 英文标点");
    if (*lpfdwConversion & 0x80)    strcat_s(pOutputBuf, " 软键盘");
    SetWindowText(g_hWndStatus, (LPCWSTR)pOutputBuf);
#ifdef  _DEBUG
    sprintf_s(pOutputBuf, "\n    Conversion = 0x%X, Sentence = 0x%X\n    ", *lpfdwConversion, *lpfdwSentence);
    ::OutputDebugString((LPCWSTR)pOutputBuf);
    ::OutputDebugString((LPCWSTR)pOutputBuf);
#endif
    return ret;
}

DWORD CIME::HandleCandidate(HWND hWnd)
{
    HIMC            hIMC;
    unsigned long   dwCount, dwSize, i, j;
    char*           pBuf;
    LPCANDIDATELIST pList;
    hIMC = ::ImmGetContext(hWnd);
    dwSize = ::ImmGetCandidateListCount(hIMC, &dwCount);
    pBuf = new char[dwSize];
    pList = (LPCANDIDATELIST)pBuf;
#ifdef  _DEBUG
    char          pOutputBuf[40];
    sprintf_s(pOutputBuf, "\nCount= %d, size= %d", dwCount, dwSize);
    ::OutputDebugString((LPCWSTR)pOutputBuf);
#endif
    while (::SendMessage(g_hWndCandidate, LB_GETCOUNT, 0, 0))
        ::SendMessage(g_hWndCandidate, LB_DELETESTRING, 0, 0);
    for (i=0; i<dwCount; i++)
    {	//取得候选字符串列表
        ::ImmGetCandidateList(hIMC, i, pList,dwSize);
        for (j=0; j<pList->dwPageSize; j++)
            ::SendMessage(g_hWndCandidate, LB_ADDSTRING, 0, (DWORD)pBuf+pList->dwOffset[pList->dwPageStart+j]);
        ::SendMessage(g_hWndCandidate, LB_SETCURSEL, pList->dwSelection, 0);
#ifdef  _DEBUG
        sprintf_s(pOutputBuf, "\nList[%d]:", pList->dwPageSize);
        ::OutputDebugString((LPCWSTR)pOutputBuf);
        for (j=0; j<pList->dwPageSize; j++)
        {
            ::OutputDebugString(L" ");
            ::OutputDebugString((LPCWSTR)pBuf+pList->dwOffset[pList->dwPageStart+j]);
        }
        ::OutputDebugString(L"\nSel: ");
        ::OutputDebugString((LPCWSTR)pBuf+pList->dwOffset[pList->dwSelection]);
#endif
    }
    delete[] pBuf;
    ::ImmReleaseContext(hWnd,hIMC);
    return dwCount;
}

LONG CIME::HandleComposition(HWND hWnd)
{	//取得输入上下文
	HIMC hIMC = ::ImmGetContext(hWnd);
	//取得组字字符串大小
    LONG lSize = ::ImmGetCompositionStringW(hIMC, GCS_COMPSTR, 0, 0);
    if (lSize==0) return 0;
	//取得组字字符串
    char* pString = new char[lSize+1];//增加一个结束符位
	::ImmGetCompositionString(hIMC, GCS_COMPSTR, pString, lSize);
	pString[lSize] = '\0';//结束符

	//处理组字字符串
    SetWindowText(g_hWndComposition, (LPCWSTR)pString);

#ifdef  _DEBUG
    ::OutputDebugString(L"\n");
    ::OutputDebugString((LPCWSTR)pString);
#endif
    delete[] pString;//释放字符串
	::ImmReleaseContext(hWnd, hIMC ) ;//释放输入上下文
	return lSize ;
}

int CIME::HandleChangeLanguage(char* lpszIMENameBuf, long lBufSize)
{
    HKL hKL = ::GetKeyboardLayout(0);
    int iSize = ::ImmGetDescription(hKL, NULL, 0);
    if (iSize>=lBufSize) return -1;
    if (iSize==0)
    {
        ::ShowWindow(g_hWndStatus, SW_HIDE);
#ifdef  _DEBUG
        ::OutputDebugString(L"\n输入法关闭");
#endif
    }else
    {
        ::ShowWindow(g_hWndStatus, SW_SHOW);
        ::UpdateWindow(g_hWndStatus);
        ::SetFocus(g_hWnd);
        ::ImmGetDescription(hKL, (LPWSTR)lpszIMENameBuf, lBufSize);
#ifdef  _DEBUG
        ::OutputDebugString(L"\n输入法：");
        ::OutputDebugString((LPCWSTR)lpszIMENameBuf);
#endif
    }
    return iSize;
}
