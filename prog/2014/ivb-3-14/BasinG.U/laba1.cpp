/*
	04 ќпределить в каком массиве больше минимум элементов, больших заданного
	числа. ≈сли в двух или трЄх массивах минимумы совпадают, вывести соответствующее
	сообщение.
*/
#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MATRIX1 4
#define MATRIX2 2
#define MATRIX3 6

static double m1[] = { 1., 1., 1., 1. };

static double m2[] = { 1., 1. };

static double m3[] = { 4., 4., 4., 4., 4., 4. };

static int 
calculate(double matrix[], int elements, const double part)
{
	int i;
	int n = 0;

	for (i = 0; i < elements; ++i) {
		if (matrix[i] > part) {
			++n;
		}
	}
	return n;
}

int
main(int argc, char **argv)
{
	const double part = 2;
	int mr1 = calculate(m1, MATRIX1, part);
	int mr2 = calculate(m2, MATRIX2, part);
	int mr3 = calculate(m3, sizeof(m3)/sizeof(m3[0]), part);

	if (mr1 == mr2)
		fprintf(stdout, "Matrix1 == Matrix2\n");
	if (mr1 == mr3)
		fprintf(stdout, "Matrix1 == Matrix3\n");
	if (mr2 == mr3)
		fprintf(stdout, "Matrix2 == Matrix3\n");
	system("pause");
	return EXIT_SUCCESS;
}