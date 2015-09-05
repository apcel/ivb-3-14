/*
* Лаба №1
* ИВБ-3-14
* Фоломкин Антон
* 15 вариант
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define TrgetNumber 4
#define len(a) sizeof(a)/sizeof(a[0])
#define max(a,b) a>b?a:b

double mt1[] = { 1.0, 5.0, 6.3, 8.0 };
double mt2[] = { 5.0, 4.0 };
double mt3[] = { 1.1, 5.6, 4.8, 8.2 };

static double Calculate(double matrix[], int elements, const double part)
{
	double result = 0;
	int n = 0;

	for (int i = 0; i < elements; ++i) {
		if ((matrix[i] < part) && (matrix[i]> result)) {
			result = Matrix[i];
			++n;
		}
	}
	return result;
}

void main(int argc, char **argv)
{
	setlocale(0, "Russian");
	double s1 = Calculate(mt1, len(mt1));
	double s2 = Calculate(mt2, len(mt2));
	double s3 = Calculate(mt3, len(mt3));

	double max_value = max(max(s1, s2), s3);

	printf("Максимальное значение %0.1lf содержится в:\n", s1);
	if (max_value == s1)
		printf(" mt1", s1);
	if (max_value == s2)
		printf(" mt2", s1);
	if (max_value == s3)
		printf(" mt3", s1);

	printf("\n");
}