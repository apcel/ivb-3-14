#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

struct Element {
};

struct Number : public Element {
	double value;
	Number(double v) : value(value)
	{
		printf("Number: %f\n", v);
	}
};
struct Litera : public Element {
	std::string value;
	Litera(std::string v) : value(value)
	{
		printf("Litera: %s\n", v.c_str());
	}
};
struct Symbol : public Element {
	char value;
	Symbol(char v) : value(value)
	{
		printf("Symbol: %c\n", v);
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
	return	c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

bool
isSymbol(char c)
{
	return !isNumber(c) && !isLitera(c);
}

int
main()
{
	std::vector<Element*> result;

	std::string str = "Ildar228_gogogo 3.7 420 mlg +=+ 6789.65";
	std::string buff;
	const char * input = str.c_str();
	bool numberOnly = false;
	bool usePoint = false;
	char c;

	printf("Input:\n%s\n\n", input);

	for (int i = 0; i <= str.size(); i++) {
		c = input[i];
		if (numberOnly && c == '.' && !usePoint) {
			usePoint = true;
			buff += c;
		} else {
			if (isSymbol(c) && !(c == '_' && !buff.empty())) {
				if (!buff.empty()) {
					if (!numberOnly) {
						result.push_back(new Litera(buff));
					} else {
						usePoint = false;
						numberOnly = false;
						result.push_back(new Number(atof(buff.c_str())));
					}
					buff.clear();
				}
				if (c != 0)
					result.push_back(new Symbol(c));
			} else {
				if (buff.empty() || numberOnly)
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
