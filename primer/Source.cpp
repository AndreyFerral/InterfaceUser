#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
using std::cout;
using std::string;

void SwitchSizeCursor() {
    CONSOLE_CURSOR_INFO CCI;
    srand(time(0)); // �������������� ������������
    CCI.dwSize = 1 + rand() % 100;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
}

void ClearTextFon()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 15));
}

void SetColorFon()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(0)); // �������������� ������������
    SetConsoleTextAttribute(hStdOut, (WORD)((1 + rand() % 13 << 4) | 15));
}

void SetColorText()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(0)); // �������������� ������������
    SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 1 + rand() % 13));
}

void func(COORD& positionMenu, HANDLE hConsole) {
    positionMenu.Y++; SetConsoleCursorPosition(hConsole, positionMenu);
}

void DeleteMenu(COORD& positionMenu, HANDLE hConsole) {
    SetConsoleCursorPosition(hConsole, positionMenu);
    for (int i = 0; i < 9; i++) {
        func(positionMenu, hConsole); cout << "                              ";
    }
    positionMenu = { 50, 10 };
}

void DeletePodMenu(HANDLE hConsole) {
    COORD pospal = { 63, 12 };

    SetConsoleCursorPosition(hConsole, pospal);
    for (int i = 0; i < 3; i++) {
        func(pospal, hConsole); cout << "                   ";
    }
    pospal = { 63, 12 };
}

void OutputPalitra(HANDLE hConsole) {

    string palitra[3] = {
    "-----------------",
    " ������ |  ���  |",
    "-----------------",
    };

    COORD pospal = { 63, 12 };
    SetConsoleCursorPosition(hConsole, pospal);
    for (int i = 0; i < 3; i++) {
        pospal.Y++; SetConsoleCursorPosition(hConsole, pospal); cout << palitra[i];
    }
    pospal = { 63, 12 };
}

enum { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, F2 = 60, ENTER = 13 };

int main()
{
    setlocale(LC_ALL, "rus");
    ClearTextFon();

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 15));

    COORD positionMenu = { 50, 10 };	                // ���������� ����������� ���������
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// ��������� ����������� ���������� ������������ ������

    string MENU[9] = {
        "-------------",
        "|  ������   |",
        "-------------",
        "|  �������  |",
        "-------------",
        "|  ���      |",
        "-------------",
        "|  �����    |",
        "-------------"
    };

    bool IsMenuWork = false;
    bool exit = false;
    char ch;
    COORD position = { 0, 0 };
    COORD StandartPosition = { 0, 0 };
    SetConsoleCursorPosition(hConsole, position);

    while (!exit) {
        ch = _getch();
        switch (ch) {
        case UP: {
            if (position.Y != 0 && IsMenuWork == true) {
                position.Y--; SetConsoleCursorPosition(hConsole, position);
                if (position.X >= 50 && position.X <= 62) {
                    if (position.Y >= 14 && position.Y <= 15) OutputPalitra(hConsole);
                    else DeletePodMenu(hConsole);
                    SetConsoleCursorPosition(hConsole, position);
                }
            }
            break;
        }
        case DOWN: {
            if (IsMenuWork == true) {
                position.Y++; SetConsoleCursorPosition(hConsole, position);
                if (position.X >= 50 && position.X <= 62) {
                    if (position.Y >= 14 && position.Y <= 15) OutputPalitra(hConsole);
                    else DeletePodMenu(hConsole);
                    SetConsoleCursorPosition(hConsole, position);
                }
            }
            break;
        }
        case LEFT: {
            if (position.X != 0 && IsMenuWork == true) {
                position.X--; SetConsoleCursorPosition(hConsole, position);
                if (position.X >= 50 && position.X <= 62) {
                    if (position.Y >= 14 && position.Y <= 15) OutputPalitra(hConsole);
                    else DeletePodMenu(hConsole);
                    SetConsoleCursorPosition(hConsole, position);
                }
            }
            break;
        }
        case RIGHT: {
            if (IsMenuWork == true) {
                position.X++; SetConsoleCursorPosition(hConsole, position);
                if (position.X >= 50 && position.X <= 62) {
                    if (position.Y >= 14 && position.Y <= 15) OutputPalitra(hConsole);
                    else DeletePodMenu(hConsole);
                    SetConsoleCursorPosition(hConsole, position);
                }
            }
            break;
        }
        case F2: {
            IsMenuWork = true;
            SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 15));
            SetConsoleCursorPosition(hConsole, positionMenu);
            for (int i = 0; i < 9; i++) {
                func(positionMenu, hConsole); cout << MENU[i];
            }
            positionMenu = { 50, 10 };
            SetConsoleCursorPosition(hConsole, StandartPosition);
            break;
        }
        case ENTER: {
            if (position.X >= 50 && position.X <= 62) {
                if (position.Y >= 11 && position.Y <= 13) {
                    IsMenuWork = false;
                    DeleteMenu(positionMenu, hConsole);
                    SwitchSizeCursor();
                    SetConsoleCursorPosition(hConsole, StandartPosition);
                }
                if (position.Y >= 16 && position.Y <= 17) {
                    IsMenuWork = false;
                    DeleteMenu(positionMenu, hConsole);
                    SetConsoleCursorPosition(hConsole, StandartPosition);
                }
                if (position.Y >= 18 && position.Y <= 19) {
                    ClearTextFon();
                    return 0;
                }
            }
            else if (position.Y >= 14 && position.Y <= 15) {
                if (position.X >= 63 && position.X <= 71) {
                    IsMenuWork = false;
                    DeleteMenu(positionMenu, hConsole);
                    SetColorText();
                    SetConsoleCursorPosition(hConsole, StandartPosition);
                }
                else if (position.X >= 72 && position.X <= 79) {
                    IsMenuWork = false;
                    DeleteMenu(positionMenu, hConsole);
                    SetColorFon();
                    SetConsoleCursorPosition(hConsole, StandartPosition);
                }
            }
            break;
        }

        case 82: { // ����� �
            if (IsMenuWork == true) {
                IsMenuWork = false;
                DeleteMenu(positionMenu, hConsole);
                SwitchSizeCursor();
                SetConsoleCursorPosition(hConsole, StandartPosition);
            }
            else cout << ch;
            break;
        }
        case 71: { // ����� �
            if (IsMenuWork == true) {
                IsMenuWork = false;
                DeleteMenu(positionMenu, hConsole);
                //SetColor();
                SetConsoleCursorPosition(hConsole, StandartPosition);
            }
            else cout << ch;
            break;
        }
        case 67: { // ����� C
            if (IsMenuWork == true) {
                IsMenuWork = false;
                DeleteMenu(positionMenu, hConsole);
                SetColorText();
                SetConsoleCursorPosition(hConsole, StandartPosition);
            }
            else cout << ch;
            break;
        }
        case 65: { // ����� �
            if (IsMenuWork == true) {
                IsMenuWork = false;
                DeleteMenu(positionMenu, hConsole);
                SetColorFon();
                SetConsoleCursorPosition(hConsole, StandartPosition);
            }
            else cout << ch;
            break;
        }
        case 39: { // ����� �
            if (IsMenuWork == true) {
                IsMenuWork = false;
                DeleteMenu(positionMenu, hConsole);
                SetConsoleCursorPosition(hConsole, StandartPosition);
            }
            else cout << ch;
            break;
        }
        case 68: { // ����� �
            if (IsMenuWork == true) { return 0; }
            else cout << ch;
            break;
        }
        default:
            if (IsMenuWork == false && ch > 0) cout << ch;
            break;
        }
    }
    return 0;
}