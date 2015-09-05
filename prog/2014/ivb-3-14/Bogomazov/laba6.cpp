#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

/* Лаб. работа 6
 Вариант 6
 ИВБ-3-14
 Богомазов Степан */ 
 
using std::istream;
using std::ostream;
using std::cout;
using std::cin;

class Item
{
public:
        int i, c, m;

	bool operator < (const Item a)
	{
		return c < a.c;
	}

	bool operator >(const Item a)
	{
		return c > a.c;
	}

private:
	friend istream & operator >> (istream &fs, Item &item);
	friend ostream & operator << (ostream &fs, const Item &item);
};

istream &
operator >> (istream &fs, Item &item)
{
	fs >> item.i;
	fs >> item.c;
	fs >> item.m;
	return fs;
}

ostream &
operator << (ostream &fs, const Item &item)
{
        fs << item.i << '\t';
	fs << item.c << '\t';
	fs << item.m << std::endl;
	return fs;
}


Item * Base = nullptr;
int BaseLen = 0;

void LoadArray();
void SaveArray();
void ShortArray();
void PrintArray();
Item* Find(int index);


int
main()
{
        setlocale(LC_ALL, "rus");

	LoadArray();
	PrintArray();

	printf("Сортировка по цене\n");
	ShortArray();

	PrintArray();
	printf("Поиск тавара:");
	int k = 0;
	cin >> k;

	Item * find = Find(k);
	if (find != nullptr)
		cout << *find;
	else
		cout << "Не найдено\n";

	SaveArray();

	system("pause");
	return 0;
}


void
LoadArray()
{
	if (Base != nullptr) {
	        delete[] Base;
		Base = nullptr;
	}

	std::ifstream fs("base.txt");
	fs >> BaseLen;

	Base = new Item[BaseLen];
	for (int i = 0; i < BaseLen; i++)
	fs >> Base[i];

	fs.close();

	int s = sizeof(Item);
	printf("Dыделенно %i байт\n", s * BaseLen, s);
}

void
SaveArray()
{

	std::ofstream fs("base.txt");
	fs << BaseLen << '\n';

	for (int i = 0; i < BaseLen; i++)
		fs << Base[i];

	fs.close();
}

void
ShortArray()
{
	for (int j = 1; j <= (BaseLen - 1); j++) {
		for (int i = 0; i < BaseLen - j; i++) {
			if (Base[i] < Base[i + 1]) {
				Item s = Base[i + 1];
				Base[i + 1] = Base[i];
				Base[i] = s;
			}
		}
	}
}

void
PrintArray()
{
	cout << "Индекс\tЦена\tМасса\n";
	for (int i = 0; i < BaseLen; i++)
		 cout << Base[i];
}

Item*
Find(int i)
{
	for (int i = 0; i < BaseLen; i++)
	if (Base[i].i == i)
		return &Base[i];

	        return nullptr;
}
