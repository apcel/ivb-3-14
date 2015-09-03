/*

10  ���� ��� ������� ������� �������. ��� ��� �� ������, � ������� ������ ����������
������� ���������, ����� ����������� ������� � ������ ������.

*/

#pragma warning(disable: 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

static double** __loadMatrix(
	const char* const szFileName,
	int* piRows,
	int* piCols);

static void __destroyMatrix(double** pMatrix, int rows, int cols);

static int __exception(const char* const szMessage)
{
	fprintf(stderr, "%s\n", szMessage);
	return EXIT_FAILURE;
}

static void __printMatrix(double** pMatrix, int rows, int cols);
static int __findMaxElement(double** pMatrix, int rows, int cols);
static void __outputMaxElements(double** pMatrix, int rows, int cols);



#include <string>
#include <vector>

template <typename T>
class NumberFromFileParser
{
	typedef std::vector<T> __MatrixLine;
	typedef std::vector<__MatrixLine > __Matrix;

	friend T**
		__loadMatrix(
		const char* const szFileName,
		int* piRows,
		int* piCols);
public:
	NumberFromFileParser() :_ch(0), _fd(nullptr) {}
	~NumberFromFileParser() {}

	bool eof() const
	{
		return feof(_fd) > 0;
	}

	bool next()
	{
		_ch = fgetc(_fd);
		return _ch != EOF;
	}

	bool isWhiteSpace() const
	{
		return isspace((int)_ch) > 0;
	}

	bool isDigit() const
	{
		return isdigit((int)_ch) > 0;
	}

	bool isDot() const
	{
		return _ch == '.' || _ch == ',';
	}

	bool isSign() const
	{
		return _ch == '+' || _ch == '-';
	}

	bool isEndOfLine() const
	{
		return _ch == '\r' || _ch == '\n';
	}

	void skipWhiteSpace()
	{
		while (!eof() && isWhiteSpace() && next());
	}

	void skipEndOfLine()
	{
		while (!eof() && isEndOfLine() && next());
	}

	void parseNumber() {
		skipWhiteSpace();
		while (!eof() && !isWhiteSpace() &&
			(isSign() || isDot() || isDigit())) {
			put();
			next();
		}
	}

	void put()
	{
		_buffer.push_back(_ch);
	}

	__Matrix parse(const char* const name)//, __Matrix &matrix)
	{
		__Matrix matrix;
		std::vector<T> row;
		matrix.clear();
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
private:
	char _ch;
	FILE *_fd;
	std::string _buffer;
};

/*double** __loadMatrix(
	const char* const szFileName,
	int* piRows,
	int* piCols)
{
	NumberFromFileParser<double> parser;
	auto retval = parser.parse(szFileName, matrix);
	if (retval) {
		(*piRows) = matrix.size();
		double** result = new double*[matrix.size()];
		for (
			NumberFromFileParser::__MatrixLine::size_type k = 0;
			k < matrix.size();
		k++) {
			NumberFromFileParser::__MatrixLine line = matrix.at(k);
			result[k] = new double[line.size()];
			(*piCols) = line.size();
			for (
				NumberFromFileParser::__Matrix::size_type i = 0;
				i < line.size();
			i++) {
				result[k][i] = line.at(i);
			}
		}
		return result;
	}
	return nullptr;
}*/

void
__destroyMatrix(double **pMatrix, int rows, int cols)
{
	if (pMatrix != nullptr) {
		for (auto i = 0; i < rows; i++) {
			if (pMatrix[i] != nullptr)
				delete[] pMatrix[i];
		}
		delete[] pMatrix;
	}
}

void
__printMatrix(std::vector<std::vector<double>> matrix)
{
	for (auto i = matrix.begin(); i < matrix.end(); ++i) {
		for (auto j = i->begin(); j < i->end(); j++) {
			fprintf(stdout, "%3.5f ", *j);

		}
		fprintf(stdout, "\n");
	}
}

int
__findMaxElement(std::vector<std::vector<double>> matrix)
{
	int result = 0;
	for (auto i = matrix.begin(); i < matrix.end(); ++i) {
		for (auto j = i->begin(); j < i->end(); ++j) {
			if (*j == 0.0)
				result++;
		}
	}
	return result;
}

void
__outputMaxElements(std::vector<std::vector<double>> matrix)
{
	for (auto i = matrix.begin(); i < matrix.end(); ++i) {
		double min = (*i).front();
		for (auto j = i->begin(); j < i->end(); ++j) {
			if (*j < min)
				min = *j;
		}
		fprintf(stdout, "%3.5f\n", min);
	}
}


int main(int argc, char** argv)
{

	if (argc < 3) {
		return __exception("Not found input file");
	}

	NumberFromFileParser<double> parser;
	auto m1 = parser.parse(argv[1]);
	auto m2 = parser.parse(argv[2]);
	fprintf(stdout, "Matrix N1:\n");
	__printMatrix(m1);
	fprintf(stdout, "Matrix N2:\n");
	__printMatrix(m2);
	double max1 = __findMaxElement(m1);
	double max2 = __findMaxElement(m2);
	if (max1 < max2) {
		fprintf(stdout, "Output matrix N1:\n");
		__outputMaxElements(m1);
	} else {
		fprintf(stdout, "Output matrix N2:\n");
		__outputMaxElements(m2);
	}
	/*
	
	__printMatrix(matrix1, mRows1, mCols1);
	;
	__printMatrix(matrix2, mRows2, mCols2);

	double max1 = __findMaxElement(matrix1, mRows1, mCols1);
	double max2 = __findMaxElement(matrix2, mRows2, mCols2);

	if (max1 < max2) {
	fprintf(stdout, "Output matrix N1:\n");
	__outputMaxElements(matrix1, mRows1, mCols1);
	}
	else {
	fprintf(stdout, "Output matrix N2:\n");
	__outputMaxElements(matrix2, mRows2, mCols2);
	}
	__destroyMatrix(matrix1, mRows1, mCols1);
	__destroyMatrix(matrix2, mRows2, mCols2);*/
	system("pause");
	return EXIT_SUCCESS;
}