#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

void Enter();
void Igra(string *a);
bool Take1(int m, int lenl, string *a);
void Take2(int m);

string sl0 = "parallelepiped";
string sl1 = "matematika";
string sl2 = "sinus";
string sl3 = "revolucia";
string sl4 = "prilagatelnoe";
string sl5 = "identifikacia";
string sl6 = "hromirovanie";
string sl7 = "otkritie";
string sl8 = "antilopa";
string sl9 = "vzrivchatka";

string *mass[10];

char pic_mass[30];
int mas1[5][4] = { { 1, 1, 1, 1 }, { 1, 256, 2, 256 }, { 1, 4, 3, 5 }, { 1, 256, 6, 256 }, { 1, 7, 256, 8 } }; 
char mas2[5][4] = { { '|', '-', 'T', '-' }, { '|', ' ', 'o', ' ' }, { '|', '-', '|', '-' }, { '|', ' ', '^', ' ' }, { '|', '/', ' ', '\\' } };

int main()
{
	setlocale(LC_CTYPE, "");

	mass[0] = &sl0;
	mass[1] = &sl1;
	mass[2] = &sl2;
	mass[3] = &sl3;
	mass[4] = &sl4;
	mass[5] = &sl5;
	mass[6] = &sl6;
	mass[7] = &sl7;
	mass[8] = &sl8;
	mass[9] = &sl9;

	for (int i = 0; i < 30; i++)
	{
		pic_mass[i] = '*';
	}

	Enter();

	cin.sync();
	cin.clear();
	cin.get();

	return 0;
}

void Enter()
{
	system("cls");
	cout << "Начать игру" << endl
		<< "1 - Да.\t\t" << "2 - Нет." << endl;
	int i;
	cin >> i;

	if (i == 1) {
		srand(time(NULL));
		Igra(mass[rand() % 9]);
	}

	return;
}

void Igra(string *a)
{
	system("cls");

	int i = 0;
	int j = 0;
	int oshibka = 0;
	bool verno = false;
	int lenl = a->size();
	char litera;

	while (i <= 34)
	{
		while (j != lenl)
		{
			cout << "*";
			j++;
		}

		cout << endl << endl << "Назовите букву:" << endl;
		cin >> litera;
		
		for (int k = 0; k < lenl; k++)
		{
			if ((*a)[k] == litera) 
			{
				verno = true;
				if (Take1(k, lenl, a)) 
				{     
					cout << endl << "Вы выиграли!";

					Enter();
					return;
				}
			}
		}
		if (verno == false) 
		{

			oshibka++;
			Take2(oshibka);

			if (oshibka == 8) 
			{

				cout << endl << "Вы проиграли!" << endl
					<< "Правильный ответ: " << (*a) << endl;

				cin.sync();
				cin.clear();
				cin.get();

				Enter();
				return;
			}
		}

		i++;
		verno = false;
	}

}

bool Take1(int m, int lenl, string *a)
{
	system("cls");

	pic_mass[m] = (*a)[m];
	for (int i = 0; i < lenl; i++)
	{
		cout << pic_mass[i];
	}

	for (int j = 0; j < lenl; j++)
	{
		if (pic_mass[j] == '*')
			return false;
	}
	return true;
};

void Take2(int m)
{
	system("cls");

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
			if (mas1[i][j] <= m)
				cout << mas2[i][j];
			else
				cout << " ";
		cout << endl;
	}
}
