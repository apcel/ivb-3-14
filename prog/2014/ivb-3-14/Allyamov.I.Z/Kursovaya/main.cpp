#include <iostream>
#include <conio.h>

#define MAP_SIZE 10
#define SHIP_LIMIT { 4, 3, 2, 1 }
#define MAP_PLAYER			0
#define MAP_PLAYER2			1
#define MAP_TEMP			2

#define KEY_BACKSPACE	8
#define KEY_ENTER		13
#define KEY_UP			72
#define KEY_LEFT		75
#define KEY_RIGHT		77
#define KEY_DOWN		80

int player = MAP_PLAYER;
int player2 = MAP_PLAYER2;
int ship_limits[] = SHIP_LIMIT;
int total_ship = 1;
bool game = true;
bool build = true;
bool build2 = false;
int cursor[2];
char map[3][MAP_SIZE][MAP_SIZE];

void
swap()
{
	system("cls");
	std::cout << "\n\n\t\tChange player, press key to switch.";
	_getch();
	system("cls");

	int t = player;
	player = player2;
	player2 = t;
}

void
print()
{
	if (player == MAP_PLAYER)
		std::cout << "First player." << std::endl;
	else
		std::cout << "Second player." << std::endl;

	if (build)
		std::cout << "Press key 'Enter' to put ship.\nPress key 'Backspace' to delete.\n" << std::endl;
	std::cout << ' ';

	for (int n = 0; n < 2; n++) {
		for (char i = 0; i < MAP_SIZE; i++)
			std::cout << ' ' << (char)('A' + i);
		std::cout << "\t ";
	}
	std::cout << std::endl;

	char c;
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int n = 0; n < 2; n++) {
			std::cout << x;
			for (int y = 0; y < MAP_SIZE; y++) {
				if (n) {
					c = !build && cursor[0] == y && cursor[1] == x ? '>' : ' ';
					std::cout << c;
					if (map[player2][y][x] == '#' || map[player2][y][x] == ' ')
						std::cout << '?';
					else
						std::cout << map[player2][y][x];
				}
				else {
					c = build && cursor[0] == y && cursor[1] == x ? '>' : ' ';
					std::cout << c << map[player][y][x];
				}
			}
			std::cout << "\t";
		}
		std::cout << std::endl;
	}
}

void
clear(int index)
{
	for (int x = 0; x < MAP_SIZE; x++){
		for (int y = 0; y < MAP_SIZE; y++){
			map[index][x][y] = ' ';
		}
	}
}

bool
isValid()
{
	int len[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < MAP_SIZE; i++) {
		if (map[player][i][0] == '#')
			len[0]++;
		else
			len[0] = 0;

		if (map[player][i][MAP_SIZE - 1] == '#')
			len[1]++;
		else
			len[1] = 0;

		if (map[player][0][i] == '#')
			len[2]++;
		else
			len[2] = 0;

		if (map[player][MAP_SIZE - 1][i] == '#')
			len[3]++;
		else
			len[3] = 0;

		if (len[0] > 4 || len[1] > 4 || len[2] > 4 || len[3] > 4)
			return false;
	}

	for (int x = 1; x < MAP_SIZE - 1; x++) {
		for (int y = 1; y < MAP_SIZE - 1; y++) {
			if (map[player][y][x] == '#'){
				int countX = 1;
				int countY = 1;

				if (map[player][y + 1][x - 1] == '#' ||
					map[player][y - 1][x - 1] == '#' ||
					map[player][y - 1][x + 1] == '#' ||
					map[player][y + 1][x - 1] == '#')
					return false;

				int ix = x - 1;
				while (ix >= 0 && map[player][y][ix--] == '#')
					countX++;
				ix = x + 1;
				while (ix < MAP_SIZE && map[player][y][ix++] == '#')
					countX++;

				int iy = y - 1;
				while (iy >= 0 && map[player][iy--][x] == '#')
					countY++;
				iy = y + 1;
				while (iy < MAP_SIZE && map[player][iy++][x] == '#')
					countY++;

				if (countX != 1 && countY != 1)
					return false;

				if (countX > 4 || countY > 4)
					return false;
			}
		}
	}
	return true;
}

void
copy(int index)
{
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			map[MAP_TEMP][x][y] = map[index][x][y];
		}
	}
}

