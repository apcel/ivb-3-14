#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

struct Element {
};

struct Symbol : public Element {
	char value;
	Symbol(char v) : value(value)
	{
		printf("Символ: %c\n", v);
	}
};
struct Litera : public Element {
	std::string value;
	Litera(std::string v) : value(value)
	{
		printf("Литера: %s\n", v.c_str());
	}
};
struct Number : public Element {
	double value;
	Number(double v) : value(value)
	{
		printf("Число: %f\n", v);
	}
};

bool
isNumber(char c)
{
	return c >= '0' && c <= '9';
}

bool
isLitera(char c)
{
	return	c >= 'A' && c <= 'Z' ||
		c >= 'a' && c <= 'z';
}

bool
isSymbol(char c)
{
	return !isNumber(c) && !isLitera(c);
}

int
main()
{
	setlocale(0, "Russian");

	std::vector<Element*> result;

	std::string text = "testing+322_l / _ 2,2 w_at = 75,3,14";
	std::string buff;
	const char * input = text.c_str();
	bool numberOnly = false;
	bool use_tochka = false;
	char c;

	printf("Исходная строка:\n%s\n\n", input);

	for (int i = 0; i <= text.size(); i++) {
		c = input[i];
		if (numberOnly && c == ',' && !use_tochka) {
			use_tochka = true;
			buff += c;
		} else {
			if (isSymbol(c) && !(c == '_' && !buff.empty())) {
				if (buff.size() != 0) {
					if (numberOnly) {
						result.push_back(new Number(atof(buff.c_str())));
						numberOnly = false;
						use_tochka = false;
					} else 
						result.push_back(new Litera(buff));

					buff.clear();
				}
				if (c != 0)
					result.push_back(new Symbol(c));
			} else {
				if (numberOnly || buff.empty())
					numberOnly = isNumber(c);
				buff += c;
			}
		}
	}

	for (auto i = result.begin(); i != result.end(); i++)
		delete *i;
	result.clear();

	system("pause");
	return EXIT_SUCCESS;
}
