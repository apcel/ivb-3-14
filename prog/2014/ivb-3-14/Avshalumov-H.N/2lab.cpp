/*
Даны две матрицы разного размера. Для той из матриц, в которой больше
максимальный элемент, найти количество положительных элементов в каждой
строке.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <locale.h>

static double ** __loadMatrix(const char * const szFileName, int * piRows, int * piCols);

static int __exception(const char * const szMessage)
{
    fprintf(stderr, "%s\n", szMessage);
    return EXIT_FAILURE;
}

static void PrintMatrix(double **pMatrix, int rows, int cols);
static void DestroyMatrix(double **pMatrix, int rows, int cols);
static int GetMax(double **pMatrix, int rows, int cols);
static int GetCount(double **pMatrix, int rows, int cols);

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "Russian");
    if (argc < 3)
        return __exception("Not found input file");

    int mRows1 = 0, mCols1 = 0, mRows2 = 0, mCols2 = 0, mRows, mCols;

    double ** matrix1 = __loadMatrix(argv[1], &mRows1, &mCols1);
    double ** matrix2 = __loadMatrix(argv[2], &mRows2, &mCols2);
    double ** matrix;

    printf("Matrix N1:\n");
    PrintMatrix(matrix1, mRows1, mCols1);
    printf("Matrix N2:\n");
    PrintMatrix(matrix2, mRows2, mCols2);

    int max1 = GetMax(matrix1, mRows1, mCols1);
    int max2 = GetMax(matrix2, mRows2, mCols2);

    if (max1 > max2){
        matrix = matrix1;
        mRows = mRows1;
        mCols = mCols1;
        printf("\nМаксимальный элемен 1 матрици больше максимального элеманта во 2 матрици\n\n");
    }
    else{
        matrix = matrix2;
        mRows = mRows2;
        mCols = mCols2;
        printf("\nМаксимальный элемен 2 матрици больше максимального элеманта во 1 матрици\n\n");
    }

    for (int i = 0; i < mRows; i++)
    {
        printf("В %i строке %i неотрицательных элемент`а\n", i+1, GetCount(matrix, i, mCols));
    }

    DestroyMatrix(matrix1, mRows1, mCols1);
    DestroyMatrix(matrix2, mRows2, mCols2);

    system("pause");
    return EXIT_SUCCESS;
}

int GetMax(double **pMatrix, int rows, int cols)
{
    int m = 0;
    for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)
    if (pMatrix[i][j] >m)
        m = pMatrix[i][j];

    return m;
}

int GetCount(double **pMatrix, int rows, int cols)
{
    int m = 0;
    for (int j = 0; j < cols; ++j)
    if (pMatrix[rows][j] >= 0)
        m++;

    return m;
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
        double **result = new double *[matrix.size()];
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
            ++i) {
                result[k][i] = line.at(i);
            }
        }
        return result;
    }
    return nullptr;
}
