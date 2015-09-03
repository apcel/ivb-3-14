#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

using std::istream;
using std::ostream;
using std::cout;
using std::cin;

class Item
{
public:
	int index, cost, mass;

	bool operator < (const Item b)
	{
		return cost < b.cost;
	}

	bool operator > (const Item b)
	{
		return cost > b.cost;
	}

private:
	friend istream & operator >> (istream &fs, Item &item);
	friend ostream & operator << (ostream &fs, const Item &item);
};

istream & 
operator >> (istream &fs, Item &item)
{
	fs >> item.index;
	fs >> item.cost;
	fs >> item.mass;
	return fs;
}

ostream & 
operator << (ostream &fs, const Item &item)
{
	fs << item.index << '\t';
	fs << item.cost << '\t';
	fs << item.mass << std::endl;
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
	setlocale(0, "Russian");

	LoadArray();
	PrintArray();

	printf("Сортировка по цене\n");
	ShortArray();

	PrintArray();
	printf("Поиск тавара, введите индекс:");
	int h = 0;
	cin >> h;

	Item * find = Find(h);
	if (find != nullptr)
		cout << *find;
	else
		cout << "Ничего не найдено :(\n";

	SaveArray();

	system("pause");
	retutn 0;
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
	printf("База загруженна, выделенно %i байт (по %i байт на элемент)\n", s * BaseLen, s);
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
Find(int index)
{
	for (int i = 0; i < BaseLen; i++)
	if (Base[i].index == index)
		return &Base[i];

	return nullptr;
}
