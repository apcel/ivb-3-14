#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#define NUMBER_SPLIT_SYMBOL '.'
using std::string;

class Item {};

class Litera : public Item{
	string str;
public:
	Litera(string s)
	{
		str=s;
	}
};

class Symbol : public Item{
	char sym;
public:
	Symbol(char s)
	{
		sym=s;
	}
};

class Number : public Item{
	double num;
public:
	Number(double s)
	{
		num=s;
	}
};

bool isnum(char h)
{
	return h >= '0' && h <= '9';
}
bool isword(char h)
{
	return (h >= 'A' && h <= 'Z') || (h >= 'a' && h <= 'z');
}
bool issym(char h)
{
	return !isnum(h) && !isword(h);
}

int
main()
{
	string input("solo322_adda. dw =+ 2/4=0.5 74757.717.177");
	printf("%s\n\n", input.c_str());

	std::vector<Item*> result;
	std::vector<char> temp;
	bool flag = true;
	bool use = false;

	input.length();
	for (int i = 0; i <= input.length(); i++) {
		char c = input[i];
		if (issym(c) && !(!use && c == NUMBER_SPLIT_SYMBOL)) {
			if(temp.size() != 0) {
				char* fad = new char [temp.size()+1];
				for (int j = 0; j < temp.size(); j++)
					fad[j] = temp[j];
				fad[temp.size()] = 0;

				if(flag) {
					double n = atof(fad);
					result.push_back(new Number(n));
					printf("Number: %f\n", n);
				} else {
					result.push_back(new Litera(fad));
					printf("Litera: %s\n", fad);
				}

				free(fad);
				temp.clear();
				flag = true;
				use = false;
			}

			if(c != 0) {
				result.push_back(new Symbol(c));
				printf("Symbol: %c\n", c);
			}
		} else {
			if(flag)
				flag = c == NUMBER_SPLIT_SYMBOL || isnum(c);
			temp.push_back(c); 

			if(c == NUMBER_SPLIT_SYMBOL)
				use = true;
		}
	}
	
	for (auto i = result.begin(); i != result.end(); i++)
		delete *i;

	system("pause");
	return EXIT_SUCCESS;
}
