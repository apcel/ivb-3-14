//Вариант 7  
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <clocale>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian"); //для русского языка
    //зададим диапазон значений [-30; 15]
    const int min = -30;
    const int max = 15;
    cout << "Диапазон: " << '(' << min << ';' << max << ")\n\n";
    //создадим 3 массива размерностью 100 и рандомными числами(-50;50)
    const int SIZE = 100;
    int a1[SIZE];
    int a2[SIZE];
    int a3[SIZE];
    int i = 0; //для циклов
    int s[3] = {0, 0, 0}; //суммы элементов 3-х массивов
    int min_s;
    for(int i = 0; i < SIZE; i++) {
        //randomize();
        a1[i] = rand()%100 - 50;
        a2[i] = rand()%100 - 50;
        a3[i] = rand()%100 - 50;
    }
    cout << "Массив 1: ";
    for(i = 0; i < SIZE; i++)
        cout << a1[i] << ' ';
    cout << endl << "Массив 2: ";
    for(i = 0; i < SIZE; i++)
        cout << a2[i] << ' ';
    cout << endl << "Массив 3: ";
    for(i = 0; i < SIZE; i++)
        cout << a3[i] << ' ';
    cout << endl;

    for(i = 0; i < SIZE; i++) {
        if(a1[i] < min || a1[i] > max)
            s[0] += a1[i];
        if(a2[i] < min || a2[i] > max)
            s[1] += a2[i];
        if(a3[i] < min || a3[i] > max)
            s[2] += a3[i];
    }
    cout << endl;
    for(i = 0; i < 3; i++)
        cout << "Значение суммы " << i+1 << ": "<< s[i] << endl;
    cout << endl;
    min_s = s[0];
    for( i = 1; i < 3; i++)
        if(s[i] < min_s)
            min_s = s[i];
    cout << "Минимальная сумма элементов заданного диапазона: " << min_s << endl;
    cout << "Минимальная сумма в массиве: ";
    for(i = 0; i < 3; i++)
        if(min_s == s[i])
            cout << i + 1 << ' ';
    cout << endl;
    _getch();
}
