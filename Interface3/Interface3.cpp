#include "Header.h"
#include "framework.h"
#include "Interface3.h"



#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
int NumberText = 0;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK   PviewDlgProc1(HWND    hWnd, UINT    wMsg, WPARAM  wParam, LPARAM  lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    ULONG_PTR token;
    GdiplusStartupInput input;
    input.GdiplusVersion = 1;
    GdiplusStartup(&token, &input, NULL);

    //UNREFERENCED_PARAMETER(hPrevInstance);
    //UNREFERENCED_PARAMETER(lpCmdLine);

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
    GdiplusShutdown(token);
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

BOOL CALLBACK   PviewDlgProc1(HWND    hDlg,
    UINT    wMsg,
    WPARAM  wParam,
    LPARAM  lParam)
{ 

    static int lx = 350, ly = 150;
    static RECT rect; // координаты прямоугольника
    static HDC hdc, hdcm; // контекст устройтва
    static PAINTSTRUCT ps; // структура для перерисовки окна
    static HBITMAP hbm; // дескриптор изображения
    static HBRUSH hbr; // дескриптор кисти

    switch (wMsg)
    {
        // сообщение об инициализации диалоговой формы
    case WM_INITDIALOG: {
        switch (NumberText) {
        case 1: SetWindowText(GetDlgItem(hDlg, IDC_STATIC1), L"К топливным относятся такие полезные искомаемые, как нефть, природный газ, уголь, торф и горячие сланцы."); break;
        case 2: SetWindowText(GetDlgItem(hDlg, IDC_STATIC1), L"Рудные минеральные ресурсы разделяют на руды черных металлов и цветных металлов. К черным металлам относятся: железо, марганца, хрома. К цветным металлам относятся: медь, свинец, цинк и алюминей."); break;
        case 3: SetWindowText(GetDlgItem(hDlg, IDC_STATIC1), L"Нерудные минеральные ресурсы разделяют на химическое сырье, строительные материалы и драгоценные камни. К химическому сырью относятся: калийные соли, сера, фосфит, апатит и пирит. К строительным материалам относятся: гранит, известняк, песок и глина. К драгоценным камням относятся: алмаз, изумруд, рубин, сапфир, яшма и агат."); break;
        case 4: SetWindowText(GetDlgItem(hDlg, IDC_STATIC1), L"Лесные минеральные ресурсы разделяют на древесные и недревесные. К недревесным относятся: ягоды, грибы, орехи, смола и лекарственные растения."); break;
        case 5: SetWindowText(GetDlgItem(hDlg, IDC_STATIC1), L"К кормовым ресурсам относятся травы сенокосов и пастбищ."); break;
        case 6: SetWindowText(GetDlgItem(hDlg, IDC_STATIC1), L"К пищевым растительным ресурсам морей относятся водоросли."); break;
        case 7: SetWindowText(GetDlgItem(hDlg, IDC_STATIC1), L"К водным ресурсам в жидком состоянии относятся океана, моря, озера, реки, болота, подземные воды и искуственно-созданные водоемы."); break;
        case 8: SetWindowText(GetDlgItem(hDlg, IDC_STATIC1), L"К водным ресурсам газообразного состояния относится парообразное состояние атмосферы."); break;
        case 9: SetWindowText(GetDlgItem(hDlg, IDC_STATIC1), L"К водным ресурсам твердого состояния относятся: замерзшая вода ледников Антарктиды, Арктики и снежные вершины гор."); break; }
    }
        break;
    case WM_CLOSE:
        EndDialog(hDlg, (INT_PTR)TRUE);
        break;

    case WM_PAINT:
    {
        static PAINTSTRUCT ps; // структура для перерисовки окна
        HDC hdc = BeginPaint(GetDlgItem(hDlg, IDC_STATIC123), &ps); // получить контекст устройства

        switch (NumberText) {
        case 1: DrawImage(hdc, L"1.jpg", 0, 0, lx, ly); break;
        case 2: DrawImage(hdc, L"2.jpg", 0, 0, lx, ly); break;
        case 3: DrawImage(hdc, L"3.jpg", 0, 0, lx, ly + 50); break;
        case 4: DrawImage(hdc, L"4.jpg", 0, 0, lx, ly + 50); break;
        case 5: DrawImage(hdc, L"5.jpg", 0, 0, lx, ly + 50); break;
        case 6: DrawImage(hdc, L"6.jpg", 0, 0, lx, ly + 50); break;
        case 7: DrawImage(hdc, L"7.jpg", 0, 0, lx, ly + 50); break;
        case 8: DrawImage(hdc, L"8.jpg", 0, 0, lx, ly + 50); break;
        case 9: DrawImage(hdc, L"9.jpg", 0, 0, lx, ly + 50); break; }

        EndPaint(GetDlgItem(hDlg, IDC_STATIC123), &ps);
        break;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            EndDialog(hDlg, (INT_PTR)TRUE);
            break;
        default:
            return FALSE;
        }
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId) {
            case IDABORT: DestroyWindow(hWnd); break;
            case ID_32771: NumberText = 1; DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), 0, PviewDlgProc1); break;
            case ID_32772: NumberText = 2; DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), 0, PviewDlgProc1); break;
            case ID_32773: NumberText = 3; DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), 0, PviewDlgProc1); break;
            case ID_32774: NumberText = 4; DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), 0, PviewDlgProc1); break;
            case ID_32775: NumberText = 5; DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), 0, PviewDlgProc1); break;
            case ID_32776: NumberText = 6; DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), 0, PviewDlgProc1); break;
            case ID_32777: NumberText = 7; DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), 0, PviewDlgProc1); break;
            case ID_32778: NumberText = 8; DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), 0, PviewDlgProc1); break;
            case ID_32779: NumberText = 9; DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), 0, PviewDlgProc1); break;
            default: return DefWindowProc(hWnd, message, wParam, lParam); }
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