// Interface3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Interface3.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_INTERFACE3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INTERFACE3));

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

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INTERFACE3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_INTERFACE3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

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
            case IDABORT:
                DestroyWindow(hWnd);
                break;
            case ID_32771:
                MessageBox(NULL, L"К топливным относятся такие полезные искомаемые, как нефть, природный газ, уголь, торф и горячие сланцы.", L"Топливные", MB_OK);
                break;
            case ID_32772:
                MessageBox(NULL, L"Рудные минеральные ресурсы разделяют на руды черных металлов и цветных металлов. \nК черным металлам относятся: железо, марганца, хрома. \nК цветным металлам относятся: медь, свинец, цинк и алюминей.", L"Рудные", MB_OK);
                break;
            case ID_32773:
                MessageBox(NULL, L"Нерудные минеральные ресурсы разделяют на химическое сырье, строительные материалы и драгоценные камни. \nК химическому сырью относятся: калийные соли, сера, фосфит, апатит и пирит. \nК строительным материалам относятся: гранит, известняк, песок и глина. \nК драгоценным камням относятся: алмаз, изумруд, рубин, сапфир, яшма и агат.", L"Нерудные", MB_OK);
                break;
            case ID_32774:
                MessageBox(NULL, L"Лесные минеральные ресурсы разделяют на древесные и недревесные. \nК недревесным относятся: ягоды, грибы, орехи, смола и лекарственные растения.", L"Лесные ресурсы", MB_OK);
                break;
            case ID_32775:
                MessageBox(NULL, L"К кормовым ресурсам относятся травы сенокосов и пастбищ.", L"Кормовые ресурсы", MB_OK);
                break;
            case ID_32776:
                MessageBox(NULL, L"К пищевым растительным ресурсам морей относятся водоросли.", L"Пищевые растительные ресурсы морей", MB_OK);
                break;
            case ID_32777:
                MessageBox(NULL, L"К водным ресурсам в жидком состоянии относятся океана, моря, озера, реки, болота, подземные воды и искуственно-созданные водоемы.", L"Водные ресурсы жидкого состояния", MB_OK);
                break;
            case ID_32778:
                MessageBox(NULL, L"К водным ресурсам газообразного состояния относится парообразное состояние атмосферы.", L"Водные ресурсы газообразного состояния", MB_OK);
                break;
            case ID_32779:
                MessageBox(NULL, L"К водным ресурсам твердого состояния относятся: замерзшая вода ледников Антарктиды, Арктики и снежные вершины гор.", L"Водные ресурсы твердого состояния", MB_OK);
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