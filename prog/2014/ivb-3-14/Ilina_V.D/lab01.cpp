/*

10
Определить в каком массиве меньше среднее арифметическое элементов, меньших 
заданного числа. Если в двух или трех массивах значения среднего 
арифметического совпадают, вывести соответствующее сообщение.

*/

#pragma warning(disable: 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>

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
	int n = 0;

	for (i = 0; i < elements; ++i) {
		if (matrix[i] < part) {
			result += matrix[i];
			++n;
		}
	}
	return result == 0 || n == 0 ? 0 : result / n;
}

int
main(int argc, char **argv)
{
	const double part = 4.;
	double mr1 = calculate(m1, MATRIX1, part);
	double mr2 = calculate(m2, MATRIX2, part);
	double mr3 = calculate(m3, sizeof(m3) / sizeof(m3[0]), part);

	if (mr1 < mr2 && mr1 < mr3)
		fprintf(stdout, "Среднее арифметического для первого массива наименьшее.\n");
	if (mr2 < mr1 && mr2 < mr3)
		fprintf(stdout, "Среднее арифметического для второго массива наименьшее.\n");
	if (mr3 < mr1 && mr3 < mr2)
		fprintf(stdout, "Среднее арифметического для третьего массива наименьшее.\n");
	if (mr1 == mr2)
		fprintf(stdout, "Среднее арифметическое первого и второго массивов равны.\n");
	if (mr1 == mr3)
		fprintf(stdout, "Среднее арифметическое первого и третьего массивов равны.\n");
	if (mr2 == mr3)
		fprintf(stdout, "Среднее арифметическое второго и третьего массивов равны.\n");
	system("pause");
	return EXIT_SUCCESS;
}