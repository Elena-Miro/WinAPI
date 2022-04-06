#define _CRT_SECURE_NO_WARNINGS 
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* string[] = 
{
	"Хорошо","живет","на","свете ","Винни-","Пух"
};
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam)
{

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); i++)
		{
			SendMessage(hComboBox, CB_ADDSTRING, 0,(LPARAM)string[i]);
		}
		
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			CHAR sz_message[SIZE] = {};
			HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
			int index = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
			SendMessage(hComboBox, CB_GETLBTEXT, index, (LPARAM)sz_buffer);
			sprintf(sz_message, "Вы выбрали элемент № %d со значением \"%s\".", index, sz_buffer);
			
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL:EndDialog(hwnd, 0); break;

		}

		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}