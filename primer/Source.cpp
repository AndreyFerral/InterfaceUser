#include <iostream>
#include <windows.h>
#include <conio.h>
using std::cout;

int main()
{
    setlocale(LC_ALL, "rus");
    bool exit = false;
    int ch;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { 0, 0 };
    cout << (char)16 << "������� ���� \n ������������� \n �������";
    SetConsoleCursorPosition(hConsole, position);

   // cout << position.Y;

    while (!exit)
    {
        ch = _getch();
        switch (ch) {
        case 224: {
            switch (_getch()) {
            case 72: {// ������ ������� �����
                if (position.Y != 0) {
                    cout << " ";
                    position.Y--;
                    SetConsoleCursorPosition(hConsole, position);
                    cout << (char)16;
                    SetConsoleCursorPosition(hConsole, position);
                }
                break;
            }
            case 80: {// ������ ������� ����
                cout << " "; position.Y++;
                SetConsoleCursorPosition(hConsole, position);
                cout << (char)16;
                SetConsoleCursorPosition(hConsole, position);
                break;
            }

            case 75: { // ������ ������� �����
                if (position.X != 0) {
                    cout << " "; position.X--;
                    SetConsoleCursorPosition(hConsole, position);
                    cout << (char)16;
                    SetConsoleCursorPosition(hConsole, position);
                }
                break;
            }
            case 77: { // ������ ������� ������
                cout << " "; position.X++;
                SetConsoleCursorPosition(hConsole, position);
                cout << (char)16;
                SetConsoleCursorPosition(hConsole, position);
                break;
            }
            default:
                break;
            }
            break;
        }
        case 27: {
            exit = true;
            break;
        }
        default:
            break;
        }
    }
    return 0;
}