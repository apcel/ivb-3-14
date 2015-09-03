#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

#define MAP_SIZE 8
#define MAP_PLAYER_LINES 3

#define TABLE_TOP_LEFT		(char)218
#define TABLE_TOP_MIDLE		(char)194
#define TABLE_TOP_RIGHT		(char)191
#define TABLE_MIDLE_LEFT	(char)195
#define TABLE_MIDLE_MIDLE	(char)197
#define TABLE_MIDLE_RIGHT	(char)180
#define TABLE_BOTTOM_LEFT	(char)192
#define TABLE_BOTTOM_MIDLE	(char)193
#define TABLE_BOTTOM_RIGHT	(char)217
#define TABLE_VRTICAL		(char)179
#define TABLE_HORIZONTAL	(char)196
#define TABLE_FULL			(char)219

#define TABLE_LINE	TABLE_HORIZONTAL<<TABLE_HORIZONTAL<<TABLE_HORIZONTAL

char map[MAP_SIZE][MAP_SIZE];
int cursor[] = { MAP_SIZE / 2, MAP_SIZE / 2 };
int state[] = { 0, 0 };
char marker[] = { '0', 'O' };
bool step = true;
bool isMove = false;
int movePosition[] = { 0, 0 };
int win_state = -1;
bool enrage = false;

int
clamp(int value, int min, int max)
{
	return value<min ? min : value>max ? max : value;
}

void
swap(char* a, char* b)
{
	char c = *a;
	*a = *b;
	*b = c;
}

bool
isValidKill(int x, int y)
{
	if (x >= 0 && y >= 0 && x < MAP_SIZE  && y < MAP_SIZE && map[x][y] == ' ') {

		int a = x - movePosition[0];
		int b = y - movePosition[1];
		if (abs(a) == 2 && abs(b) == 2) {
			a = movePosition[0] + a*0.5;
			b = movePosition[1] + b*0.5;
			return map[a][b] == marker[!step];
		}
	}
	return false;
}

bool
isValidMove(int x, int y)
{
	if (enrage)
		return false;

	int a = x - movePosition[0];
	int b = abs(y - movePosition[1]);

	if (a == 0 && a == b)
		return true;

	if (b == 1 && ((step && a == 1) || !step && a == -1))
			return map[x][y] == ' ';
	return false;
}

char
printPoint(int x, int y)
{
	return (isMove && !isValidMove(x, y) && !isValidKill(x, y)) ? 'X' : map[x][y];
}

char
printBorder(int x, int y, bool left)
{
	return (cursor[0] == x && cursor[1] == y) ? left ? '[' : ']' : ' ';
}

void
printInfo(int i)
{
	switch (i)
	{
	case 0:
		cout << "\t'" << marker[1] << "' - white, '" << marker[0] << "' - black.";
		break;
	case 1:
		cout << "\tStep:\tScore:";
		break;
	case 2:
		cout << "\t ";
		if (step)
			cout << "white";
		else
			cout << "black";
		cout << "\t " << state[1] << ':' << state[0];
		break;
	case 6:
		cout << "\tUse arrow keys to move the pointer.";
		break;
	case 7:
		if (isMove)
			cout << " Press 'Enter' clear point else press 'Esc' to exit.";
		else
			cout << "\t\tPress 'Enter' to select.";
		break;
	}
}

void
printWin(bool player)
{
	cout << "\n\n\t\t\t";
	if (player)
		cout << "White";
	else
		cout << "Black";
	cout << " player is win!" << endl;
}

void
echo()
{
	if (state[!step] == win_state)
		printWin(!step);
	else {
		for (int x = 0; x < MAP_SIZE; x++) {
			if (x != 0) {
				cout << TABLE_MIDLE_LEFT;
				for (int y = 1; y < MAP_SIZE; y++)
					cout << TABLE_LINE << TABLE_MIDLE_MIDLE;
				cout << TABLE_LINE << TABLE_MIDLE_RIGHT << endl;

			} else {
				cout << TABLE_TOP_LEFT;
				for (int y = 1; y < MAP_SIZE; y++)
					cout << TABLE_LINE << TABLE_TOP_MIDLE;
				cout << TABLE_LINE << TABLE_TOP_RIGHT << endl;
			}
			for (int y = 0; y < MAP_SIZE; y++)
				cout << TABLE_VRTICAL << printBorder(x, y, true) << printPoint(x, y) << printBorder(x, y, false);
			cout << TABLE_VRTICAL;
			printInfo(x);
			cout << endl;
		}

		cout << TABLE_BOTTOM_LEFT;
		for (int y = 1; y < MAP_SIZE; y++)
			cout << TABLE_LINE << TABLE_BOTTOM_MIDLE;
		cout << TABLE_LINE << TABLE_BOTTOM_RIGHT << endl;
	}
}

void
bindPlayers(bool black)
{
	win_state = 0;
	int x, end;
	char c;

	if (black) {
		x = 0;
		end = MAP_PLAYER_LINES;
	} else {
		x = MAP_SIZE - MAP_PLAYER_LINES;
		end = MAP_SIZE;
	}
	c = marker[black];


	for (int i = black; x < end; x++) {
		for (int y = 0; y < MAP_SIZE; y++, i++) {
			if (i % 2) {
				map[x][y] = c;
				win_state++;
			}
		}
		i--;
	}
}

int
main()
{
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++)
			map[x][y] = ' ';
	}

	bool needUpdate = true;
	bindPlayers(true);
	bindPlayers(false);

	int c = 0;
	while (true)
	{
		if (needUpdate) {
			system("cls");
			echo();
		}
		c = getch();
		if (c == 224) c = getch();

		needUpdate = true;
		switch (c)
		{
		case 27:
			if (isMove)
				isMove = false;
			else
				return EXIT_SUCCESS;
			break;
		case 72:
			cursor[0]--;
			break;
		case 75:
			cursor[1]--;
			break;
		case 77:
			cursor[1]++;
			break;
		case 80:
			cursor[0]++;
			break;
		case 13:
			if (isMove) {
				if (!enrage && isValidMove(cursor[0], cursor[1])) {
					swap(&map[cursor[0]][cursor[1]], &map[movePosition[0]][movePosition[1]]);
					step = !step;
					isMove = false;
				} else if (isValidKill(cursor[0], cursor[1])) {
					swap(&map[cursor[0]][cursor[1]], &map[movePosition[0]][movePosition[1]]);
					int a = movePosition[0] + (cursor[0] - movePosition[0])*0.5;
					int b = movePosition[1] + (cursor[1] - movePosition[1])*0.5;
					map[a][b] = ' ';
					state[step]++;
				 	movePosition[0] = cursor[0];
				 	movePosition[1] = cursor[1];
					if (!isValidKill(cursor[1] + 2, cursor[1] + 2) &&
						!isValidKill(cursor[1] - 2, cursor[1] + 2) &&
						!isValidKill(cursor[1] + 2, cursor[1] - 2) &&
						!isValidKill(cursor[1] - 2, cursor[1] - 2)) {

						enrage = false;
						isMove = false;
						step = !step;
					} else
						enrage = true;
				} else
					needUpdate = false;
			} else {
				if (map[cursor[0]][cursor[1]] == marker[step]) {
					isMove = true;
					movePosition[0] = cursor[0];
					movePosition[1] = cursor[1];
				} else
					needUpdate = false;
			}
			break;
		default:
			needUpdate = false;
			break;
		}
		cursor[0] = clamp(cursor[0], 0, MAP_SIZE - 1);
		cursor[1] = clamp(cursor[1], 0, MAP_SIZE - 1);
	}
	return EXIT_SUCCESS;
}
