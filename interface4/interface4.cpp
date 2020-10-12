#undef UNICODE
#include "framework.h"
#include "interface4.h"
#include <string>
#include <queue>
using std::string;
using std::queue;
HWND hWndDialog;

// Описание используемой оконной процедуры 
BOOL CALLBACK PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

// Главное приложение программы 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    MSG msg;

    // Создание диалогового окна 
    hWndDialog = CreateDialogParam(hInstance,
        MAKEINTRESOURCE(IDD_ABOUTBOX),
        NULL,
        (DLGPROC)PviewDlgProc,
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

//Процедура обработки сообщений диалогового окна 
BOOL CALLBACK PviewDlgProc(HWND hWnd,
    UINT wMsg,
    WPARAM wParam,
    LPARAM lParam) {

    queue <unsigned> q;
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
            HWND hList = GetDlgItem(hWnd, IDC_LIST1);
            HWND hEdit = GetDlgItem(hWnd, IDC_EDIT1);
            SendMessage(hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)text.data());

            q.push(atoi(text.data()));
            /*
            text = std::to_string(q.front());
            SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)text.data());
            */
            // сделать массив, которые перебирает все элементы очереди и кидает их в листбокс

            for (int i = 0; i < q.size(); i++) {
                text = std::to_string(q.front());
                // эта функция нихуя не работает, бля
                // надо сделать вторую очередь, где будет вывод эоемента первого, а потом его удаление 


                SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)text.data());
            }
            SendMessage(hList, WM_PAINT, 0, 0);

            
        
        
            break;
        }
        case IDOK:
            PostQuitMessage(0);
            break;
        case IDC_LIST1:
            if (HIWORD(wParam) == LBN_DBLCLK) /* например Двойной Клик */
            {
                HWND hList = GetDlgItem(hWnd, IDC_LIST1);

                //q.pop();

                // здесь почему-то q пустая, пофиксить
                while (!q.empty())
                {
                    SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)std::to_string(q.front()).data());
                    q.pop();
                }


                /*/
                for (int i = 0; i < q.size(); i++) {
                    text = std::to_string(q.front());
                    SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)text.data());
                }
                */
                SendMessage(hList, WM_PAINT, 0, 0);
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