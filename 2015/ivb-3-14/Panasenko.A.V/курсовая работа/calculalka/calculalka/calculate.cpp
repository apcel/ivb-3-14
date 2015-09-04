#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::strlen;

#include <stack>
using std::stack;

#include <vector>
using std::vector;

#include "calculate.h"

/* таблица выбора пути для символа:
	=    +    -    *    /   (    )

=   4    1    1    1    1   1    5

+   2    2    2    1    1   1    2

-   2    2    2    1    1   1    2

*   2    2    2	   2	2	1    2

/   2    2    2    2    2   1    2

(   5    1    1    1    1   1    3

1) символ отправляется в operation
2) последний символ, направившийся в стек, направляется в postN
3) текущий символ и предыдущий символ, отправившийся в Operation, удаляются
4) Остановка. Символы, находящиеся в postN, представляют собой формулу в обратной польской записи, если читать слева направо
5) Остановка. Произошла ошибка. Изначальная формула была некорректно сбалансирована */


calculate::calculate(string copy)
{
	infN = copy;
	last = 'b';
	parce();
	calc();
}

calculate::~calculate() {}

void calculate::error()
{
	cout << "\nОшибка, неивестная комбинация! " << endl;
	cout << "Сброс данных, введите выражение корректно ('e' - для выхода)" << endl;;
	calculate::~calculate();
}

void calculate::str(char& last, string infN, int i)
{
	string str(&last, 1);
	operation.pop();
	postN.push(str);
	operation.push(infN[i]);
	last = infN[i];
}
string calculate::number(int& i, string g)
{
	int c = 0;
	int begin = i;
	while (true) {
		if ((g[i] == ',') || (isdigit(g[i]))) {
			c++;
			i++;
		} else {
			i--;
			break;
		}
	}
	string x(g, begin, c);
	return x;
}

string calculate::numberM(int& i)
{
	string x;
	x = "-";
	i++;
	while (true) {
		if ((infN[i] == ',') || (isdigit(infN[i]))) {
			x += infN[i];
			i++;
		}
		else {
			i--;
			break;
		}
	}
	return x;
}

string calculate::numberS(int& i)
{
	string x;
	x = "-";
	i++;
	while (true) {
		if ((infN[i] == ',') || (isdigit(infN[i]))) {
			x += infN[i];
			i++;
		}
		else {
			i--;
			break;
		}
	}
	return x;
}

char calculate::parce()
{
	for (int i = 0; i < infN.size(); i++) {
		int size;
		string s;
		switch (infN[i]) {
		case 'm':
			s = numberM(i);
			postN.push(s);
			break;
		case '+':
			if (operation.empty() || last == '(') {
				operation.push(infN[i]);
				last = infN[i];
				break;
			}
			else if (last == '+' || last == '-' || last == '*' || last == '/') {
				str(last, infN, i);
				break;
			}
		case '-':
			if (operation.empty() || last == '(') {
				operation.push(infN[i]);
				last = infN[i];
				break;
			}
			else if (last == '+' || last == '-' || last == '*' || last == '/') {
				str(last, infN, i);
				break;
			}
		case '*':
			if (operation.empty() || last == '(' || last == '+' || last == '-') {
				operation.push(infN[i]);
				last = infN[i];
				break;
			}
			else if (last == '*' || last == '/') {
				str(last, infN, i);
				break;
			}
		case '/':
			if (operation.empty() || last == '(' || last == '+' || last == '-') {
				operation.push(infN[i]);
				last = infN[i];
				break;
			}
			else if (last == '*' || last == '/') {
				str(last, infN, i);
				break;
			}
		case '(':
			if (last == '+' || last == '-' || last == '*' || last == '/' || last == '(' || operation.empty()) {
				operation.push(infN[i]);
				last = infN[i];
				break;
			}
		case ')': 
				if (last == '+' || last == '-' || last == '*' || last == '/') {
					size = operation.size();
					for (int j = 0; j < size; j++) {
					    string x;
						x += operation.top();
						if (x == "+" || x == "-" || x == "*" || x == "/") {
							postN.push(x);
							operation.pop();
						} else if (x == "(") {
							operation.pop();
							last = '(';
							break;
						}
				    }
				}
		
		case '=': 
				if (last == '+' || last == '-' || last == '*' || last == '/') {
					size = operation.size();
					for (int j = 0; j < size; j++) {
						string x;
						x += operation.top();
						if (x == "+" || x == "-" || x == "*" || x == "/") {
							postN.push(x);
							operation.pop();
						} else if(x == "(") {
							error();
						}
					}
					break;
				}
		case ' ':
			break;
		default:
			if (isdigit(infN[i])) {
				string x = number(i, infN);
				postN.push(x);
				break;
			} else if (infN[i] != '=' && infN[i] != ')' && infN[i] != '(' && infN[i] != '+' && infN[i] != '-' && infN[i] != '*' && infN[i] != '/' && !isdigit(infN[i]) && infN[i] != ',' && infN[i] != 'm')
				error();
		}
	}
		
	while (!postN.empty()) {
		postN2.push_back(postN.top());
		postN.pop();
	}
	return 0;
}

void calculate::print()
{
	cout << infN << ' ' << numb.top();
	
}

void calculate::calc()
{
	double a, b;
	string c;
	while(postN2.size() >= 1) {
		if (postN2.back() == "+") {
			a = numb.top();
			numb.pop();
			b = numb.top();
			numb.pop();
			numb.push(a + b);
			postN2.pop_back();
		} else if (postN2.back() == "-") {
			a = numb.top();
			numb.pop();
			b = numb.top();
			numb.pop();
			numb.push(b - a);
			postN2.pop_back();
		} else if (postN2.back() == "/") {
			a = numb.top();
			numb.pop();
			b = numb.top();
			numb.pop();
			if (a != 0) {
				numb.push(b / a);
				postN2.pop_back();
			} else {
				error();
			}
		} else if (postN2.back() == "*") {
			a = numb.top();
			numb.pop();
			b = numb.top();
			numb.pop();
			numb.push(a * b);
			postN2.pop_back();
		} else {
			numb.push(atof(postN2.back().c_str()));
			postN2.pop_back();
		}
	}
	print();
}
