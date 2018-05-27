#include "FileOperate.h"
CFileOperate oFileOperatr;
void CFileOperate::OpenFileInitialize (HWND hwnd)
{
     static TCHAR szFilter[] = TEXT("DAT (*.dat)\0*.dat\0\0");
							//   TEXT ("�����ļ�\0*.bmp;*.jpg;*.jpeg;*.jpe;*.gif;*.png;*.ico;*.dat\0")  \
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
     ofn.hwndOwner         = hwnd ;			 //�������ڣ�����ΪNULL
     ofn.hInstance         = NULL ;
     ofn.lpstrFilter       = szFilter ;		 //�ļ�ɸѡ�ַ���
     ofn.lpstrCustomFilter = NULL ;
     ofn.nMaxCustFilter    = 0 ;
     ofn.nFilterIndex      = 0 ;
     ofn.lpstrFile         = szCurrentDirectory ;   //ȫ·�����ļ���������
     ofn.nMaxFile          = MAX_PATH ;				//�ļ�������������
     ofn.lpstrFileTitle    = szCurrentDirectory ;   //������·�����ļ���������
     ofn.nMaxFileTitle     = MAX_PATH ;				//�ļ�������������
     ofn.lpstrInitialDir   = L"map\\";	//��ʼĿ¼
     ofn.lpstrTitle        = TEXT ("�򿪵�ͼ�ļ�");	//�Ի������
     ofn.Flags             = 0 ;             //��־
     ofn.nFileOffset       = 0 ;			 //�ļ������ַ����е���ʼλ��
     ofn.nFileExtension    = 0 ;			 //��չ�����ַ����е���ʼλ��
     ofn.lpstrDefExt       = TEXT (".dat") ;	 //Ĭ����չ��
     ofn.lCustData         = 0L ;
     ofn.lpfnHook          = NULL ;
     ofn.lpTemplateName    = NULL ;
}

void CFileOperate::SaveFileInitialize(void)
{
     static TCHAR szFilter[] = TEXT("DAT (*.dat)\0*.dat\0");
							// TEXT ("�����ļ�\0*.bmp;*.jpg;*.jpeg;*.jpe;*.gif;*.png;*.ico;*.dat\0")  \
                            // TEXT ("JPG (*.jpg;*.jpeg;*.jpe)\0*.jpg;*.jpeg;*.jpe\0") \
                            // TEXT ("BMP (*.bmp)\0*.bmp\0") \
							// TEXT ("GIF (*.gif)\0*.gif\0") \
							// TEXT ("PNG (*.png)\0*.png\0") \
							// TEXT ("DAT (*.dat)\0*.dat\0") \
							// TEXT ("ICO (*.ico)\0*.ico\0\0");
//	OPENFILENAME ofn;       // �����Ի���ṹ��
//	TCHAR szFile[MAX_PATH]; // �����ȡ�ļ����ƵĻ�������           
	
	// ��ʼ��ѡ���ļ��Ի���
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
	ofn.lpstrInitialDir   = L"map\\";	//��ʼĿ¼
	ofn.lpstrDefExt = TEXT ("dat");
//	ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
	
	// ��ʾ��ѡ���ļ��Ի���
	//if ( GetSaveFileName(&ofn) )
	//{
	//      //��ʾѡ����ļ���
	//      OutputDebugStringW(szFile);
	//      OutputDebugStringW(L"/r/n");
	//}	
}

// Flags�ֶΨD�D�ñ�־�ֶξ����˶Ի���Ĳ�ͬ��Ϊ����������һЩȡֵ����ϡ�������һЩ�Ƚ���Ҫ�ı�־��
// OFN_ALLOWMULTISELECT�D�D����ͬʱѡ�����ļ�����
// OFN_CREATEPROMPT�D�D����û�������һ�������ڵ��ļ������Ի������û����ʡ��Ƿ����ļ���
// OFN_FILEMUSTEXIST�D�D�û�ֻ��ѡ��һ���Ѿ����ڵ��ļ�����ʹ�������־��ʱ�����ͬʱʹ�� OFN_PATHMUSTEXIST��־��
// OFN_HIDEREADONLY�D�D�Ի����в���ʾ����ֻ����ʽ�򿪡���ѡ��
// OFN_OVERWRITEPROMPT�D�D�ڡ����桱�ļ��Ի�����ʹ�õ�ʱ�򣬵�ѡ��һ���Ѵ��ڵ��ļ�ʱ���Ի�������ʡ��Ƿ񸲸��ļ�����
// OFN_PATHMUSTEXIST�D�D�û������ļ���ʱ��·��������ڡ�
// OFN_READONLY�D�D�Ի����еġ���ֻ����ʽ�򿪡���ѡ���ʼ����ʱ����ѡ��״̬��
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

