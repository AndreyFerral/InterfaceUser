#include <iostream>
#include <windows.h>
using namespace std;

void func(COORD &position, HANDLE hConsole) {
	position.Y++; SetConsoleCursorPosition(hConsole, position);
}

int main() {
	setlocale(LC_ALL, "rus");

	//putchar(' ');		// Перемещение каретки вправо на одну позицию
	//putchar('\b');		// Перемещение каретки влево на одну позицию
	//putchar('\n');		// Перемещение каретки на новую строку
	
	COORD position;										// Объявление необходимой структуры
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// Получение дескриптора устройства стандартного вывода
	position.X = 50;									// Установка координаты X
	position.Y = 10;									// Установка координаты Y
	
	SetConsoleCursorPosition(hConsole, position); cout << "-------------" << endl;
	func(position, hConsole); cout << "|  Курсор   |" << endl;
	func(position, hConsole); cout << "-------------" << endl;
	func(position, hConsole); cout << "|  Палитра  |" << endl;
	func(position, hConsole); cout << "-------------" << endl;
	func(position, hConsole); cout << "|  Эхо      |" << endl;
	func(position, hConsole); cout << "-------------" << endl;
	func(position, hConsole); cout << "|  Выход    |" << endl;
	func(position, hConsole); cout << "-------------" << endl;
	
	return 0;
}