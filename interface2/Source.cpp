#include <iostream>
#include <windows.h>
#include <conio.h>
using std::cout;
using std::string;

void Fill() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 0));
}
void Clear() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 15));
}
void HideCursor() {
    CONSOLE_CURSOR_INFO CCI;
    CCI.bVisible = false;
    CCI.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
}
void FirstRun(HANDLE hConsole, COORD position) {
    COORD position1 = { 1, 1 };
    SetConsoleCursorPosition(hConsole, position1);
    cout << " Богатства недр ";
    SetConsoleCursorPosition(hConsole, position);
}
void DrawMenu(HANDLE hConsole) {
    COORD standpos = { 0, 0 };
    string menu[9] = {
    "+------------------------------------------------------------+",
    "| Богатства недр | Растительный мир | Водные ресурсы | Выход |",
    "+------------------------------------------------------------+",
    "                                                              ",
    "                                                              ",
    "                                                              ",
    "                                                              ",
    "                                                              ",
    "                                                              ",
    };

    Clear();
    SetConsoleCursorPosition(hConsole, standpos);
    for (int i = 0; i < 9; i++) {
        cout << menu[i] << "\n";
    }
}
void DrawMenuMineralRes(HANDLE hConsole) {
    string menu1[7] = {
    "+----------+",
    "| Топливые |",
    "|----------|",
    "| Рудные   |",
    "|----------|",
    "| Нерудные |",
    "+----------+",
    };

    COORD menu2 = { 6, 1 };
    for (int i = 0; i < 7; i++) {
        menu2.Y++; SetConsoleCursorPosition(hConsole, menu2);
        cout << menu1[i] << "\n";
    }
    menu2 = { 6, 1 };
}
void DrawMenuForestRes(HANDLE hConsole) {
    string menu2[7] = {
    "+------------------+",
    "| Лесные           |",
    "|------------------|",
    "| Кормовые         |",
    "|------------------|",
    "| Пищевые ресурсы  |",
    "+------------------+",
    };

    COORD menu3 = { 17, 1 };
    for (int i = 0; i < 7; i++) {
        menu3.Y++; SetConsoleCursorPosition(hConsole, menu3);
        cout << menu2[i] << "\n";
    }
    menu3 = { 17, 1 };
}
void FillMenuText(HANDLE hConsole, COORD position) {
    COORD position1 = { 1, 1 };
    COORD position2 = { 18, 1 };
    COORD position3 = { 37, 1 };
    COORD position4 = { 54, 1 };

    string menutext[4] = {
    " Богатства недр ",
    " Растительный мир ",
    " Водные ресурсы ",
    " Выход ",
    };

    if (position.X == 10 && position.Y == 1) {
        SetConsoleCursorPosition(hConsole, position1);
        cout << menutext[0];
    }

    if (position.X == 25 && position.Y == 1) {
        SetConsoleCursorPosition(hConsole, position2);
        cout << menutext[1];
    }

    if (position.X == 40 && position.Y == 1) {
        SetConsoleCursorPosition(hConsole, position3);
        cout << menutext[2];
    }

    if (position.X == 55 && position.Y == 1) {
        SetConsoleCursorPosition(hConsole, position4);
        cout << menutext[3];
    }
    SetConsoleCursorPosition(hConsole, position);
}
void FillMenuTextMineralRes(HANDLE hConsole, COORD position) {
    COORD position1 = { 1, 1 };
    COORD position5 = { 7, 3 };
    COORD position6 = { 7, 5 };
    COORD position7 = { 7, 7 };

    string menu1text[3] = {
    " Топливые ",
    " Рудные   ",
    " Нерудные ",
    };

    if (position.Y == 1) {
        SetConsoleCursorPosition(hConsole, position1);
        cout << " Богатства недр ";
    }
    if (position.Y == 3) {
        SetConsoleCursorPosition(hConsole, position5);
        cout << menu1text[0];
    }
    if (position.Y == 5) {
        SetConsoleCursorPosition(hConsole, position6);
        cout << menu1text[1];
    }
    if (position.Y == 7) {
        SetConsoleCursorPosition(hConsole, position7);
        cout << menu1text[2];
    }
}
void FillMenuTextForestRes(HANDLE hConsole, COORD position) {
    COORD position2 = { 18, 1 };
    COORD position8 = { 18, 3 };
    COORD position9 = { 18, 5 };
    COORD position10 = { 18, 7 };

    string menu2text[3] = {
    " Лесные  ",
    " Кормовые  ",
    " Пищевые ресурсы  ",
    };
    
    if (position.Y == 1) {
        SetConsoleCursorPosition(hConsole, position2);
        cout << " Растительный мир ";
    }

    if (position.Y == 3) {
        SetConsoleCursorPosition(hConsole, position8);
        cout << menu2text[0];
    }
    if (position.Y == 5) {
        SetConsoleCursorPosition(hConsole, position9);
        cout << menu2text[1];
    }
    if (position.Y == 7) {
        SetConsoleCursorPosition(hConsole, position10);
        cout << menu2text[2];
    }
}


