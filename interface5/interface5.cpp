#undef UNICODE
#include "framework.h"
#include "interface5.h"
#include <string>
using std::string;
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

void split(string str, string* mstr) {
    int i = 0;
    while (str.data()[i] != '\r') {
        mstr[0] += str.data()[i];
        i++;
    }
    i += 2;
    while (str.data()[i] != '\0') {
        mstr[1] += str.data()[i];
        i++;
    }
}

bool OneNumber(string str) {
    int i = 0;
    while (str.data()[i] != '\0') {
        if (str.data()[i] == '\r') { return FALSE; }
        i++;
    }
    return TRUE;
}

int ResultSubstraction = 0;

//Процедура обработки сообщений диалогового окна 
BOOL CALLBACK PviewDlgProc(HWND hWnd,
	UINT wMsg,
	WPARAM wParam,
	LPARAM lParam) {

    string text;
    string ResSub;
    int FirstNumber = 0;
    int SecondNumber = 0;

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
        case IDC_BUTTON1:
        {
            HWND hList = GetDlgItem(hWnd, IDC_LIST1);
            HWND hEdit3 = GetDlgItem(hWnd, IDC_EDIT3);

            SendMessage(hEdit3, WM_GETTEXT, MAX_PATH, (LPARAM)text.data());
            string mstr[2];

            if (OneNumber(text) == FALSE) {
                split(text, mstr);

                FirstNumber = atoi(mstr[0].data());
                SecondNumber = atoi(mstr[1].data());
                if (FirstNumber > 0 && SecondNumber > 0) {
                   ResultSubstraction = FirstNumber - SecondNumber;
                   ResSub = std::to_string(ResultSubstraction);
                   SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)ResSub.data());
                }
                else SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)"error");
            }
            else {
                FirstNumber = atoi(text.data());
                if (FirstNumber > 0) {
                    ResultSubstraction = ResultSubstraction - FirstNumber;
                    ResSub = std::to_string(ResultSubstraction);
                    SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)ResSub.data());
                }
                else SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)"error");

            }

            SendMessage(hList, WM_PAINT, 0, 0);
            break;
        }
        default:
            return FALSE;
        }
        break;
    }
	default: return FALSE;
	}
	return TRUE;
}