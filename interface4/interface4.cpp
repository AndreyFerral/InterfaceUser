#undef UNICODE
#include "framework.h"
#include "interface4.h"
#include <string>
#include <queue>
using std::string;
using std::queue;
HWND hWndDialog;
HWND hWndDialog1;
HINSTANCE hInst;                                // текущий экземпляр


// Описание используемой оконной процедуры 
BOOL CALLBACK PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

//BOOL CALLBACK PviewDlgProc1(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);


// Главное приложение программы 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    MSG msg;

    // Создание диалогового окна 
    hWndDialog = CreateDialogParam(hInstance,
        MAKEINTRESOURCE(IDD_DIALOG1),
        NULL,
        (DLGPROC)0,
        (LONG)0);
    ShowWindow(hWndDialog, nCmdShow);
    UpdateWindow(hWndDialog);
    // Стандартный цикл обработки сообщений приложения 
    while (GetMessage(&msg, NULL, 0, 0))
        if (!IsDialogMessage(hWndDialog, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    DestroyWindow(hWndDialog);
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
        case IDC_BUTTON1: {
            
            HWND hEdit = GetDlgItem(hWnd, IDC_EDIT1);
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
/*
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case ID_32771: {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), 0, PviewDlgProc);
        }
            break;
        case ID_32772: DestroyWindow(hWnd); break;
        default: return DefWindowProc(hWnd, message, wParam, lParam);
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
}*/


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case ID_32771: DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), 0, PviewDlgProc); break;
        case ID_32772: DestroyWindow(hWnd); break;
        default: return DefWindowProc(hWnd, message, wParam, lParam);
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

/*
BOOL CALLBACK PviewDlgProc1(HWND hWnd,
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
        case IDOK:
            PostQuitMessage(0);
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
*/