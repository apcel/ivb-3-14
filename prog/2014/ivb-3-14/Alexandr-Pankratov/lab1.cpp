// 17 вариант
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define TrgetNumber1 -8
#define TrgetNumber2 4

#define len(a) sizeof(a)/sizeof(a[0])
#define max(a,b) a>b?a:b

double mt1[] = {1.0, -5.0, -6.3, 8.0};
double mt2[] = {5.0, 3.9};
double mt3[] = {1.1, 5.6, -4.8, 8.2};

static int Calculate(double Array[], int size)
{
	int result = 0;

	for(int i = 0; i < size; i++)
		if(Array[i] > TrgetNumber1 && Array[i] < TrgetNumber2)
			result++;

	return result;
}

void main(int argc, char **argv)
{
	setlocale(0, "");
	int s1 = Calculate(mt1, len(mt1));
	int s2 = Calculate(mt2, len(mt2));
	int s3 = Calculate(mt3, len(mt3));

	int u = max(max(s1,s2),s3);
		
	printf("Больше сумма элементов, не попадающих в заданный диапазон [%i; %i] содержится в:\n", TrgetNumber1, TrgetNumber2);
	if(u==s1)
		printf(" mt1");
	if(u==s2)
		printf(" mt2");
	if(u==s3)
		printf(" mt3");

	printf("\n");
	system("pause");
}
