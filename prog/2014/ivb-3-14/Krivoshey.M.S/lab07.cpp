#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

using std::string;

class Item
{
public:
	virtual void print(){}
};

class Number : public Item
{
	double value;
	
	void print()
	{
		printf("Число %.1f\n", value);
	}
public:
	Number(double v)
	{
		value = v;
	}
};

class Litera : public Item
{
	char * value;
	
	void print()
	{
		printf("Литера \"%s\"\n", value);
	}
public:
	Litera(char * v)
	{
		value = v;
	}
	~Litera()
	{
		free(value);
	}
};

class Symbol : public Item
{
	char value;

	void print()
	{
		printf("Символ '%c'\n", value);
	}
public:
	Symbol(char v)
	{
		value = v;
	}
};

bool isNumber(char c)
{
	return c >= '0' && c <= '9';
}

bool isLitera(char c)
{
	return	c >= 'A' && c <= 'Z' ||
		c >= 'a' && c <= 'z';
}

bool isSymbol(char c)
{
	return !isNumber(c) && !isLitera(c);
}

int main()
{
	setlocale(0, "Russian");

	std::vector<Item *> items;

	char * input = _strdup("testing+322_l / _ 2,2 w_at = 75,3,14");
	int len = strlen(input);
	char c;
	bool flag_number = false;
	bool use_tochka = false;
	std::vector<char> buff;

	printf("Исходная строка:\n%s\n\n", input);

	for (int i = 0; i <= len; i++) {
		c = input[i];
		if (flag_number && c == ',' && !use_tochka) {
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

					if (flag_number) {
						items.push_back(new Number(atof(temp)));
						flag_number = false;
						use_tochka = false;
						delete temp;
					} else
						items.push_back(new Litera(temp));

					buff.clear();
				}
				if (c != 0)
					items.push_back(new Symbol(c));
			} else {
				if (flag_number || buff.size() == 0)
					flag_number = isNumber(c);

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
