#ifndef CFILE_OPERATE_H
#define CFILE_OPERATE_H
#include "main.h"
#include <CommDlg.h>
#include <iostream>

using namespace std;




class CFileOperate
{
private:
	OPENFILENAMEW ofn;
//	GetSaveFileNameW sfn;
public:
	void OpenFileInitialize(HWND hwnd);
	void SaveFileInitialize(void);

	BOOL BOpenFileDialogBox(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName);
	BOOL BSaveFileDialogBox(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName);
};
extern CFileOperate oFileOperatr;
#endif