enum { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13 };

int main() {
    setlocale(LC_ALL, "rus");
    HideCursor();

    bool IsMineralResWork = false;
    bool IsForestResWork = false;
    bool IsWaterResWork = false;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// Получение дескриптора устройства стандартного вывода
    COORD position = { 10, 1 };

    DrawMenu(hConsole); Fill();
    FirstRun(hConsole, position);

    bool exit = false;
    char ch;
    while (!exit) {
        ch = _getch();
        switch (ch) {
        case UP: {
            if (position.X == 10 && position.Y > 2) {
                position.Y = position.Y - 2;
                
                DrawMenu(hConsole);
                DrawMenuMineralRes(hConsole); Fill();
                FillMenuTextMineralRes(hConsole, position);
                Clear(); SetConsoleCursorPosition(hConsole, position);
            }

            if (position.X == 25 && position.Y > 2) {
                position.Y = position.Y - 2;

                DrawMenu(hConsole);
                DrawMenuForestRes(hConsole); Fill();
                FillMenuTextForestRes(hConsole, position);
                Clear(); SetConsoleCursorPosition(hConsole, position);
            }

            break;
        }
        case DOWN: {
            if (IsMineralResWork == true) {
                if (position.X == 10 && position.Y < 6) {
                    position.Y = position.Y + 2;

                    DrawMenu(hConsole);
                    DrawMenuMineralRes(hConsole); Fill();
                    FillMenuTextMineralRes(hConsole, position);
                }
            }

            if (IsForestResWork == true) {
                if (position.X == 25 && position.Y < 6) {
                    position.Y = position.Y + 2;

                    DrawMenu(hConsole);
                    DrawMenuForestRes(hConsole); Fill();
                    FillMenuTextForestRes(hConsole, position);
                }
            }
            if (IsWaterResWork == true) {
                if (position.X == 45 && position.Y < 6) {
                    position.Y = position.Y + 2;
                    
                }
            }
            Clear(); SetConsoleCursorPosition(hConsole, position);
            break;
        }
        case LEFT: {
            if (position.X > 10 && position.Y == 1) {
                position.X = position.X - 15;
                DrawMenu(hConsole); Fill();
                FillMenuText(hConsole, position);
            }
            break;
        }
        case RIGHT: {
           if (position.X < 46 && position.Y == 1) {
               position.X = position.X + 15;
               DrawMenu(hConsole); Fill();
               FillMenuText(hConsole, position);
           }
            break;
        }
        case ENTER: {
            if (position.X == 10 && position.Y == 1) {
                IsMineralResWork = true;
                IsForestResWork = false;
                IsWaterResWork = false;
                Clear(); DrawMenuMineralRes(hConsole);
                SetConsoleCursorPosition(hConsole, position);
            }

            if (position.X == 25 && position.Y == 1) {
                IsMineralResWork = false;
                IsForestResWork = true;
                IsWaterResWork = false;
                Clear(); DrawMenuForestRes(hConsole);
                SetConsoleCursorPosition(hConsole, position);
            }

            if (position.X == 40 && position.Y == 1) {
                IsMineralResWork = false;
                IsForestResWork = false;
                IsWaterResWork = true;
            }

            if (position.X == 55 && position.Y == 1) {
                Clear();
                return 0;
            }
            break;
        }

        default: break;
        }
    }
    return 0;
}