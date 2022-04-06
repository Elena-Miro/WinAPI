#include<Windows.h>
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

	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCEA(IDI_APPLICATION));//в понели задач
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCEA(IDI_APPLICATION));//отражается в заголовке
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));
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
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_szClassName,//имя класса
		"Main Window",//заголовок
		WS_OVERLAPPEDWINDOW,//стиль главного окна приложения
		CW_USEDEFAULT, CW_USEDEFAULT,//положение окна на экране
		CW_USEDEFAULT, CW_USEDEFAULT,//размер окна по умолчанию
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
