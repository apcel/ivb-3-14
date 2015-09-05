#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

class pr
{
public:
	virtual void print(){}
};

class Lit : public pr
{
	char * value;
	
	void print()
	{
		cout << "This is litera " << value << endl; 
	}
public:
	Lit(char * v)
	{
		value = v;
	}
	
	~Lit()
	{
		free(value);
	}
};


class num : public pr
{
	double value;
	
	void print()
	{
		cout << "this is number" << value << endl;
	}
public:
	num(double v)
	{
		value = v;
	}
};

class Symbol : public Pr
{
public:
	Symbol(char v)
	{
		value = v;
	}
private:
	char value;

	void print()
	{
		cout << "this is symbol " << value; 
	}
};

bool Nums(char c)
{
	return c >= '0' && c <= '9';
}

bool Lits(char c)
{
	return	c >= 'A' && c <= 'Z' ||	c >= 'a' && c <= 'z';
}

bool Symbols(char c)
{
	return !Nums(c) && !Lits(c);
}

int main()
{
	setlocale(0, "Russian");

	std::vector<Pr *> pr;
	bool flag_number = false;
	bool use_tochka = false;
	
	char * input = _strdup("gg olool %228828282 _4672_test");
	int len = strlen(input);
	char x;
	std::vector<char> buff;

	cout << "is the starting line" << input;

	for (int i = 0; i <= len; i++) {
		x = input[i];
		if (flag_number && c == ',' && !use_tochka) {
			use_tochka = true;
			buff.push_back(c);
		} else 	if (Symbols(c) && !(c == '_'&&buff.size())) {
				if (buff.size() != 0) {
					int y1 = 0;
					
					char * t = new char[buff.size() + 1];
					for (auto y = buff.begin(); y != buff.end(); y++, y1++)
						t[y1] = *y;

				`	if (flag_number) {
						t.push_back(new Num(atof(t)));
						flag_number = false;
						use_tochka = false;
						delete t;
					} else
						pr.push_back(new Lit(t));

					buff.clear();
				}
				if (c != 0)
					pr.push_back(new Symbol(c));
			} else {
				if (flag_number || buff.size() == 0)
					flag_number = Nums(c);

				buff.push_back(c);
			}
		}
	}

	for (auto i = pr.begin(); i != pr.end(); i++)
		(*i)->print();

	
	for (auto i = pr.begin(); i != pr.end(); i++)
		delete *i;

	pr.clear();
	free(input);

	system("pause");
	return EXIT_SUCCESS;
}
