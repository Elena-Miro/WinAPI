#include<Windows.h>
#include"resource.h"
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMgs, WPARAM wParam, LPARAM lparam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//MessageBox(NULL, "Hello World!", "Info", MB_YESNOCANCEL | MB_ICONWARNING|MB_SYSTEMMODAL);
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:break;
	case WM_COMMAND:break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}