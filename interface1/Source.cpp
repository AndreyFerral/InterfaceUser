#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
using std::cout;
using std::string;

void SwitchSizeCursor() {
    CONSOLE_CURSOR_INFO CCI;
    srand(time(0)); // автоматическая рандомизация
    CCI.dwSize = 1 + rand() % 100;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
}

void SetColor()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(0)); // автоматическая рандомизация
    SetConsoleTextAttribute(hStdOut, (WORD)((1 + rand() % 13 << 4) | 15));
}

void func(COORD& positionMenu, HANDLE hConsole) {
    positionMenu.Y++; SetConsoleCursorPosition(hConsole, positionMenu);
}

void DeleteMenu(COORD& positionMenu, HANDLE hConsole) {
    SetConsoleCursorPosition(hConsole, positionMenu);
    for (int i = 0; i < 9; i++) {
        func(positionMenu, hConsole); cout << "             ";
    }
    positionMenu = { 50, 10 };
}

enum { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, F2 = 60, ENTER = 13 };

int main()
{
    setlocale(LC_ALL, "rus");

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 15));

    COORD positionMenu = { 50, 10 };	                // Объявление необходимой структуры
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// Получение дескриптора устройства стандартного вывода

    string MENU[9] = {
        "-------------",
        "|  Курсор   |",
        "-------------",
        "|  Палитра  |",
        "-------------",
        "|  Эхо      |",
        "-------------",
        "|  Выход    |",
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
            }
            break;
        }
        case DOWN: {
            if (IsMenuWork == true) {
                position.Y++; SetConsoleCursorPosition(hConsole, position);
            }
            break;
        }
        case LEFT: {
            if (position.X != 0 && IsMenuWork == true) {
                position.X--; SetConsoleCursorPosition(hConsole, position);
            }
            break;
        }
        case RIGHT: {
            if (IsMenuWork == true) {
                position.X++; SetConsoleCursorPosition(hConsole, position);
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
            if (position.X >= 50 && position.X <= 62 && position.Y >= 11 && position.Y <= 13) {
                IsMenuWork = false;
                DeleteMenu(positionMenu, hConsole);
                SwitchSizeCursor();
                SetConsoleCursorPosition(hConsole, StandartPosition);
            }
            if (position.X >= 50 && position.X <= 62 && position.Y >= 14 && position.Y <= 15) {
                IsMenuWork = false;
                DeleteMenu(positionMenu, hConsole);
                SetColor();
                SetConsoleCursorPosition(hConsole, StandartPosition);
            }
            if (position.X >= 50 && position.X <= 62 && position.Y >= 16 && position.Y <= 17) {
                IsMenuWork = false;
                DeleteMenu(positionMenu, hConsole);
                SetConsoleCursorPosition(hConsole, StandartPosition);
            }
            if (position.X >= 50 && position.X <= 62 && position.Y >= 18 && position.Y <= 19) {
                return 0;
            }
            break;
        }
        case 82: { // буква К
            if (IsMenuWork == true) {
                IsMenuWork = false;
                DeleteMenu(positionMenu, hConsole);
                SwitchSizeCursor();
                SetConsoleCursorPosition(hConsole, StandartPosition);
            }
            else cout << ch;
            break;
        }
        case 71: { // буква П
            if (IsMenuWork == true) {
                IsMenuWork = false;
                DeleteMenu(positionMenu, hConsole);
                SetColor();
                SetConsoleCursorPosition(hConsole, StandartPosition);
            }
            else cout << ch;
            break;
        }
        case 39: { // буква Э
            if (IsMenuWork == true) {
                IsMenuWork = false;
                DeleteMenu(positionMenu, hConsole);
                SetConsoleCursorPosition(hConsole, StandartPosition);
            }
            else cout << ch;
            break;
        }
        case 68: { // буква В
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