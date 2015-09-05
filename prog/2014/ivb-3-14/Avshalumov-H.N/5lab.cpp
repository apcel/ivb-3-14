#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <typeinfo>

typedef std::vector<double> line;
typedef std::vector<line> matrix;

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

	matrix parse(std::string  name)
	{
		matrix matrix;
		matrix.clear();
		line row;
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


void PrintMatrix(matrix m)
{
	for (auto i = m.begin(); i != m.end(); i++) {
		for (auto j = i->begin(); j != i->end(); j++)
			printf("%3.1f\t", *j);
		printf("\n");
	}
	printf("\n");
}

int GetCount(line m)
{
	int count = 0;
	for (auto j = m.begin(); j != m.end(); j++) {
		if (*j > 0)
			count++;
	}

	return count;
}

int GetMax(matrix m)
{
	int max = 0;
	for (auto i = m.begin(); i != m.end(); i++) {
		for (auto j = i->begin(); j != i->end(); j++) {
			if (*j > max)
				max = *j;
		}
	}
	return max;
}

int main()
{
	setlocale(0, "Russian");

	NumberFromFileParser parser;
	matrix m1 = parser.parse(std::string("mat1.txt"));
	matrix m2 = parser.parse(std::string("mat2.txt"));

	PrintMatrix(m1);
	PrintMatrix(m2);

	matrix m;
	if (GetMax(m1) > GetMax(m2)) {
		m = m1;
		printf("\nМаксимальный элемен 1 матрици больше максимального элеманта во 2 матрици\n\n");
	} else {
		m = m2;
		printf("\nМаксимальный элемен 2 матрици больше максимального элеманта в 1 матрици\n\n");
	}

	for (int i = 0; i < m.size(); i++) {
		printf("В %i строке %i неотрицательных элемент`а\n", i + 1, GetCount(m[i]));
	}

	system("pause");
	return EXIT_SUCCESS;
}
