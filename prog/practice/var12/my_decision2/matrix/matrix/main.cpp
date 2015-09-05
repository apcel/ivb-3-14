#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include "matrix.h"
using namespace std;

void  // проверка на симметричность
__test_isSymmetric()
{
	Matrix<int> m(4, 4, 0);

	std::cout << "Матрица: " << std::endl << m;
	std::cout << "Симметрична: " << (m.isSymmetric() ? "Нет" : "Да") << std::endl << std::endl;
}

void //сложение матриц
__test_operatorPlus()
{
	Matrix<int> a(3, 3, 2);
	Matrix<int> b(3, 3, 3);
	std::cout << "Матрица A:" << std::endl << a;
	std::cout << "Матрица B:" << std::endl << b;
	std::cout << "Матрица A+B:" << std::endl << a + b << std::endl;
}

void // вычитание матриц
__test_operatorMinus()
{
	Matrix<int> a(3, 3, 2);
	Matrix<int> b(3, 3, 3);
	std::cout << "Матрица A:" << std::endl << a;
	std::cout << "Матрица B:" << std::endl << b;
	std::cout << "Матрица A-B:" << std::endl << a - b << std::endl;
}
void //обратная матрица
__test_invert()
{
	Matrix <int> m(3, 3, 0);
	m.put(0, 0, 5);
	m.put(1, 1, 3);
	m.put(2, 2, 2);
	std::cout << m.invert() << std::endl;

}
void //транспонирование матрицы
__test_transposition()
{
	Matrix <int> a(8, 4, 1);
	a.put(5, 1, 2);
	a.put(2, 3, 1);
	a.put(2, 2, 2);
	std::cout << "Матрица: " << std::endl << a << std::endl;
	std::cout << "Transp.: " << std::endl << a.transposition() << std::endl;
}

void //определитель матрицы
__test_determinant()
{
	Matrix <int> a(3, 3, 0);
	a.put(0, 0, 5);
	a.put(1, 1, 3);
	a.put(2, 2, 2);
	std::cout << "Матрица A:" << std::endl << a;
	std::cout << "det(A)=" << a.determinant() << std::endl;
}

void //минор матрицы
__test_isMinor()
{
	Matrix <int> m(4, 4, 0);
	for (int i = 0, i2 = 0; i < m.getRowCount(); i++, i2++) {
		for (int j = 0, j2 = 0; j < m.getColCount(); j++, j2++) {
			m.put(i2, j2, m.get(i, j));
		}
	}

	int row = 3, col = 3;
	std::cout << "Матрица: " << std::endl << m;
	std::cout << "Минор (" << row << "," << col << ") = " << m.minor(row, col) << std::endl << std::endl;
}

void //переумножение матриц
__test_operatorUMN()
{
	Matrix<int> a(3, 3, 2);
	Matrix<int> b(2, 2, 3);
	std::cout << "Матрица A:" << std::endl << a;
	std::cout << "Матрица B:" << std::endl << b;
	std::cout << "Матрица A*B:" << std::endl << a*b << std::endl;
}

void //сравнение матриц
__test_equality()
{
	Matrix<int> a(3, 3, 3);
	Matrix<int> b(3, 3, 2);
	std::cout << "Матрица A:" << std::endl << a;
	std::cout << "Матрица B:" << std::endl << b << std::endl;
	std::cout << "A=B ?  " << (a == b ? "Да" : "Нет") << std::endl;
	std::cout << "A!=B ?  " << (a != b ? "Да" : "Нет") << std::endl;
	std::cout << "A>=B ?  " << (a >= b ? "Да" : "Нет") << std::endl;
	std::cout << "A<=B ?  " << (a <= b ? "Да" : "Нет") << std::endl << std::endl;
}
void //загрузка матрицы из файкла
__test_LoadByFile()
{
	Matrix <int> m(3, 3, 0);
	m.LoadByFile("matrix2.txt");
}

void //запись матрицы в файл
__test_SaveFile()
{
	Matrix <int> m(3, 3, 0);
	m.SaveFile("matrix2.txt");
}

void // Дана матрица размером n*m. Найти первый столбец с минимальным элементом и отсортировать строки матрицы по неубыванию значений элементов найденного столбца.
__test_minCol()
{
	Matrix<int> m(5, 4, 0);
	cout << "Индивидуальное задание (вариант №14):" << endl;
	for (int i = 0; i < m.getRowCount(); i++) {
		for (int j = 0; j < m.getColCount(); j++) {
			m.put(i, j, rand() % 100 - 50);
		}
	}
	cout << m << endl << "---" << endl << m.minCol() << endl;
}

int //главная ф-ция (меню)
main(int argc, char **argv)
{
	setlocale(0, "Russian");
	char key;
	cout << "Меню:\n1)ввод матрицы с клавиатуры\n2)сложение матриц\n3)вычитание матриц\n4)умножение матриц\n5)транспонирование матрицы\n6)Индивидуальное задание(вариант №14):\n'q' для выхода\n";
	cin >> key;
	while (key != 'q')
	{
		switch (key)
		{
		case '1':
			cout << "\nВаша матрица: \n" << Matrix<int>::ReadKeyboard() << endl;
			break;
		case '2':
			cout << "\nВвод матрицы из файла..." << endl;
			cout << "Вывод матриц в файл..." << endl;
			__test_operatorPlus();
			break;
		case '3':
			cout << "\nВвод матрицы из файла..." << endl;
			cout << "Вывод матриц в файл..." << endl;
			__test_operatorMinus();
			break;
		case '4':
			cout << "\nВвод матрицы из файла..." << endl;
			cout << "Вывод матриц в файл..." << endl;
			__test_operatorUMN();
			break;
		case '5':
			cout << "\nВвод матрицы из файла..." << endl;
			cout << "Вывод матриц в файл..." << endl;
			__test_transposition();
			break;
		case '6':
			cout << "\nВвод матрицы из файла..." << endl;
			cout << "Вывод матриц в файл..." << endl;
			__test_minCol();
			break;
		}
		system("pause");
		system("cls");
		cout << "Меню:\n1)ввод матрицы с клавиатуры\n2)сложение матриц\n3)вычитание матриц\n4)умножение матриц\n5)транспонирование матрицы\n6)Индивидуальное задание(вариант №14):\n'q' для выхода\n";
		cin >> key;
	}

	//__test_isSymmetric();
	//__test_operatorPlus();
	//__test_operatorMinus();
	//__test_determinant();
	//__test_isMinor();
	//__test_operatorUMN();
	//__test_equality();
	//__test_transposition();
	//__test_minCol();
	//__test_LoadByFile();
	//__test_SaveFile();
	system("pause");
	return EXIT_SUCCESS;
}
