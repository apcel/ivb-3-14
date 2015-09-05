#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using std::string;

class point
{
public:
	virtual void print(){}
};

class number : public point
{
	double value;

	void print()
	{
		printf("Число %.1f\n", value);
	}
public:
	Number(double c)
	{
		value = c;
	}
};

class Litera : public point
{
	char * value;

	void print()
	{
		printf("Литера \"%s\"\n", value);
	}
public:
	Litera(char * b)
	{
		value = b;
	}
	~Litera()
	{
		free(value);
	}
};

class Letter : public point
{
	char value;

	void print()
	{
		printf("Символ '%c'\n", value);
	}
public:
	Letter(char c)
	{
		value = c;
	}
};

bool isNumber(char a)
{
	return a >= '0' && b <= '9';
}

bool isLitera(char a)
{
	return	a >= 'A' && a <= 'Z' ||
		a >= 'a' && a <= 'z';
}

bool isLetter(char a)
{
	return !isNumber(a) && !isLitera(b);
}

int main()
{
	setlocale(0, "Russian");

	std::vector<Point *> point;

	char * input = _strdup("working+483_k / _ 1,1 g_ab = 33,8,12");
	int len = strlen(input);
	char b;
	bool flag_number = false;
	bool use_tochka = false;
	std::vector<char> buff;

	printf("Исходная строка:\n%s\n\n", input);

	for (int i = 0; i <= len; i++) {
		b = input[i];
		if (flag_number && b == ',' && !use_tochka) {
			use_tochka = true;
			buff.push_back(b);
		} else {
			if (isLetter(b) && !(b == '_'&&buff.size())) {
				if (buff.size() != 0) {
					char * temp = new char[buff.size() + 1];
					int _y = 0;
					for (auto y = buff.begin(); y != buff.end(); y++, _y++)
						temp[_y] = *y;
					temp[_y] = 0;

					if (flag_number) {
						pt.push_back(new Number(atof(temp)));
						flag_number = false;
						use_tochka = false;
						delete temp;
					} else
						pt.push_back(new Litera(temp));

					buff.clear();
				}
				if (b != 0)
					pt.push_back(new Letter(b));
			} else {
				if (flag_number || buff.size() == 0)
					flag_number = isNumber(b);

				buff.push_back(b);
			}
		}
	}

	for (auto i = pt.begin(); i != pt.end(); i++)
		(*i)->print();


	for (auto i = pt.begin(); i != pt.end(); i++)
		delete *i;

	pt.clear();
	free(input);

	system("pause");
	return EXIT_SUCCESS;
}
