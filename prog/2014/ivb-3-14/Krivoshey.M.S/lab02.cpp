#include <cstdio>
#include <cstdlib>
#include <cstring>

/*
	* Лаба №2
	* ИВБ-3-14
	* Кривошея Михаил
	* 12 вариант
		Даны две матрицы разного размера. Для той из матриц, в которой меньше
		количество нулевых элементов, найти количество отрицательных элементов
		в каждой строке.
*/

static double ** __loadMatrix( const char * const szFileName,  int * piRows, int * piCols);

static int __exception(const char * const szMessage)
{
	fprintf(stderr, "%s\n", szMessage);
	return EXIT_FAILURE;
}

static void PrintMatrix(double **pMatrix, int rows, int cols);
static void DestroyMatrix(double **pMatrix, int rows, int cols);
static int GetCount(double **pMatrix, int rows, int cols, bool findZeroElement);

/*=======================================================================================*/

int main(int argc, char **argv)
{
	if (argc < 3)
		return __exception("Not found input file");

	int	 mRows1 = 0,
		mCols1 = 0,
		mRows2 = 0,
		mCols2 = 0;

	double ** matrix1 = __loadMatrix(argv[1], &mRows1, &mCols1);
	double ** matrix2 = __loadMatrix(argv[2], &mRows2, &mCols2);

	fprintf(stdout, "Matrix N1:\n");
	PrintMatrix(matrix1, mRows1, mCols1);
	fprintf(stdout, "Matrix N2:\n");
	PrintMatrix(matrix2, mRows2, mCols2);

	int zeroCount1 = GetCount(matrix1, mRows1, mCols1, true);
	int zeroCount2 = GetCount(matrix2, mRows2, mCols2, true);

	if (zeroCount1 < zeroCount2)
		fprintf(stdout, "Output matrix N1: %i\n", GetCount(matrix1, mRows1, mCols1, false));
	else
		fprintf(stdout, "Output matrix N2: %i\n", GetCount(matrix2, mRows2, mCols2, false));

	DestroyMatrix(matrix1, mRows1, mCols1);
	DestroyMatrix(matrix2, mRows2, mCols2);

	system("pause");
	return EXIT_SUCCESS;
}

void PrintMatrix(double **pMatrix, int rows, int cols)
{
	for (auto i = 0; i < rows; ++i) {
		for (auto j = 0; j < cols; ++j) {
			if (j > 0)
				fprintf(stdout, " ");
			fprintf(stdout, "%3.1f\t", pMatrix[i][j]);
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");
}

int GetCount(double **pMatrix, int rows, int cols, bool findZeroElement)
{
	int result = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if(	(findZeroElement&&pMatrix[i][j] == 0)||
				(!findZeroElement&&pMatrix[i][j] < 0))
					result++;
		}
	}
	return result;
}

void DestroyMatrix(double **pMatrix, int rows, int cols)
{
	if (pMatrix != nullptr) {
		for (int i = 0; i < rows; i++) {
			if (pMatrix[i] != nullptr)
				delete[] pMatrix[i];
		}
		delete[] pMatrix;
	}
}

/*=======================================================================================*/

#include <string>
#include <vector>

class NumberFromFileParser
{
	typedef std::vector<double>         __MatrixLine;
	typedef std::vector< __MatrixLine > __Matrix;

	friend double **
		__loadMatrix(
		const char * const szFileName, 
		int * piRows, 
		int * piCols);
public:
	NumberFromFileParser()
		: _ch(0), _fd(nullptr)
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

	bool parse(const char * const  name, __Matrix &matrix)
	{
		std::vector<double> row;
		matrix.clear();
		if (_fd == nullptr)
			_fd = fopen(name, "r");
		if (_fd == nullptr)
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
		_fd = nullptr;
		return true;
	}
private:
	char                _ch;
	FILE               *_fd;
	std::string         _buffer;
};

double **
	__loadMatrix(
	const char * const szFileName, 
	int * piRows, 
	int * piCols)
{
	NumberFromFileParser parser;
	NumberFromFileParser::__Matrix matrix;
	auto retval = parser.parse(szFileName, matrix);
	if (retval) {		
		(*piRows) = matrix.size();
		double **result = new double * [matrix.size()];
		for (
			NumberFromFileParser::__MatrixLine::size_type k = 0; 
			k < matrix.size(); 
		k++) {
			NumberFromFileParser::__MatrixLine line = matrix.at(k);
			result[k] = new double [line.size()];
			(*piCols) = line.size();
			for (
				NumberFromFileParser::__Matrix::size_type i = 0; 
				i < line.size(); 
			++i) {
				result[k][i] = line.at(i);
			}
		}
		return result;
	}
	return nullptr;
}