bool
isValidShipsCount()
{
	copy(player);
	int limit[] = SHIP_LIMIT;

	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			if (map[MAP_TEMP][y][x] == '#') {
				map[MAP_TEMP][y][x] = '+';
				int countX = 0;
				int countY = 0;

				int ix;
				int iy;

				ix = x - 1;
				while (ix >= 0 && map[MAP_TEMP][y][ix] == '#') {
					map[MAP_TEMP][y][ix] = '+';
					countX++;
					ix--;
				}

				ix = x + 1;
				while (ix < MAP_SIZE && map[MAP_TEMP][y][ix] == '#') {
					map[MAP_TEMP][y][ix] = '+';
					countX++;
					ix++;
				}

				iy = y - 1;
				while (iy >= 0 && map[MAP_TEMP][iy][x] == '#') {
					map[MAP_TEMP][iy][x] = '+';
					countY++;
					iy--;
				}

				iy = y + 1;
				while (iy < MAP_SIZE && map[MAP_TEMP][iy][x] == '#') {
					map[MAP_TEMP][iy][x] = '+';
					countY++;
					iy++;
				}

				if (countY)
					countX = countY;

				if (limit[countX] == 0)
					return false;

				limit[countX]--;
			}
		}
	}
	return true;
}

bool
idVictory()
{
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			if (map[player2][y][x] == '#')
				return false;
		}
	}
	return true;
}

void
reset_total_ship()
{
	total_ship = 0;
	for (int i = 0; i < 4; i++)
		total_ship += ship_limits[i] * (i + 1);
}

void
reset()
{
	clear(player);
	reset_total_ship();
	build = true;
	cursor[0] = MAP_SIZE / 2;
	cursor[1] = cursor[0];
}

void
fire()
{
	map[player2][cursor[0]][cursor[1]] = '+';

	int y = cursor[0];
	int x = cursor[1];

	while (x - 1 >= 0 && (map[player2][y][x - 1] == '#' || map[player2][y][x - 1] == '+'))
		x--;
	while (y - 1 >= 0 && (map[player2][y - 1][x] == '#' || map[player2][y - 1][x] == '+'))
		y--;

	if (map[player2][y][x] == '#')
		return;

	int iy = y;
	int ix = x;

	while (x + 1 < MAP_SIZE && (map[player2][y][x + 1] == '#' || map[player2][y][x + 1] == '+')) {
		x++;
		if (map[player2][y][x] == '#')
			return;
	}

	while (y + 1 < MAP_SIZE && (map[player2][y + 1][x] == '#' || map[player2][y + 1][x] == '+')) {
		y++;
		if (map[player2][y][x] == '#')
			return;
	}

	for (; iy <= y; iy++) {
		map[player2][iy][x] = 'X';
	}
	for (; ix <= x; ix++) {
		map[player2][y][ix] = 'X';
	}
}

int
main()
{
	reset();
	clear(player2);

	while (game){
		system("cls");
		print();

		int c;
		c = _getch();
		if (c == 224)
			c = _getch();

		switch (c) {
		case KEY_BACKSPACE:
			if (build) {
				if (map[player][cursor[0]][cursor[1]] == '#')
					total_ship++;
				map[player][cursor[0]][cursor[1]] = ' ';
			}
			break;
		case KEY_ENTER:
			if (build) {
				map[player][cursor[0]][cursor[1]] = '#';
				if (isValid()) {
					total_ship--;
					if (!total_ship) {
						if (!isValidShipsCount())
						{
							std::cout << "There is a wrong number of ships!\n\tTry again." << std::endl;
							system("pause");
							reset();
						}
						else {
							if (build2)
								build = false;
							else {
								reset_total_ship();
								build2 = true;
								cursor[0] = MAP_SIZE / 2;
								cursor[1] = cursor[0];
							}
							swap();
						}
					}
				}
				else
					map[player][cursor[0]][cursor[1]] = ' ';
			}
			else {
				c = map[player2][cursor[0]][cursor[1]];
				if (c != '-' && c != '+' && c != 'X') {
					if (c == ' ') {
						map[player2][cursor[0]][cursor[1]] = '-';
						swap();
					}
					else
						fire();

					if (idVictory())
						game = false;
				}
			}
			break;
		case KEY_UP:
			cursor[1]--;
			if (cursor[1] < 0)
				cursor[1] = 0;
			break;
		case KEY_RIGHT:
			cursor[0]++;
			if (cursor[0] == MAP_SIZE)
				cursor[0] = MAP_SIZE - 1;
			break;
		case KEY_LEFT:
			cursor[0]--;
			if (cursor[0] < 0)
				cursor[0] = 0;
			break;
		case KEY_DOWN:
			cursor[1]++;
			if (cursor[1] == MAP_SIZE)
				cursor[1] = MAP_SIZE - 1;
			break;
		}
	}

	if (player == MAP_PLAYER)
		std::cout << "The first player won!" << std::endl << std::endl;
	else
		std::cout << "The second player won!" << std::endl << std::endl;

	system("pause");
	return 0;
}
