/*
Определить в каком массиве больше количество элементов, меньших заданного
числа. Если в двух или трёх массивах количества искомых элементов совпадают,
вывести соответствующее сообщение.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define len(a) sizeof(a)/sizeof(a[0])
#define max(a,b) a>b?a:b
#define number 2

double mt1[] = { 1.0, -5.0, -6.3, 8.0 };
double mt2[] = { 5.0, 3.9 };
double mt3[] = { 1.1, 5.6, -4.8, 8.2 };

static int Calculate(double Array[], int size, int max)
{
    int count = 0;

    for (int i = 0; i < size; i++){
        if (Array[i] < max)
            count++;
    }

    return count;
}

void main(int argc, char **argv)
{
    setlocale(LC_ALL, "Russian");
    int s1 = Calculate(mt1, len(mt1), number);
    int s2 = Calculate(mt2, len(mt2), number);
    int s3 = Calculate(mt3, len(mt3), number);

    int min_value = max(max(s1, s2), s3);

    printf("В масиве");
    if (min_value == s1)
        printf(" 1");
    if (min_value == s2)
        printf(" 2");
    if (min_value == s3)
        printf(" 3");

    printf(" количество элементов, меньших %i максимально.\n", number);
    system("pause");
}
