/*
* Лабораторная 6
* ИВБ-3-14
* Фоломкин Антон
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

int memory = 0;

struct Date {
	int day, month, year;

	void* operator new(size_t size)
	{
		memory += size;
		return malloc(size);
	}
	void operator delete(void* id)
	{
		memory -= sizeof(Date);
		free(id);
	}
};

std::vector<Date*> base;

void
clear()
{
	for (int i = 0; i < base.size(); i++)
		delete base[i];
	base.clear();
}

void
load(std::string patch)
{
	clear();

	std::ifstream fs(patch.c_str());

	int k = 0;
	fs >> k;
	for (int i = 0; i<k; i++)
	{
		Date* item = new Date();
		fs >> item->day >> item->month >> item->year;
		base.push_back(item);
	}
	fs.close();

	std::cout << "Выделено " << memory << " байт" << std::endl;
}

void
print()
{
	for (auto x = base.begin(); x < base.end(); x++)
		std::cout << (*x)->day << ' ' << (*x)->month << ' ' << (*x)->year << std::endl;
	std::cout << std::endl;
}

void
sort()
{
	for (int i = 0; i < base.size() - 1; i++) {
		for (int l = 0; l < base.size() - 1 - i; l++) {
			if (base[l]->month > base[l + 1]->month) {
				auto temp = base[l];
				base[l] = base[l + 1];
				base[l + 1] = temp;
			}
		}
	}
}

void
find(int d)
{
	for (auto x = base.begin(); x < base.end(); x++) {
		if ((*x)->month == d) {
			std::cout << (*x)->day << ' ' << (*x)->month << ' ' << (*x)->year << std::endl;
		}
	}
}

void
save(std::string patch)
{
	std::ofstream fs(patch.c_str());

	fs << base.size();
	fs << std::endl;

	for (auto x = base.begin(); x < base.end(); x++)
		fs << (*x)->day << ' ' << (*x)->month << ' ' << (*x)->year << std::endl;

	fs.close();
}

int
main()
{
	setlocale(0, "Russian");

	while (true)
	{
		system("cls");
		print();

		std::cout << "Доступные команды: load, save, sort, find, exit" << std::endl;
		std::string cmd;
		std::cin >> cmd;

		if (cmd == "load") {
			std::cout << "Укажите название файла:" << std::endl;
			std::cin >> cmd;

			system("cls");
			load(cmd);
			system("pause");
		} else if (base.size()) {
			if (cmd == "save") {
				std::cout << "Укажите название файла:" << std::endl;
				std::cin >> cmd;

				save(cmd);
				system("cls");
				std::cout << "Сохранено." << std::endl;
				system("pause");
			} else if (cmd == "find") {
				std::cout << "Укажите месяц:" << std::endl;
				std::cin >> cmd;

				system("cls");
				std::cout << "Вот результаты поиска:" << std::endl;
				find(atoi(cmd.c_str()));
				system("pause");
			} else if (cmd == "sort") {
				sort();
			} else if (cmd == "exit") {
				break;
			} else {
				system("cls");
				std::cout << "О_0." << std::endl;
				system("pause");
			}
		} else {
			system("cls");
			std::cout << "Для загрузки базы используйте команду под названием LOAD" << std::endl;
			system("pause");
		}
	}

	system("pause");
	clear();

	return EXIT_SUCCESS;
}
