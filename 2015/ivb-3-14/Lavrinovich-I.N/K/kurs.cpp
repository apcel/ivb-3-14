#pragma warning(disable : 4996)
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <Windows.h>
#include <ctime>
#include <process.h>

using namespace std;
void x_y(int xp, int yp)
{
	COORD sc;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	sc.X = xp; sc.Y = yp;
	SetConsoleCursorPosition(hOuput, sc);
}

int position[][2] = { { 3, 2 }, { 9, 2 }, { 15, 2 }, { 21, 2 },
{ 3, 5 }, { 9, 5 }, { 15, 5 }, { 21, 5 },
{ 3, 8 }, { 9, 8 }, { 15, 8 }, { 21, 8 },
{ 3, 11 }, { 9, 11 }, { 15, 11 }, { 21, 11 } };
bool Game1 = true;
int steps = 0;
CRITICAL_SECTION cs;
void print_field()
{
	cout << " _______________________" << endl;
	cout << "|     |     |     |     |" << endl;
	cout << "|     |     |     |     |" << endl;
	cout << "|_____|_____|_____|_____|" << endl;
	cout << "|     |     |     |     |" << endl;
	cout << "|     |     |     |     |" << endl;
	cout << "|_____|_____|_____|_____|" << endl;
	cout << "|     |     |     |     |" << endl;
	cout << "|     |     |     |     |" << endl;
	cout << "|_____|_____|_____|_____|" << endl;
	cout << "|     |     |     |     |" << endl;
	cout << "|     |     |     |     |" << endl;
	cout << "|_____|_____|_____|_____|" << endl;
	cout << "\n\nКоличество ходов: 0 ";
}

void generate(int *desk)
{
	int i, j;
	srand(time(0));
	for (i = 1; i <= 15; i++)
	while (1) {
		j = rand() % 15;
		if (!desk[j]){ desk[j] = i; break; }
	}
	desk[16] = 0;
}

void fill_field(int *desk)
{
	for (int i = 0; i<15; i++) {
		x_y(position[i][0], position[i][1]);
		printf("%i", desk[i]);
	}
}

void zamena(int *desk, int a, int b)
{
	desk[b] ^= desk[a] ^= desk[b] ^= desk[a];
	EnterCriticalSection(&cs);
	x_y(position[b][0], position[b][1]);
	printf("   ");
	x_y(position[a][0], position[a][1]);
	printf("   ");
	x_y(position[a][0], position[a][1]);
	printf("%i ", desk[a]);
	LeaveCriticalSection(&cs);

}

bool check_win(int *desk)
{
	for (int i = 1; i<16; i++)
	if (desk[i - 1] != i) return false;

	return true;
}

bool move(int *desk, int &emptypos, char c)
{
	switch (c) {
	case 80: { if (emptypos > 3)     { zamena(desk, emptypos, emptypos - 4); emptypos -= 4; steps++; } break; } // down
	case 72: { if (emptypos < 12)    { zamena(desk, emptypos, emptypos + 4); emptypos += 4; steps++; } break; } // up
	case 77: { if ((emptypos % 4))     { zamena(desk, emptypos, emptypos - 1); emptypos--;  steps++; } break; } // right
	case 75: { if (((emptypos - 3) % 4)) { zamena(desk, emptypos, emptypos + 1); emptypos++;  steps++; } break; } // left
	case 27:    return false;
	}
	return true;
}

void fgame(void *ds)
{
	Game1 = true;
	int *desk = (int *)ds;
	int emptypos = 15;

	while (move(desk, emptypos, getch())) {
		EnterCriticalSection(&cs);
		x_y(18, 15);
		printf("%i", steps);
		LeaveCriticalSection(&cs);
		if (check_win(desk)) {
			x_y(0, 19);
			printf("Вы победили!!!\n");
			break;
		}
	}
	Game1 = false;
}

void m_str()
{

	cout << "                  #########################################\n";
	cout << "                  ############### ПЯТНАШКИ ################\n";
	cout << "                  #########################################\n";
	cout << "                  ############ 1. Начать игру  ############\n";
	cout << "                  ############  2. Цели игры   ############\n";
	cout << "                  ############    3. Выход     ############\n";
	cout << "                  #########################################\n";
	cout << "                  #########################################\n\n";
	cout << "Выберите соответствующей меню: ";

}

int Game()
{
	int field[16] = { 0 };

	system("cls");

	print_field();
	generate(field);
	fill_field(field);

	InitializeCriticalSection(&cs);
	_beginthread(fgame, 0, (void *)(field));

	while (Game1);

	x_y(0, 22);
	printf("Нажмите любую клавишу для выхода");
	getch();
	return 0;
}

void menu()
{
int choice_sw;
		
		cout << "Цель игры - упорядочить размещение чисел в коробке, разместив их по возрастанию слева направо и сверху вниз.\n";
		cout << "Начинается размещение с костяшки с номером 1 в левом верхнем углу и заканчивая  пустым местом в правом нижнем углу коробки.\n"; 
		cout << "Управление осуществляется стрелками на клавиатуре \n\n";
		cout << "\n\n		1.Начать игру \n		2.Выход\n";
		cout << "";
		cin >> choice_sw;
		if(choice_sw == 1) Game();
		if(choice_sw == 2) exit(0);
		else {
			system("cls");
			cout << "Ошибка! Вы можете вводить только 1,2\n\n";
			menu();
		}
}

int main()
{
	setlocale(LC_ALL, "rus");

	int choice;

	m_str();

	cin >> choice;

	if(choice == 1){
		system ("cls");
		Game();
	}
	if (choice == 2) {
		system("cls");
		menu();
		
	}
	if (choice == 3) exit(0);
	else {
		system ("cls");
		cout << "Ошибка! Вы можете вводить только 1,2,3\n";
		main();
	}
		
	
}
