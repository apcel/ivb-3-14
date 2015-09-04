/*

1) Дана входная строка любой длины
2) Строку разобрать на элементы:
2.1) Число
2.2) Символ
2.3) Литерал
3) Число: начинается с '0'..'9', может содержать точку (вещественное число)
Литерал: начинается с буквы либо '_', может содержать любое кол-во цифр/букв до разделителя
Разделитель: символ, не являющийся цифрой, буквой или '_'
Символ: любой символ, не являющийся пробелом, цифрой, буквой, '_'
4) Результатом работы является коллекция токенов
[паровозик, разобранный на цифры-литералы-символы]
[Примечание: символ содержит _один_ символ. Поначалу у меня из-за этого неправильно было]

*/

#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <time.h>
#include <iostream>

using namespace std;

class Item
{
public:
	virtual void Print() { }
};

class Number : public Item
{
private:
	double value;

public:
	Number(double n)
	{
		value = n;
	}

	void Print()
	{
		printf("Number: %.1f\n", value);
	}
};

class Litera : public Item
{
private:
	char* value;
public:
	Litera(char * l)
	{
		value = l;
	}
	
	void Print()
	{
		printf("Literal: %s\n", value);
	}
};

class Symbol : public Item
{
	char value;

public:
	Symbol(char c)
	{
		value = c;
	}

	void Print()
	{
		printf("Symbol: %c\n", value);
	}
};

bool isNumber(char c)
{
	return c >= '0' && c <= '9';
}

bool isLiteral(char c)
{
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

bool isSymbol(char c)
{
	return !isNumber(c) && !isLiteral(c);
}

vector<Item*> parse_string(string s);
string get_random_string(int length);

int main()
{
	int length = 10 + rand() % 30;
	string line = get_random_string(length);
	std::vector<Item*> items = parse_string(line);
	for (auto i = items.begin(); i != items.end(); i++)
		(*i)->Print();
	items.clear();
	system("pause");
	return EXIT_SUCCESS;
}

vector<Item*> parse_string(string line)
{
	std::vector<Item*> items;
	int length = line.length();
	char c;
	bool flag_number = false;
	bool use_tochka = false;
	std::vector<char> buff;
	printf("%s\n", line.c_str());
	for (int i = 0; i <= length; i++) {
		c = line[i];
		if (flag_number && c == ',' && !use_tochka) {
			use_tochka = true;
			buff.push_back(c);
		} else {
			if (isSymbol(c) && !(c == '_'&&buff.size())) {
				if (buff.size() != 0) {
					char * temp = new char[buff.size() + 1];
					int _y = 0;
					for (auto j = buff.begin(); j != buff.end(); j++, _y++)
						temp[_y] = *j;
					temp[_y] = 0;
					if (flag_number) {
						items.push_back(new Number(atof(temp)));
						flag_number = false;
						use_tochka = false;
						delete temp;
					} else {
						items.push_back(new Litera(temp));
					}
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
	return items;
}

string get_random_string(int length)
{
	static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-\|/?._=~!@#$%^&*() {}";
	srand(time(NULL));
	string line;
	line.resize(length);
	for (auto i = 0; i < length; i++)
		line[i] = charset[rand() % charset.length()];
	return line;
}