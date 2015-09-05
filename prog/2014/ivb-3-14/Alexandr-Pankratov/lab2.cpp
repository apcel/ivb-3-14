// 17 вариант
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

static double ** __loadMatrix( const char * const szFileName,  int * piRows, int * piCols);

static int __exception(const char * const szMessage)
{
	fprintf(stderr, "%s\n", szMessage);
	return EXIT_FAILURE;
}

static void __printMatrix(double **pMatrix, int rows, int cols);
static int __calculate(double **pMatrix, int rows, int cols);
static void __Count(double **pMatrix, int rows, int cols);
static void __destroyMatrix(double **pMatrix, int rows, int cols);

/*=======================================================================================*/

int main(int argc, char **argv)
{
	if (argc < 3)
		return __exception("Not found input file");

	setlocale(0, "Russian");
	int  mRows1,mCols1,mRows2,mCols2,mtx1,mtx2 = 0;
	
	double ** matrix1 = __loadMatrix(argv[1], &mRows1, &mCols1);
	double ** matrix2 = __loadMatrix(argv[2], &mRows2, &mCols2);

	fprintf(stdout, "Матрица 1:\n");
	__printMatrix(matrix1, mRows1, mCols1);
	fprintf(stdout, "Матрица 2:\n");
	__printMatrix(matrix2, mRows2, mCols2);
	
	mtx1 = __calculate(matrix1, mRows1, mCols1);
	mtx2 = __calculate(matrix2, mRows2, mCols2);

	if (mtx1 < mtx2) {
		printf("Среднее арифметическое положительных элементов 1 матрици меньше.\n");
		__Count(matrix1, mRows1, mCols1);
	} else {
		printf("Среднее арифметическое положительных элементов 2 матрици меньше.\n");
		__Count(matrix2, mRows2, mCols2);
	}
	
	__destroyMatrix(matrix1, mRows1, mCols1);
	__destroyMatrix(matrix2, mRows2, mCols2);

	system("pause");
	return EXIT_SUCCESS;
}

void __printMatrix(double **pMatrix, int rows, int cols)
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

int __calculate(double **pMatrix, int rows, int cols)
{
	int n = 0, c = 0;
	for (int i = 0; i < rows; ++i) 
	{
		for (int j = 0; j < cols; ++j)
		{
			if (pMatrix[i][j] > 0)
			{
				n+=pMatrix[i][j];
				c++;
			}
		}
	}

	if (c==0)
		return 0;
	return n/c;
}

void __Count(double **pMatrix, int rows, int cols)
{
	for (int i = 0; i < rows; ++i) 
	{
		int n = 0;
		for (int j = 0; j < cols; ++j)
		{
			if (pMatrix[i][j] < 0)
				n++;
		}
		printf("\t%i строка ", i+1);
		if(n==0)
			printf("не содержит отрицательных элементов.\n");
		else
			printf("содержит %i отрицательных элемента.\n", n);
	}
}

void __destroyMatrix(double **pMatrix, int rows, int cols)
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
