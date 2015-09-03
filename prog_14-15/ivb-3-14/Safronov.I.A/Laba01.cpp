#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MATRIX1 4
#define MATRIX2 3
#define MATRIX3 8

static double m1[] = { 13., 2., 15., 8. };

static double m2[] = { 1., 1., 1. };

static double m3[] = { 3., 9., 6., 12., 15., 18., 21., 24. };

static double
calculate (double matrix[], int elements, const double part)
{
	double result = 0;
	int i;
	int n = 0;

	for (i = 0; i < elements; ++i) {
		if (matrix[i] < part) {
			result += matrix[i];
			n++;
		}
	}

	return result == 0|| n ==0 ? 0: result / n;
}

int
main(int argc, char **argv)
{
	const double part = 5.;
	double mr1 = calculate(m1, MATRIX1, part);
	double mr2 = calculate(m2, MATRIX2, part);
	double mr3 = calculate(m3, sizeof(m3)/sizeof(m3[0]), part);
	
	fprintf(stdout, "%f\n", mr1>mr2?mr1>mr3?mr1:mr3:mr2 );

	if (mr1 == mr2)
		fprintf(stdout, "Matrix1 == Matrix2\n");
	if (mr1 == mr3)
		fprintf(stdout, "Matrix1 == Matrix3\n");
	if (mr2 == mr3)
		fprintf(stdout, "Matrix2 == Matrix3\n");
	system("pause");
	return EXIT_SUCCESS;
}
