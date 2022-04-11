#define _CRT_SECURE_NO_WARNINGS
#include<winapifamily.h>
#include<Windows.h>
#include<stdio.h>
#include"resource.h"

#define IDC_MY_STATIC 104

CONST CHAR g_szClassName[] = "My Window Class";//global sz-string ziro
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCMDLine, int nCmdShow)
{
	//Регистрация класса окна
	WNDCLASSEX wc; //wc- windows class
	ZeroMemory(&wc, sizeof(WNDCLASS));//зануляем класс wc
	//инициализируем поля структуры wc
	wc.cbSize = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;//задаем процедуру окна для данного класса
	wc.style = 0;//стиль окна.дополнительные свойства
	//набор возможных стилей зависит от класса окна
	wc.hIcon = (HICON)LoadImage(hInstance, "phone.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "sleep.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));//в понели задач
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));//отражается в заголовке
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;
	//NULL-меню отсутствует
	wc.lpszClassName = g_szClassName;
	//Регистрация окна

	if (!RegisterClassEx(&wc))//если класс окна не зарегистрировался, прерываем программу
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//2)Создание окна
	int screen_width = GetSystemMetrics(SM_CXSCREEN);//получает некоторые параметры системы.см-систем метрик размер экрана по х
	int screen_height = GetSystemMetrics(SM_CYSCREEN);//по y
	int window_start_x = screen_width / 8;
	int window_start_y = screen_height / 8;
	int window_width = screen_width - screen_width / 4;
	int window_height = screen_height - screen_height / 4;
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_szClassName,//имя класса
		"Main Window",//заголовок
		WS_OVERLAPPEDWINDOW,//стиль главного окна приложения
		window_start_x, window_start_y,//положение окна на экране
		window_width, window_height,//размер окна по умолчанию
		NULL,//родительское окно , оно отсутствует
		NULL,//меню или id дочернего окна //id меню окна,если оно главное.или ресурса,если дочернее
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Info", MB_OK | MB_ICONERROR);

	}
	ShowWindow(hwnd, nCmdShow);//задаем режим отображения
	UpdateWindow(hwnd);//прорисовка окна

	//3)Запуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)//берет сообщение из очереди сообщений текущего потока
	{
		TranslateMessage(&msg);//преобразует виртуальные клавиши в символы
		DispatchMessage(&msg);//отправляет сообщения в процедуру окна
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE: //создаются элемнты окна,кнопки,меню,значки аналог WM_INITDIALOG
		//это сообщение отрабатывает один раз
		CreateWindowEx
		(
			NULL,
			"Static",
			"Это мой статический текст, в котором будет отображаться размер окна и его положение на экране",
			WS_CHILDWINDOW|WS_VISIBLE,
			10,10,
			10000,50,
			hwnd,
			(HMENU)IDC_MY_STATIC,
			GetModuleHandle(NULL),
			NULL

		);
	
		break;
	case WM_MOVE:

	case WM_SIZE:
	{
		CONST INT SIZE = 256;
		CHAR buffer[SIZE] = {};
		RECT rect;//объявляем прямоугольник
		GetWindowRect(hwnd, &rect);
		int window_width = rect.right - rect.left;
		int window_height = rect.bottom - rect.top;
		sprintf(buffer, "Size:%dx%d, Position:%dx%d" , window_width, window_height,rect.left,rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)buffer);
		HWND hStatic = GetDlgItem(hwnd, IDC_MY_STATIC);
		SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)buffer);
	}
		break;
	case WM_COMMAND:break;
	case WM_CLOSE:
		//посылает сообщение DestroyWindow своему окну
		if(MessageBox(hwnd,"Вы действительно хотите закрыть сообщение?","Серьезно?",MB_YESNO|MB_ICONQUESTION)==IDYES)
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		//отправляет сообщение о прекращении работы
		PostQuitMessage(0);
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
