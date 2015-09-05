#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>

/* Лабораторная работа №1
	* Вариант 16
	* ИВБ-3-14
	* Панасенко Андрей
Определить в каком массиве меньше сумма элементов, попадающих в заданный диапазон.
Если в двух или трех массивах  суммы совпадают, вывести соответствующее сообщение.*/

#define MATRIX1 4
#define MATRIX2 2
#define MATRIX3 6

static double m1[] = { 1., 1., 1., 1. };

static double m2[] = { 1., 1. };

static double m3[] = { 4., 4., 4., 4., 4., 4. };

static double
calculate(double matrix[], int elements, const double part)
{
	double result = 0;
	int i;
	for (i = 0; i < elements; i++) {
		if (matrix[i] < part) {
			result += matrix[i];
		}
	}
	return result;
}
 void min_mr(double mr1, double mr2, double mr3)
{
	 if (mr1 == mr2)
		 fprintf(stdout, "Matrix1 == Matrix2\n");
	 if (mr2 == mr3)
		 fprintf(stdout, "Matrix2 == Matrix3\n");
	 if (mr1 == mr3)
		 fprintf(stdout, "Matrix1 == Matrix3\n");
}
int main(int argc, char **argv)
{
	const double part = 4.;
	double mr1 = calculate(m1, MATRIX1, part);
	double mr2 = calculate(m2, MATRIX2, part);
	double mr3 = calculate(m3, MATRIX3, part);
	min_mr(mr1, mr2, mr3);
	system("pause");
	return EXIT_SUCCESS;
}
