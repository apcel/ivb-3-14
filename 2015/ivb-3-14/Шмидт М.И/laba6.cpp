/*
	* Лаба №6
	* ИВБ-3-14
	* Шмидт Максим
	* 23 вариант
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

	int h = 0;
	fs >> h;
	for (int i = 0; i<h; i++)
	{
		Date* item = new Date();
		fs >> item->day >> item->month >> item->year;
		base.push_back(item);
	}
	fs.close();

	std::cout << "Выделенно " << memory << " байт" << std::endl;
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
		for (int j = 0; j < base.size() - 1 - i; j++) {
			if (base[j]->month > base[j + 1]->month) {
				auto temp = base[j];
				base[j] = base[j + 1];
				base[j + 1] = temp;
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
			std::cout << "Укажите имя файла:" << std::endl;
			std::cin >> cmd;

			system("cls");
			load(cmd);
			system("pause");
		}
		else if (base.size()) {
			if (cmd == "save") {
				std::cout << "Укажите имя файла:" << std::endl;
				std::cin >> cmd;

				save(cmd);
				system("cls");
				std::cout << "Сохранено." << std::endl;
				system("pause");
			} else if (cmd == "find") {
				std::cout << "Укажите месяц:" << std::endl;
				std::cin >> cmd;

				system("cls");
				std::cout << "Результаты поиска:" << std::endl;
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
			std::cout << "Для загрузки базы используйте команду load." << std::endl;
			system("pause");
		}
	}

	system("pause");
	clear();

	return EXIT_SUCCESS;
}
