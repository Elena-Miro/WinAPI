#include<Windows.h>
#include"resource.h"

CHAR sz_login_invitation[] = "Введите логин";
CHAR sz_password_invitation[] = "Введите пароль";

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
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd,WM_SETICON,0,(LPARAM)hIcon);
		SendMessageA(GetDlgItem(hwnd, IDC_EDIT_LOGIN),WM_SETTEXT, 0, (LPARAM)sz_login_invitation);
		SendMessageA(GetDlgItem(hwnd, IDC_EDIT_PASSWORD),WM_SETTEXT, 0, (LPARAM)sz_password_invitation);
	}
		break;
	case WM_COMMAND: //отправляется в оконную процедуру:пользователь выбирает элемент из меню
	{
		
		
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			//при выполнении различных действий над к-л элементом интерфейса . Этот эл интерфейса
			//он получает уведомления
			//уведомления -это самые обычные сообщения
			//когда мы становимся в текстовое поле, то это текстовое поле получает уведомление EN_SETFOCUS
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			switch (HIWORD(wParam))
			{
			case EN_SETFOCUS:
				if (strcmp(sz_buffer, sz_login_invitation) == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)""); break;
				
			case EN_KILLFOCUS:
				if(strlen(sz_buffer)==0)
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)sz_login_invitation); break;
			}
		}
		break;
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;//Размер буффера
			CHAR sz_buffer[SIZE] = {};
			HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);//получаем окно текстового поля по имени ресурса
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);//копируем текст из текстового поля пассворвд в сз буффер
			HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDC_BUTTON_SET_TITLE:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			
		}
		break;
		case IDOK:MessageBox(NULL, "Была нажта кнопка ОК ", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
	}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}