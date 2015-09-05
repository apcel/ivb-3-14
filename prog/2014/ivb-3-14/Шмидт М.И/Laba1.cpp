#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

/* Лаб. работа 1
 Вариант 23
 ИВБ-3-14
 Шмидт Максим */

#define TargetNumber 7
#define len(a) sizeof(a)/sizeof(a[0])
#define min(a,b) a<b?a:b


double mt1[] = { 1.0, 4.9, 3.7, 7.0 };
double mt2[] = { 3.2, 5.0 };
double mt3[] = { 1.1, 5.3, 4.2, 8.6 };

static int Calculate(double Array[], int size)
{
    int result = 0;
    
    for (int i = 0; i < size; i++)
        if (Array[i] > TargetNumber)
            result++;
    
    return result;
}

int
main(int argc, char **argv)
{
    setlocale(0, "");
    int s1 = Calculate(mt1, len(mt1));
    int s2 = Calculate(mt2, len(mt2));
    int s3 = Calculate(mt3, len(mt3));
    
    int min_value = min(min(s1,s2),s3);
    
    printf("Минимальное значение %i содержится в:\n", min_value);
    if (min_value == s1)
        printf(" mt1");
    if (min_value == s2)
        printf(" mt2");
    if (min_value == s3)
        printf(" mt3");
    
    printf("\n");
}
