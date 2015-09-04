/*

1. Дан объект произвольной структуры (не менее трёх полей)
2. Написать программу, осуществляющую работу с коллекцией объектов
2.1 Сохранение коллекции в файл
2.2 Загрузка коллекции из файла
2.3 Сортировка коллекции по выбранному полю
2.4 Поиск объекта в коллекции (по любым полям)
2.5 Кол-во памяти, выделеной для единичного объекта
2.6 -//- для коллекции объектов
2.7 Вывод на экран форматированной коллекции объектов

*/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <algorithm>

using namespace std;

class Cat
{
public:
	unsigned int Age;
	string Name;
	bool Sex;

	Cat()
	{
	}

	Cat(unsigned int age, string name, bool sex)
	{
		this->Age = age;
		this->Name = name;
		this->Sex = sex;
	}

	friend ostream& operator<< (ostream& stream, const Cat& cat);
	friend istream& operator>> (istream& stream, Cat& cat);
};

ostream& operator<< (ostream& stream, const Cat& cat)
{
	stream << cat.Age << "\t";
	stream << cat.Name << "\t";
	stream << cat.Sex << "\n";
	return stream;
}

istream& operator>> (istream& stream, Cat& cat)
{
	stream >> cat.Age;
	stream >> cat.Name;
	stream >> cat.Sex;
	return stream;
}

Cat* FindCat(int age, string name, bool sex, vector<Cat*>* cats);
size_t IsCatFat(Cat* cat);
size_t HowCatsAreFat(vector<Cat*>* cats);
void SaveTheCats(vector<Cat*>* cats);
vector<Cat*>* GetTheCats();
vector<Cat*>* MakeSomeCats(int count);
void PrintCats(vector<Cat*>* cats);
void SortCats(int field, vector<Cat*>* cats);

const char* path = "C:\\dev\\cats.txt";

struct sort_by_age
{
	inline bool operator() (Cat* c1, Cat* c2)
	{
		return (c1->Age < c2->Age);
	}
};

struct sort_by_name
{
	inline bool operator() (Cat* c1, Cat* c2)
	{
		return (c1->Name < c2->Name);
	}
};

struct sort_by_sex
{
	inline bool operator() (Cat* c1, Cat* c2)
	{
		return (c1->Sex < c2->Sex);
	}
};

int main()
{
	printf("Started.\n");
	srand(time(NULL));
	vector<Cat*>* cats = MakeSomeCats(10);
	SortCats(1, cats);
	SaveTheCats(cats);
	cats->clear();
	cats = GetTheCats();
	printf("First cat is %d bytes fat.\n", IsCatFat(cats->front()));
	printf("All cats are %d bytes fat.\n", HowCatsAreFat(cats));
	system("pause");
	PrintCats(cats);
	system("pause");
	return 0;
}

size_t IsCatFat(Cat* cat)
{
	return sizeof(cat->Age) + sizeof(cat->Name) + sizeof(cat->Sex);
}

size_t HowCatsAreFat(vector<Cat*>* cats)
{
	size_t result = 0;
	for (auto i = cats->begin(); i < cats->end(); i++) {
		result += sizeof((*i)->Age) + sizeof((*i)->Name) + sizeof((*i)->Sex);
	}
	return result;
}

void SaveTheCats(vector<Cat*>* cats)
{
	printf("Saving the cats.\n");
	ofstream f;
	f.open(path);
	f << cats->size() << "\n";
	for (auto i = cats->begin(); i < cats->end(); i++)
		f << *(*i);
	f.close();
}

vector<Cat*>* GetTheCats()
{
	printf("Getting the cats.\n");
	ifstream f;
	f.open(path);
	vector<Cat*>* result = new vector<Cat*>();
	int count;
	f >> count;
	for (auto i = 0; i < count; i++) {
		Cat* cat = new Cat();
		f >> *cat;
		result->push_back(cat);
	}
	f.close();
	return result;
}

Cat* FindCat(int age, string name, bool sex, vector<Cat*>* cats)
{
	printf("Finding lost cat.\n");
	Cat* result = nullptr;
	for (auto i = cats->begin(); i < cats->end(); i++) {
		if (age != NULL && name != "" && sex != NULL) {
			if ((*i)->Age == age && (*i)->Name == name && (*i)->Sex == sex) {
				result = *i;
				break;
			}
		} else if (age != NULL && name != "") {
			if ((*i)->Age == age && (*i)->Name == name) {
				result = *i;
				break;
			}
		} else if (age != NULL && sex != NULL) {
			if ((*i)->Age == age && (*i)->Sex == sex) {
				result = *i;
				break;
			}
		} else if (name != "" && sex != NULL) {
			if ((*i)->Name == name && (*i)->Sex == sex) {
				result = *i;
				break;
			}
		} else if (age != NULL) {
			if ((*i)->Age == age) {
				result = *i;
				break;
			}
		} else if (name != "") {
			if ((*i)->Name == name)	{
				result = *i;
				break;
			}
		} else if (sex != NULL)	{
			if ((*i)->Sex == sex) {
				result = *i;
				break;
			}
		}
	}
	return result;
}

vector<Cat*>* MakeSomeCats(int count)
{
	static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	printf("Making some new cats.\n");
	vector<Cat*>* cats = new vector<Cat*>();
	for (auto i = 0; i < count; i++) {
		string name;
		int name_length = 5 + rand() % 15;
		name.resize(name_length);
		for (auto j = 0; j < name_length; j++) {
			name[j] = charset[rand() % charset.length()];
		}
		int age = 1 + rand() % 20;
		bool sex = rand() % 2;
		Cat* cat = new Cat(age, name, sex);
		cats->push_back(cat);
	}
	return cats;
}

void PrintCats(vector<Cat*>* cats)
{
	printf("Here are your cats.\n");
	printf(" %-5s | %-20s | %-5s\n", "Age", "Name", "Sex");
	printf("--------------------------------------\n");
	for (auto i = cats->begin(); i < cats->end(); i++)
		printf(" %-5d | %-20s | %-5s\n", (*i)->Age, (*i)->Name.c_str(), ((*i)->Sex) ? "male" : "female");
	printf("--------------------------------------\n");
}

void SortCats(int field, vector<Cat*>* cats)
{
	switch (field) {
	case 0:
		sort(cats->begin(), cats->end(), sort_by_age());
		break;
	case 1:
		sort(cats->begin(), cats->end(), sort_by_name());
		break;
	case 2:
		sort(cats->begin(), cats->end(), sort_by_sex());
		break;
	}
}