//вариант 7
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <clocale>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int i, j; /для циклов
    bool opt1 = false; //есть ли нули в матрицах
    bool opt2 = false;
    //Зададим размеры 2-х матриц
    const int N1 = 2;
    const int N2 = 3;
    const int M1 = 4;
    const int M2 = 5;
    int c1[N1]; //счетчик отрицательных элементов столбцов
    int c2[N2];
    //зададим 2 матрицы N1xM1 и N2xM2
    int m1[N1][M1];
    int m2[N2][M2];
    //рандомим числа от -3 до 3
    for(i = 0; i < N1; i++)
        for(j = 0; j < M1; j++)
            m1[i][j] = rand() % 6 - 3;
    for(i = 0; i < N2; i++)
        for(j = 0; j < M2; j++)
            m2[i][j] = rand() % 6 - 3;

    cout << "Матрица 1:" << endl;
    for(i = 0; i < N1; i++) {
        for(j = 0; j < M1; j++)
            cout << m1[i][j] << ' ';
        cout << endl;
    }

    cout << endl << "Матрица 2:" << endl;
    for(i = 0; i < N2; i++) {
        for(j = 0; j < M2; j++)
            cout << m2[i][j] << ' ';
        cout << endl;
    }
    //поиск нулей в массивах
    for(i = 0; i < N1; i++) {
        for(j = 0; j < M1; j++)
            if(m1[i][j] == 0) {
                opt1 = true;
                break;
            }
        if(opt1)
            break;
    }
    for(i = 0; i < N2; i++) {
        for(j = 0; j < M2; j++)
            if(m2[i][j] == 0) {
                opt2 = true;
                break;
            }
        if(opt2)
            break;
    }
    //находим количество отрицательных элементов в каждой строке 
    if(opt1) {
        cout << endl << "в первой матрице есть 0" << endl << endl;
        for(i = 0; i < N1; i++) {
            c1[i] = 0;
            for(j = 0; j < M1; j++)
                if(m1[i][j] < 0)
                    c1[i]++;
            cout << "количество отрицательных элеметнов в "<< i << "-й строке: " << c1[i] << endl;
        }
    }
    if(opt2) {
        cout << endl << "во второй матрице есть 0" << endl << endl;
        for(i = 0; i < N2; i++) {
            c2[i] = 0;
            for(j = 0; j < M2; j++)
                if(m2[i][j] < 0)
                    c2[i]++;
            cout << "количество отрицательных элементов в "<< i << "-й строке: " << c2[i] << endl;
        }
    }
    _getch();
}
