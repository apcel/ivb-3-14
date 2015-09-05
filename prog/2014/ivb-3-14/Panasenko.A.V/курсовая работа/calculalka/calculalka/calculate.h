#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <stack>
using std::stack;

#include <string>
using std::string;

#include <vector>
using std::vector;

class calculate
{
private:
	stack <char> operation; 
	stack <string> postN;
	vector<string> postN2;
	stack <double> numb;
	string infN; 
	char last; 
	stack <string> st;
public:
	calculate(string);
	~calculate();
	char parce(); 
	void error();
	string number(int&, string);
	void str(char&, string, int);
	void calc();
	void print();
	string numberM(int&);
	string numberS(int&);
};

