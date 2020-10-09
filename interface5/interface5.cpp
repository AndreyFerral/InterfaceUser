#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include "framework.h"
#include "interface5.h"



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
        TCHAR buff1[128];
        TCHAR buff2[128];
        char buff3[128];
        int x = 0, y = 0, z = 0;

        switch (LOWORD(wParam))
        {
        case IDOK:
            PostQuitMessage(0);
            break;
        case IDC_BUTTON1: {
            HWND hList = GetDlgItem(hWnd, IDC_LIST1);
            HWND hEdit3 = GetDlgItem(hWnd, IDC_EDIT3);
            HWND hEdit4 = GetDlgItem(hWnd, IDC_EDIT4);
            //SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("ывывыв"));

            GetWindowText(hEdit3, buff1, 128);
            GetWindowText(hEdit4, buff2, 128);

            //SendMessage(hEdit3, WM_GETTEXT, MAX_PATH, buff1);
            //SendMessage(hEdit4, WM_GETTEXT, MAX_PATH, buff2);

            x = _ttoi(buff1);
            y = _ttoi(buff2);

            SendMessage(hList, LB_RESETCONTENT, 0, 0);

            if (x > 0 && y > 0) {
                z = x - y;

                // buff3 = itoa(z);
                _itoa(z, buff3, 10);
                //buff3 = (LPARAM)z;

                //_stprintf(buff3, TEXT("%d"), z);
                SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)buff3);
            }
            else SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("Error"));

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