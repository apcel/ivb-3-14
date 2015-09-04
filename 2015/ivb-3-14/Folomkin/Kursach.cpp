#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

#define OPERATOR_NONE		0
#define OPERATOR_PLUS		1
#define OPERATOR_MINUS		2
#define OPERATOR_MULTER		3
#define OPERATOR_DIVISION	4

using namespace std;

struct Element {
	string data;
	double value = OPERATOR_NONE;
	Element *A = nullptr, *B = nullptr;

	Element(double value);
	Element(string data);
	~Element();

	double operator()();
};

Element::Element(double value)
{
	this->value = value;
}

Element::Element(string data)
{
	this->data = data;
	bool flag = true;

	int sp;
	while (flag && data[0] == '(' && data[data.length() - 1] == ')') {
		sp = 0;
		for (unsigned int i = 1; i < data.length() - 2; i++) {
			if (data[i] == ')')
				sp--;
			else if (data[i] == '(')
				sp++;

			if (sp == -1) {
				flag = false;
				break;
			}
		}
		if (flag)
			data = data.substr(1, data.length() - 2);
	}

	for (int n = 0; n < 2; n++) {
		sp = 0;
		for (int i = data.length() - 1; i >= 0; i--) {
			if (data[i] == ')')
				sp--;
			else if (data[i] == '(')
				sp++;
			else if (sp == 0) {
				switch (n) {
				case 0:
					switch (data[i]) {
					case '+': value = OPERATOR_PLUS; break;
					case '-': value = OPERATOR_MINUS; break;
					}
					break;
				case 1:
					switch (data[i])
					{
					case '*': value = OPERATOR_MULTER; break;
					case '/': value = OPERATOR_DIVISION; break;
					}
					break;
				}

				if (value != OPERATOR_NONE) {
					A = new Element(data.substr(0, i));
					B = new Element(data.substr(i + 1, data.length() - i - 1));
					return;
				}
			}
		}
	}

	value = atof(data.c_str());
}

double
Element::operator()()
{
	if (A != nullptr) {
		double a = (*A)();
		double b = (*B)();

		switch ((int)value) {
		case OPERATOR_PLUS:
			return a + b;
		case OPERATOR_MINUS:
			return a - b;
		case OPERATOR_MULTER:
			return a * b;
		case OPERATOR_DIVISION:
			if (b == 0)
				std::runtime_error("„еление на ноль");
			return a / b;
		}
	}
	return value;
}


Element::~Element()
{
	if (A != nullptr)
		delete A;
	if (B != nullptr)
		delete B;
}

int
main()
{
	setlocale(0, "Russian");

	std::string data;
	while (true) {
		printf("‚ведите новое выражение:\n");
		std::getline(cin, data);
		if(data=="exit")
			break;
		try {
			double result = Element(data)();
			if (result == (int)result)
				printf("=%i\n", (int)result);
			else
				printf("=%f\n", result);
		} catch (const std::exception& e) {
			printf("Ћшибка: %s.\n", e.what());
		}
	}
	system("pause");
	return EXIT_SUCCESS;
}
