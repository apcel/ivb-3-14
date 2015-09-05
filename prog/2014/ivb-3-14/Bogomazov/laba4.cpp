#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>

/* Лаб. работа 4
 Вариант 6
 ИВБ-3-14
 Богомазов Степан */

void array_in(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        scanf("%d", &array[i]);
}
int sum_arr(int array[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        if (array[i] > 0)
            sum += array[i];
    }
    return sum;
}
int product_arr(int array[], int i_min, int i_max)
{
    if (i_min > i_max) {
        int temp = i_min;
        i_min = i_max;
        i_max = temp;
    }
    int product = 1;
    for (int i = i_min + 1; i < i_max; ++i) {
        product *= array[i];
    }
    return product;
}
int max_element(int array[], int size)
{
    int i_max = 0;
    int max = array[0];
    for (int i = 1; i < size; ++i) {
        if (array[i] > max) {
            max = array[i];
            i_max = i;
        }
    }
    return i_max;
}
int min_element(int array[], int size)
{
    int i_min = 0;
    int min = array[0];
    for (int i = 1; i < size; ++i) {
        if (array[i] < min) {
            min = array[i];
            i_min = i;
        }
    }
    return i_min;
}
int main(void)
{
    int size, sum, product;
    int array[100];
    printf("size = ");
    scanf("%d", &size);
    array_in(array, size);
    sum = sum_arr(array, size);
    product = product_arr(array, min_element(array, size), max_element(array, size));
    printf("sum = %d \n", sum);
    printf("product = %d \n", product);
    return 0;
}
