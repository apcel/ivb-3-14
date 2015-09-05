/* 
 * Лаба №7 
 * ИВБ-3-14 
 * Фоломкин Антон 
 */ 


#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

using std::string;

class Box
{
public:
	virtual void print(){}
};

class Nomer : public Box
{
	double value;

	void print()
	{
		printf("Номер %.1f\n", value);
	}
public:
	Nomer(double a)
	{
		value = a;
	}
};

class Bykva : public Box
{
	char * value;

	void print()
	{
		printf("Буква \"%s\"\n", value);
	}
public:
	Bykva(char * a)
	{
		value = a;
	}
	~Bykva()
	{
		free(value);
	}
};

class Symbol : public Box
{
	char value;

	void print()
	{
		printf("Символ '%c'\n", value);
	}
public:
	Symbol(char a)
	{
		value = a;
	}
};

bool isBykva(char c)
{
	return	c >= 'A' && c <= 'Z' ||
		c >= 'a' && c <= 'z';
}

bool isNomer(char c)
{
	return c >= '0' && c <= '9';
}

bool isSymbol(char c)
{
	return !isNomer(c) && !isBykva(c);
}

int main()
{
	setlocale(0, "Russian");

	std::vector<Box *> items;

	char * input = _strdup("testing+218_m / _ 1,8 e_zt = 25,7,15");
	int len = strlen(input);
	char c;
	bool use_tochka = false;
	bool flag_nomer = false;
	std::vector<char> buff;

	printf("Исходная строка:\n%s\n\n", input);

	for (int i = 0; i <= len; i++) {
		c = input[i];
		if (flag_nomer && c == ',' && !use_tochka) {
			use_tochka = true;
			buff.push_back(c);
		} else {
			if (isSymbol(c) && !(c == '_'&&buff.size())) {
				if (buff.size() != 0) {
					char * temp = new char[buff.size() + 1];
					int _y = 0;
					for (auto y = buff.begin(); y != buff.end(); y++, _y++)
						temp[_y] = *y;
					temp[_y] = 0;

					if (flag_nomer) {
						items.push_back(new Nomer(atof(temp)));
						flag_nomer = false;
						use_tochka = false;
						delete temp;
					} else
						items.push_back(new Bykva(temp));

					buff.clear();
				}
				if (c != 0)
					items.push_back(new Symbol(c));
			} else {
				if (flag_nomer || buff.size() == 0)
					flag_nomer = isNomer(c);

				buff.push_back(c);
			}
		}
	}

	
	for (auto i = items.begin(); i != items.end(); i++)
		(*i)->print();

	for (auto i = items.begin(); i != items.end(); i++)
		delete *i;


	items.clear();
	free(input);

	system("pause");
	return EXIT_SUCCESS;
}
