#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <typeinfo>

typedef std::vector<double> vector;
typedef std::vector<vector> matrix;

class NumberFromFileParser
{
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

	matrix parse(std::string  name)
	{
		matrix mtx;
		mtx.clear();
		vector row;
		if (_fd == nullptr)
			_fd = fopen(name.c_str(), "r");
		if (_fd == nullptr)
			return mtx;
		next();
		while (!eof()) {
			_buffer.clear();
			parseNumber();
			if (_buffer.size() > 0) {
				row.push_back(atof(_buffer.c_str()));
			}
			if (isEndOfLine()) {
				skipEndOfLine();
				mtx.push_back(row);
				row.clear();
			}
		}
		if (row.size() > 0)
			mtx.push_back(row);
		fclose(_fd);
		_fd = nullptr;
		return mtx;
	}
};


int
FindZeroElement(matrix m)
{
	int count = 0;
	for (auto i = m.begin(); i != m.end(); i++) {
		for (auto j = i->begin(); j != i->end(); j++) {
			if (*j == 0)
				count++;
		}
	}

	return count;
}

void
OutputNegativeElements(matrix m)
{
	int n = 0;
	for (auto i = m.begin(); i != m.end(); i++, n++) {
		int max = 0;
		for (auto j = i->begin(); j != i->end(); j++) {
			if (*j < 0)
				max++;
		}
		printf("Line %i: %d\n", n, max);
	}
}

void
PrintMatrix(matrix m)
{
	for (auto i = m.begin(); i != m.end(); i++) {
		for (auto j = i->begin(); j != i->end(); j++) {
			printf("%3.1f\t", *j);
		}
		printf("\n");
	}
	printf("\n");
}

int
main()
{
	setlocale(0, "Russian");

	NumberFromFileParser parser;
	matrix m1 = parser.parse(std::string("mat1.txt"));
	matrix m2 = parser.parse(std::string("mat2.txt"));

	PrintMatrix(m1);
	PrintMatrix(m2);

	int zeroCount1 = FindZeroElement(m1);
	int zeroCount2 = FindZeroElement(m2);

	if (zeroCount1 < zeroCount2)
		OutputNegativeElements(m1);
	else
		OutputNegativeElements(m2);

	system("pause");
	return EXIT_SUCCESS;
}
