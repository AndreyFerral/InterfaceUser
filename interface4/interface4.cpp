// interface5.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "interface4.h"



HWND hWndDialog;
//HINSTANCE ghInstance; // Переменная для хранения хендела процесса 

// Описание используемой оконной процедуры 
BOOL CALLBACK PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

// Главное приложение программы 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    MSG msg;
    //ghInstance = hInstance;

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