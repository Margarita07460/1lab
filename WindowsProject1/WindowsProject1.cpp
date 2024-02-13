// WindowsProject1.cpp : Определяет точку входа для приложения.
// lab1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject1.h"
#include "math.h"


#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

double tree[15][3] = { {140, 20, 1},
                                {140, 260, 1},
                                {120, 260, 1},
                                {160, 260, 1},

                                {120, 40, 1},
                                {160, 40, 1},

                                {100, 100, 1},
                                {140, 60, 1},
                                {180, 100, 1},

                                {80, 160, 1},
                                {140, 100, 1},
                                {200, 160, 1},

                                {60, 220, 1},
                                {140, 140, 1},
                                {220 ,220, 1}, };

double current_tree[15][3] = { {140, 20, 1},
                                {140, 260, 1},
                                {120, 260, 1},
                                {160, 260, 1},

                                {120, 40, 1},
                                {160, 40, 1},

                                {100, 100, 1},
                                {140, 60, 1},
                                {180, 100, 1},

                                {80, 160, 1},
                                {140, 100, 1},
                                {200, 160, 1},

                                {60, 220, 1},
                                {140, 140, 1},
                                {220 ,220, 1}, };


//Матрицы аффинных преобразований

double CarryMatrix[3][3] = { {1, 0, 0},                                                          //расчет расстояния = 2 длины объекта
                           {0, 1, 0},
                            {300, 0, 1} };


double ScaleMatrix[3][3] = { {4, 0, 0},
                            {0, 1, 0},
                            {0, 0, 1} };






double RotateMatrix[3][3] = {                                              //перевод в радианы
                               { cos(1.22), sin(1.22), 0},
                            {  -sin(1.22), cos(1.22),0} ,
                            { 50, 0,1 }, };


//double RotateMatrix[3][3] = { {cos(1.22), 0,  -sin(1.22)},
//                            {0, 1, 0},
//                            {sin(1.22),0, cos(1.22)} };

double rezult[3][3];

//Функция перемножения координат объекта и матрицы преобразований
void MultMatrix(double AffinMatrix[3][3]) {

    double tmp = 0;

    for (int k = 0; k < 15; k++) {
        for (int i = 0; i < 3; i++) {

            for (int j = 0; j < 3; j++) {
                tmp += AffinMatrix[j][i]* current_tree[k][j] ;
            }

            current_tree[k][i] = tmp;
            tmp = 0;
        }
    }

    return;
}

void FunctionStart() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 3; j++) {
            current_tree[i][j] = tree[i][j];
        }
    }
    return;
}








// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        case IDM_START:
            FunctionStart();
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;

        case IDM_MOVE:
            MultMatrix(CarryMatrix);
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;

        case IDM_SCALE:
            MultMatrix(ScaleMatrix);
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;

        case IDM_ROTATE:
            MultMatrix(RotateMatrix);
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;




    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...



        MoveToEx(hdc, current_tree[0][0], current_tree[0][1], 0);
        LineTo(hdc, current_tree[1][0], current_tree[1][1]);
        MoveToEx(hdc, current_tree[2][0], current_tree[2][1], 0);
        LineTo(hdc, current_tree[3][0], current_tree[3][1]);
       
        
        MoveToEx(hdc, current_tree[4][0], current_tree[4][1], 0);
        LineTo(hdc, current_tree[0][0], current_tree[0][1]);
        LineTo(hdc, current_tree[5][0], current_tree[5][1]);

        for (int i = 6; i < 16; i += 3) {
            MoveToEx(hdc, current_tree[i][0], current_tree[i][1], 0);
            LineTo(hdc, current_tree[i+1][0], current_tree[i+1][1]);
            LineTo(hdc, current_tree[i + 2][0], current_tree[i + 2][1]);
        }
       

       
       // MoveToEx(hdc, current_tree[3][0], current_tree[3][1], 0);
       
        EndPaint(hWnd, &ps);

    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
