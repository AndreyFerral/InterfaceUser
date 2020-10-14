#undef UNICODE
#include "framework.h"
#include "interfac4.h"
#include <string>
#include <queue>
using std::string;
using std::queue;
HWND hwnm;

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
BOOL CALLBACK PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

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
    LoadStringW(hInstance, IDC_INTERFAC4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INTERFAC4));

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
    wcex.hIcon          = 0;
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_INTERFAC4);
    wcex.lpszClassName  = szWindowClass;
   wcex.hIconSm        = 0;

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
            case IDM_ABOUT:
                hwnm = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX1), hWnd, PviewDlgProc);
                ShowWindow(hwnm, SW_SHOW);
                UpdateWindow(hwnm);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
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
void OutputQueue(queue <unsigned> q, HWND hWnd) {
    HWND hList = GetDlgItem(hWnd, IDC_LIST1);
    SendMessage(hList, LB_RESETCONTENT, 0, 0);

    while (!q.empty())
    {
        SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)std::to_string(q.front()).data());
        q.pop();
    }

    SendMessage(hList, WM_PAINT, 0, 0);

}

queue <unsigned> q;
int count = 0;

//Процедура обработки сообщений диалогового окна 
BOOL CALLBACK PviewDlgProc(HWND hWnd,
    UINT wMsg,
    WPARAM wParam,
    LPARAM lParam) {

    string text;

    switch (wMsg) {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
        //перед отображением на экране диалогового окна
    case WM_INITDIALOG: {
        break;
    }
    case WM_PAINT: {
        break;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam))
        {
        case ADDELEM: {

            HWND hEdit = GetDlgItem(hWnd, IDC_ADD);
            SendMessage(hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)text.data());
            if (atoi(text.data()) > 0) q.push(atoi(text.data()));
            OutputQueue(q, hWnd);
        }
                        break;
        case IDOK:
            PostQuitMessage(0);
            break;
        case IDC_LIST1:
            if (HIWORD(wParam) == LBN_DBLCLK) {
                q.pop();
                OutputQueue(q, hWnd);
            }
            break;
        default:
            return FALSE;
        }
        break;
    }
    default: return FALSE;
    }
    return TRUE;
}