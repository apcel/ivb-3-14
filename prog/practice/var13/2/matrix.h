#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <vector>
#include <map>
#include <exception>
#include <algorithm>
#include <ostream>
#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <fstream>

template<typename _Type>
class Matrix {
private:
    typedef std::vector<_Type>      MatrixLine;
    typedef std::vector<MatrixLine> MatrixValue;
    MatrixValue _value;
public:
    Matrix(int rows, int cols, _Type def)  // конструктор
    {
        clear(rows, cols, def);
    }

    void loadFromFile(std::string file); //загрузка матрицы из файла
    void saveToFile(std::string file); //запись матрицы в файл
    void readFromKeyboard(); //чтение матрицы с клавиатуры

    void clear(int rows, int cols, _Type def); //очистка памяти матрицы

    Matrix operator+(const Matrix &that); // оператор сложения матриц
    Matrix operator-(const Matrix &that); //оператор вычитания матриц
    Matrix operator*(_Type number); // оператор умножения матрицы на число
    Matrix operator*(const Matrix &that); //оператор перемножения матриц

    int getRowCount() const; // получить количество строк
    int getColCount() const; //получить количество столбцов
    Matrix<_Type> transponse(); //транспонирование матрицы


    _Type get(int row, int col) const; // получить значение элемента матрицы
    void put(int row, int col, _Type value); // присвоить значение элементу матрицы


    int individualFind();

private:
    template<typename U> friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& m);
    bool isCorrect(int colFirst, int rowFirst, int sizeS);
};



#endif /** _MATRIX_H_ */