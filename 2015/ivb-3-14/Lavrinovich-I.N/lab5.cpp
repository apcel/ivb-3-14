#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <typeinfo>

typedef std::vector<std::vector<double>> matrix;

template <typename Type>
class NumberFromFileParser {
	char                _ch;
	FILE               *_fd;
	std::string         _buffer;
public:
	NumberFromFileParser() : _ch(0), _fd(nullptr){}

	bool eof() const
	{
		return feof(_fd) > 0;
	}
	bool next()
	{
		_ch = fgetc(_fd);
		return _ch != EOF;
	}
	bool isWhitespace() const
	{
		return isspace((int)_ch) > 0;
	}
	bool isDigit() const
	{
		return isdigit((int)_ch) > 0;
	}
	bool isDot() const
	{
		return _ch == '.' ||
			_ch == ',';
	}
	bool isSign() const
	{
		return _ch == '-' ||
			_ch == '+';
	}
	bool isEndOfLine() const
	{
		return _ch == '\r' ||
			_ch == '\n';
	}
	void skipWhitespace()
	{
		while (!eof() && isWhitespace() && next());
	}
	void skipEndOfLine()
	{
		while (!eof() && isEndOfLine() && next());
	}
	void parseNumber()
	{
		skipWhitespace();
		while (!eof() && !isWhitespace() &&
			(isSign() || isDot() || isDigit())) {
			put();
			next();
		}
	}
	void put()
	{
		_buffer.push_back(_ch);
	}

	std::vector<std::vector<Type>> parse(std::string  name)
	{
		std::vector<std::vector<Type>> matrix;
		matrix.clear();
		std::vector<Type> row;
		if (_fd == nullptr)
			_fd = fopen(name.c_str(), "r");
		if (_fd == nullptr)
			return matrix;
		next();
		while (!eof()) {
			_buffer.clear();
			parseNumber();
			if (_buffer.size() > 0) {
				row.push_back(atof(_buffer.c_str()));
			}
			if (isEndOfLine()) {
				skipEndOfLine();
				matrix.push_back(row);
				row.clear();
			}
		}
		if (row.size() > 0)
			matrix.push_back(row);
		fclose(_fd);
		_fd = nullptr;
		return matrix;
	}
};

static void __printMatrix(matrix m);
static int __findNullElement(matrix m);
static void __product_Element(matrix m);

int
main()
{
	setlocale(0, "Russian");

	NumberFromFileParser<double> parser;
	matrix m1 = parser.parse(std::string("mat1.txt"));
	matrix m2 = parser.parse(std::string("mat2.txt"));

	__printMatrix(m1);
	__printMatrix(m2);

	int zeroCount1 = __findNullElement(m1);
	int zeroCount2 = __findNullElement(m2);

	if (zeroCount1 > zeroCount2) {
		printf("Output matrix N2:\n");
		__product_Element(m2);
	} else {
		printf("Output matrix N1:\n");
		__product_Element(m1);
	}

	system("pause");
	return EXIT_SUCCESS;
}

void
__printMatrix(matrix m)
{
	for (auto i = m.begin(); i != m.end(); i++){
		for (auto j = i->begin(); j != i->end(); j++){
			printf("%3.1f\t", *j);
		}
		printf("\n");
	}
	printf("\n");
}

int
__findNullElement(matrix m) 
{
	int count = 0;
	for (auto i = m.begin(); i != m.end(); i++){
		for (auto j = i->begin(); j != i->end(); j++){
			if (*j == 0)
				count++;
		}
	}
	return count;
}

void
__product_Element(matrix m)
{
	int n = 0;
	for (auto i = m.begin(); i != m.end(); i++, n++){
		double result = 1;
		for (auto j = i->begin(); j != i->end(); j++){
			if (*j != 0)
				result *= *j;
		}
		printf("Line %i: %f\n", n, result);
	}
}
