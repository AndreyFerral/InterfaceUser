#include <iostream>
#include <windows.h>
#include <conio.h>
using std::cout;
using std::string;

void Fill()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 0));
}
void Clear()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 15));
}
void HideCursor() {
    CONSOLE_CURSOR_INFO CCI;
    CCI.bVisible = false;
    CCI.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
}
void DrawMenu(HANDLE hConsole, COORD standpos) {
    string menu[3] = {
    "+------------------------------------------------------------+",
    "| Богатства недр | Растительный мир | Водные ресурсы | Выход |",
    "+------------------------------------------------------------+",
    };

    Clear();
    SetConsoleCursorPosition(hConsole, standpos);
    for (int i = 0; i < 3; i++) {
        cout << menu[i] << "\n";
    }
    Fill();
}

enum { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13 };

int main() {
    setlocale(LC_ALL, "rus");
    HideCursor();

    /*
    string menu[3] = {
        "+------------------------------------------------------------+",
        "| Богатства недр | Растительный мир | Водные ресурсы | Выход |",
        "+------------------------------------------------------------+",
    };
    */

    string menutext[4] = {
        " Богатства недр ",
        " Растительный мир ",
        " Водные ресурсы ",
        " Выход ",
    };
    /*
    for (int i = 0; i < 3; i++) {
        cout << menu[i] << "\n";
    }
    */

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// Получение дескриптора устройства стандартного вывода
    COORD position1 = { 1, 1 };
    COORD position2 = { 18, 1 };
    COORD position3 = { 37, 1 };
    COORD position4 = { 54, 1 };
    COORD position = { 10, 1 };
    COORD standpos = { 0, 0 };

    DrawMenu(hConsole, standpos);

    Fill();
    SetConsoleCursorPosition(hConsole, position1);
    cout << menutext[0];
    SetConsoleCursorPosition(hConsole, position);

    bool exit = false;
    char ch;
    while (!exit) {
        ch = _getch();
        switch (ch) {
        case UP: {
            if (position.Y != 0) {
                position.Y--; SetConsoleCursorPosition(hConsole, position);
            }
            break;
        }
        case DOWN: {
            //if (IsMenuWork == true) {
                position.Y++; SetConsoleCursorPosition(hConsole, position);
            //}
            break;
        }
        case LEFT: {
            if (position.X > 10) {
                position.X = position.X - 15;
                SetConsoleCursorPosition(hConsole, position);

                DrawMenu(hConsole, standpos);

                /*
                Clear();
                SetConsoleCursorPosition(hConsole, standpos);
                for (int i = 0; i < 3; i++) {
                    cout << menu[i] << "\n";
                }
                Fill();
                */
                
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
            break;
        }
        case RIGHT: {
           if (position.X < 46) {
               position.X = position.X + 15;
               SetConsoleCursorPosition(hConsole, position);

               DrawMenu(hConsole, standpos);
               /*
               Clear();
               SetConsoleCursorPosition(hConsole, standpos);
               for (int i = 0; i < 3; i++) {
                   cout << menu[i] << "\n";
               }
               Fill();
               */
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
            break;
        }
        case ENTER: {

            if (position.X == 55 && position.Y == 1) {
                Clear();
                return 0;
            }
            break;
        }
        
        default:
            
            break;
        }
    }
    return 0;
}