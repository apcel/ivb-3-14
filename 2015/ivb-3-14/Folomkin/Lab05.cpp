#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <typeinfo>

/*
* Лабораторная 6
* ИВБ-3-14
* Фоломкин Антон
*/
 
typedef std::vector<std::vector<double>> matrix;

template <typename Type>
class NumberFromFileParser
{
	char                _ch;
	FILE               *_fd;
	std::string         _buffer;
public:
	NumberFromFileParser() : _ch(0), _fd(nullptr) {}

	bool eof () const {
		return feof(_fd) > 0;
	}
	bool next () {
		_ch = fgetc(_fd);
		return _ch != EOF;
	}
	bool isWhitespace () const {
		return isspace((int)_ch) > 0;
	}
	bool isDigit () const {
		return isdigit((int)_ch) > 0;
	}
	bool isDot () const {
		return _ch == '.' || _ch == ',';
	}
	bool isSign () const {
		return _ch == '-' || _ch == '+';
	}
	bool isEndOfLine () const {
		return _ch == '\r' || _ch == '\n';
	}
	void skipWhitespace () {
		while (!eof() && isWhitespace() && next());
	}
	void skipEndOfLine () {
		while (!eof() && isEndOfLine() && next());
	}
	void parseNumber () {
		skipWhitespace();
		while (!eof() && !isWhitespace() &&
			(isSign() || isDot() || isDigit())) {
			put();
			next();
		}
	}
	void put () {
		_buffer.push_back(_ch);
	}

	std::vector<std::vector<Type>> parse(const char * const  name) {
		std::vector<std::vector<Type>> matrix;
		matrix.clear();
		std::vector<Type> row;
		if (_fd == nullptr)
			_fd = fopen(name, "r");
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

int
__findMaxElement (matrix m)
{
	int max = *m.begin()->begin();

	for (auto i = m.begin(); i != m.end(); i++) {
		for (auto j = i->begin(); j != i->end(); j++) {
			if (*j > max)
				max = *j;
		}
	}
	return max;
}

void
__outputCount (matrix m)
{
	int count;
	for (auto i = m.begin(); i != m.end(); i++) {
		count = 0;
		for (auto j = i->begin(); j != i->end(); j++) {
			if (*j > 0)
				count++;
		}
		printf("%i\n", count);
	}
}

void
PrintMatrix (matrix m)
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
main (int argc, char **argv)
{
	setlocale(0, "Russian");
	if (argc < 3)
		return 0;

	NumberFromFileParser<double> parser;
	matrix m1 = parser.parse(argv[1]);
	matrix m2 = parser.parse(argv[2]);

	PrintMatrix(m1);
	PrintMatrix(m2);

	int max1 = __findMaxElement(m1);
	int max2 = __findMaxElement(m2);

	if (max1 < max2)
		__outputCount(m1);
	else
		__outputCount(m2);

	system("PAUSE");
	return EXIT_SUCCESS;
}
