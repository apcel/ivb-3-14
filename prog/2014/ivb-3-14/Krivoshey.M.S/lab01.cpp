/*
	* Лаба №1
	* ИВБ-3-14
	* Кривошея Михаил
	* 12 вариант
		Определить в каком массиве меньше количество элементов, меньших заданного
		числа. Если в двух или трёх массивах количества искомых элементов совпадают,
		вывести соответствующее сообщение.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define TrgetNumber 4
#define len(a) sizeof(a)/sizeof(a[0])
#define min(a,b) a<b?a:b

double mt1[] = {1.0, -5.0, -6.3, 8.0};
double mt2[] = {5.0, 3.9};
double mt3[] = {1.1, 5.6, -4.8, 8.2};

static int Calculate(double Array[], int size)
{
	int result = 0;

	for(int i = 0; i < size; i++)
		if(Array[i] < TrgetNumber)
			result++;

	return result;
}

void main(int argc, char **argv)
{
	setlocale(0, "");
	int s1 = Calculate(mt1, len(mt1));
	int s2 = Calculate(mt2, len(mt2));
	int s3 = Calculate(mt3, len(mt3));

	int min_value = min(min(s1,s2),s3);
		
	printf("Минимальное значение %i содержится в:\n", min_value);
	if(min_value==s1)
		printf(" mt1");
	if(min_value==s2)
		printf(" mt2");
	if(min_value==s3)
		printf(" mt3");

	printf("\n");
}
