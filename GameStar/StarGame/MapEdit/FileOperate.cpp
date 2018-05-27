#include "FileOperate.h"
CFileOperate oFileOperatr;
void CFileOperate::OpenFileInitialize (HWND hwnd)
{
     static TCHAR szFilter[] = TEXT("DAT (*.dat)\0*.dat\0\0");
							//   TEXT ("所有文件\0*.bmp;*.jpg;*.jpeg;*.jpe;*.gif;*.png;*.ico;*.dat\0")  \
                            //   TEXT ("JPG (*.jpg;*.jpeg;*.jpe)\0*.jpg;*.jpeg;*.jpe\0") \
                            //   TEXT ("BMP (*.bmp)\0*.bmp\0") \
							//   TEXT ("GIF (*.gif)\0*.gif\0") \
							//   TEXT ("PNG (*.png)\0*.png\0") \
							//   TEXT ("DAT (*.dat)\0*.dat\0") \
							//   TEXT ("ICO (*.ico)\0*.ico\0\0"); 
	 TCHAR szCurrentDirectory[MAX_PATH];
//	 GetCurrentDirectoryW(MAX_PATH,szCurrentDirectory);
	 GetModuleFileNameW(NULL,szCurrentDirectory,MAX_PATH);
	 SetCurrentDirectoryW(szCurrentDirectory);
     ZeroMemory(&ofn, sizeof(ofn));
     ofn.lStructSize       = sizeof (OPENFILENAME) ;
     ofn.hwndOwner         = hwnd ;			 //所属窗口，可以为NULL
     ofn.hInstance         = NULL ;
     ofn.lpstrFilter       = szFilter ;		 //文件筛选字符串
     ofn.lpstrCustomFilter = NULL ;
     ofn.nMaxCustFilter    = 0 ;
     ofn.nFilterIndex      = 0 ;
     ofn.lpstrFile         = szCurrentDirectory ;   //全路径的文件名缓冲区
     ofn.nMaxFile          = MAX_PATH ;				//文件名缓冲区长度
     ofn.lpstrFileTitle    = szCurrentDirectory ;   //不包含路径的文件名缓冲区
     ofn.nMaxFileTitle     = MAX_PATH ;				//文件名缓冲区长度
     ofn.lpstrInitialDir   = L"map\\";	//初始目录
     ofn.lpstrTitle        = TEXT ("打开地图文件");	//对话框标题
     ofn.Flags             = 0 ;             //标志
     ofn.nFileOffset       = 0 ;			 //文件名在字符串中的起始位置
     ofn.nFileExtension    = 0 ;			 //扩展名在字符串中的起始位置
     ofn.lpstrDefExt       = TEXT (".dat") ;	 //默认扩展名
     ofn.lCustData         = 0L ;
     ofn.lpfnHook          = NULL ;
     ofn.lpTemplateName    = NULL ;
}

void CFileOperate::SaveFileInitialize(void)
{
     static TCHAR szFilter[] = TEXT("DAT (*.dat)\0*.dat\0");
							// TEXT ("所有文件\0*.bmp;*.jpg;*.jpeg;*.jpe;*.gif;*.png;*.ico;*.dat\0")  \
                            // TEXT ("JPG (*.jpg;*.jpeg;*.jpe)\0*.jpg;*.jpeg;*.jpe\0") \
                            // TEXT ("BMP (*.bmp)\0*.bmp\0") \
							// TEXT ("GIF (*.gif)\0*.gif\0") \
							// TEXT ("PNG (*.png)\0*.png\0") \
							// TEXT ("DAT (*.dat)\0*.dat\0") \
							// TEXT ("ICO (*.ico)\0*.ico\0\0");
//	OPENFILENAME ofn;       // 公共对话框结构。
//	TCHAR szFile[MAX_PATH]; // 保存获取文件名称的缓冲区。           
	
	// 初始化选择文件对话框。
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
//	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFilter;
	
	//
//	ofn.lpstrFile = NULL;
	ofn.nMaxFile = sizeof(szFilter);
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 1;
//	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir   = L"map\\";	//初始目录
	ofn.lpstrDefExt = TEXT ("dat");
//	ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
	
	// 显示打开选择文件对话框。
	//if ( GetSaveFileName(&ofn) )
	//{
	//      //显示选择的文件。
	//      OutputDebugStringW(szFile);
	//      OutputDebugStringW(L"/r/n");
	//}	
}

// Flags字段――该标志字段决定了对话框的不同行为，它可以是一些取值的组合。下面是一些比较重要的标志：
// OFN_ALLOWMULTISELECT――允许同时选择多个文件名。
// OFN_CREATEPROMPT――如果用户输入了一个不存在的文件名，对话框向用户提问“是否建立文件”
// OFN_FILEMUSTEXIST――用户只能选择一个已经存在的文件名，使用这个标志的时候必须同时使用 OFN_PATHMUSTEXIST标志。
// OFN_HIDEREADONLY――对话框中不显示“以只读方式打开”复选框。
// OFN_OVERWRITEPROMPT――在“保存”文件对话框中使用的时候，当选择一个已存在的文件时，对话框会提问“是否覆盖文件”。
// OFN_PATHMUSTEXIST――用户输入文件名时，路径必须存在。
// OFN_READONLY――对话框中的“以只读方式打开”复选框初始化的时候处于选中状态。
BOOL CFileOperate::BOpenFileDialogBox (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
     ofn.hwndOwner         = hwnd ;
     ofn.lpstrFile         = pstrFileName ;
     ofn.lpstrFileTitle    = pstrTitleName ;
     ofn.Flags             = OFN_HIDEREADONLY | OFN_CREATEPROMPT |OFN_FILEMUSTEXIST;
     return GetOpenFileName (&ofn) ;
}

BOOL CFileOperate::BSaveFileDialogBox(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
     ofn.hwndOwner      = hwnd ;
     ofn.lpstrFile      = pstrFileName ;
     ofn.lpstrFileTitle = pstrTitleName ;
     ofn.Flags			= OFN_SHOWHELP | OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT;
     return GetSaveFileName (&ofn) ;
}

