#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int memory_count = 0;
struct Object {
	int value1, value2, value3;
	void* operator new(size_t size)
	{
		memory_count += size;
		return ::operator new(size);
	}
};

std::vector<Object*> table;

void Load(std::string file);
void Save(std::string file);
void Sort();
void Print(std::vector<Object*> list);
std::vector<Object*> Find(int index);

int main()
{
	setlocale(0, "Russian");

	Load("base.txt");
	Print(table);

	printf("Сортировка по возрастанию:\n");
	Sort();
	Print(table);

	printf("Поиск по первому стобцу:\n");

	int h = 0;
	std::cin >> h;
	auto find_result = Find(h);

	if (!find_result.empty())
		Print(find_result);
	else
		std::cout << "Ничего не найдено.\n";

	Save("base1.txt");

	for (auto x = table.begin(); x < table.end(); x++)
		delete *x;
	table.clear();
	system("pause");
	return 0;
}


void
Save(std::string file)
{
	std::ofstream fs(file);

	fs << table.size() << '\n';
	for each (Object* var in table) {
		fs << var->value1 << ' ' << var->value2 << ' ' << var->value3 << '\n';
	}
	fs.close();
}

void
Load(std::string file)
{
	std::ifstream fs(file);
	int length = 0;
	fs >> length;

	for (int i = 0; i < length; i++) {
		Object* item = new Object();
		fs >> item->value1 >> item->value2 >> item->value3;
		table.push_back(item);
	}

	fs.close();

	printf("Использовано %i байт\n", memory_count);
}

void
Sort()
{
	int len = table.size() - 1;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (table[j]->value1 > table[j + 1]->value1) {
				Object* t = table[j];
				table[j] = table[j+1];
				table[j+1] = t;
			}
		}
	}
}

std::vector<Object*>
Find(int index)
{
	std::vector<Object*> find_result;

	for each (Object* var in table) {
		if (var->value1 == index)
			find_result.push_back(var);
	}

	return find_result;
}

void
Print(std::vector<Object*> list)
{
	for each (Object* var in list) {
		std::cout << var->value1 << '\t' << var->value2 << '\t' << var->value3 << '\n';
	}
}
