#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

typedef std::vector<std::vector<double>> matrix;

double
calculate(matrix mtx)
{
	double sa = 0;
	int count = 0;

	for(auto x = mtx.begin(); x < mtx.end(); x++) {
		for(auto y = x->begin(); y < x->end(); y++) {
			if ( *y > 0 ) {
				count++;
				sa += *y;
			}
		}
	}

	sa /= count;
	return sa;
}

void
galculate(matrix mtx)
{
	int i = 1;
	for(auto x = mtx.begin(); x < mtx.end(); x++, i++) {
		int raq = 0;
		for(auto y = x->begin(); y < x->end(); y++) {
			if ( *y < 0 )
				raq++;
		}
		printf("B %i строке %i отрицательных элементов\n", i, raq);
	}
}

void
print(matrix mtx)
{
	for(auto x = mtx.begin(); x < mtx.end(); x++) {
		for(auto y = x->begin(); y < x->end(); y++) {
			printf("%.1f ",  *y);
		}
		printf("\n");
	}
	printf("\n");
}

class NumberFromFileParser
{
	typedef std::vector<double>         __MatrixLine;
	typedef std::vector< __MatrixLine > __Matrix;
public:
	NumberFromFileParser()
		: _ch(0), _fd(0)
	{
	}
	~NumberFromFileParser()
	{
	}

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

	bool parse(std::string name, __Matrix &matrix)
	{
		std::vector<double> row;
		matrix.clear();
		if (_fd == 0)
			_fd = fopen(name.c_str(), "r");
		if (_fd == 0)
			return false;
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
		_fd = 0;
		return true;
	}
private:
	char                _ch;
	FILE               *_fd;
	std::string         _buffer;
};

int
main()
{
	setlocale (0, "Russian");
	
	matrix matrix1, matrix2;
	NumberFromFileParser parser;
	parser.parse(std::string("matrix1.txt"), matrix1);
	parser.parse(std::string("matrix2.txt"), matrix2);
	
	print(matrix1);
	print(matrix2);

	double m1 = calculate(matrix1);
	double m2 = calculate(matrix2);

	if (m1 > m2)
		galculate(matrix1);
	else
		galculate(matrix2);

	system("pause");
	return EXIT_SUCCESS;
}
