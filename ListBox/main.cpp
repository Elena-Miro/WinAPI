#define _CRT_SECURE_NO_WARNINGS //sprintf()
#include<Windows.h>
#include<cstdio>//sprintf()
#include"resource.h"

CONST CHAR* string[] = //вот эти строки мы добавим в листбокс
{
	"This ","is ","my ","first","List ","Box"
};
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);

//calling_convention-конвенция вызовов(соглашение о вызове функции)
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);//запускает диалоговое окно
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam)//процедура создания окна/ распознает сообщения
{

	switch (uMsg)
	{
	case WM_INITDIALOG://сообщение отправляется в окно при его создании
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);//возвращает хвнд элемента окна по айди ресурса нужного элемента
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); i++)//
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)string[i]);//функция отправляет сообщение окну листбокс //ADDSTRING сообщение добавляет указанною строку в листбокс//и каждую строку добавляет
		}
	}
		break;
	case WM_COMMAND://сообщение обрабатывает нажатие на кнопку 
		switch (LOWORD(wParam))//лоуворд там лежит в впарам
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};//в эту строку скопируем выделенную строку листбокса
			CHAR sz_message[SIZE] = {};//эту строку мы будем отображать в месседжбокс
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			int index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);//возвращает индекс текущего элемента//получаем числовой индекс выделенного элемента листбокса
			SendMessage(hListBox, LB_GETTEXT, index, (LPARAM)sz_buffer);
			sprintf(sz_message, "Вы выбрали элемент № %d со значением \"%s\".", index, sz_buffer);
			//эта функцияя выполняет форматирование строк
			//sz_message-буфер, в которую сохраница отформатированная строка
			//"Вы выбрали.."шаблонт строки, то как должна она выглядеть
			//в  этом шаблоне %d означает вставить в строку десятичное целое чило
			//%s-вствить в шаблонную строку подстроку
			//все вставляемые значения перечислены далее в передаваемых параметрах:index,sz_buffer ....
			//количество параметров функции sprintf()неограничено
			//функция sprintf()позваляет вставлять в строку какие-угодно значения
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
			break;//элемент интерфейса ок
		case IDCANCEL:EndDialog(hwnd, 0); break;//элемент интерфейса кансел
			
		}
		
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);//процедура закрытия окна
	}
	return FALSE;
}