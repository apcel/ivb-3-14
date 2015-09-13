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
using namespace std;

template<typename _Type>
//#define _Type int
class Matrix {
	typedef std::vector<_Type>      MatrixLine;
	typedef std::vector<MatrixLine> MatrixValue;
	typedef Matrix MatrixT;

	MatrixValue _value;
public:
	Matrix(int rows, int cols, _Type def)  // конструктор
	{
		clear(rows, cols, def);
	}

	void LoadByFile(string file) //загрузка матрицы из файла
	{
		_value.clear();
		ifstream s = ifstream(file);
		string in;
		int len = 1;
		getline(s, in);
		for each (char c in in)
			if (c == ' ') len++;
		s.seekg(0);

		while (!s.eof())
		{
			MatrixLine line;
			for (int i = 0; i < len; i++){
				_Type h;
				s >> h;
				line.push_back(h);
			}
			_value.push_back(line);
		}
		s.close();
	}

	void SaveFile(string file) //запись матрицы в файл
	{
		ofstream s(file);
		for each (auto line in _value)
		{
			for (int i = 0; i < getColCount(); i++){
				s << line[i];
				if (i != getColCount() - 1)
					s << ' ';
			}
			s << endl;
		}
		s.close();
	}

	static MatrixT ReadKeyboard() //чтение матрицы с клавиатуры
	{
		int x, y;
		cout << "¬ведите размер м-ци:  (2 числа через пробел)\n";
		cin >> x >> y;
		MatrixT m(x, y, 0);
		for (int i = 0; i < x; i++) {
			cout << "¬ведите " << i + 1 << "строку (" << y << " чисел через пробел):\n";
			for (int j = 0; j < y; j++)
				cin >> m._value[i][j];
		}
		return m;
	}

	void clear(int rows, int cols, _Type def) //очистка пам€ти матрицы 
	{
		_value.clear();
		for (auto i = 0; i < rows; i++) {
			auto line = MatrixLine(cols);
			std::fill(line.begin(), line.end(), def);
			_value.push_back(line);
		}
	}

	bool operator==(const MatrixT &other) //оператор сравнени€ ==
	{
		for (int i = 0; i < getRowCount(); i++) {
			for (int j = 0; j < getColCount(); j++) {
				if (get(i, j) != other.get(i, j))
					return false;
			}
		}
		return true;
	}

	bool operator>=(const MatrixT &other) // оператор сравнени€ >=
	{
		return determinant() >= other.determinant();
	}

	bool operator<=(const MatrixT &other) // оператор сравнени€ <=
	{
		return determinant() <= other.determinant();
	}

	bool operator!=(const MatrixT &other) // оператор неравенства !=
	{
		return !operator==(other);
	}

	Matrix operator+(const MatrixT &that) // оператор сложени€ матриц
	{
		if (getRowCount() != that.getRowCount() ||
			getColCount() != that.getColCount()) {
			return *this;
		}

		Matrix result(getRowCount(), getColCount(), 0);
		for (int i = 0; i < getRowCount(); i++) {
			for (int j = 0; j < getColCount(); j++) {
				result.put(i, j, get(i, j) + that.get(i, j));
			}
		}
		return result;
	}

	Matrix operator-(const MatrixT &that) //оператор вычитани€ матриц
	{
		if (getRowCount() != that.getRowCount() ||
			getColCount() != that.getColCount()) {
			return *this;
		}

		Matrix result(getRowCount(), getColCount(), 0);
		for (int i = 0; i < getRowCount(); i++) {
			for (int j = 0; j < getColCount(); j++) {
				result.put(i, j, get(i, j) - that.get(i, j));
			}
		}
		return result;
	}


	Matrix operator*(_Type number) // оператор умножени€ матрицы на число
	{
		Matrix  result(getRowCount(), getColCount(), 0);

		for (int i = 0; i < getRowCount(); i++) {
			for (int j = 0; j < getColCount(); j++) {
				result.put(i, j, get(i, j) * number);
			}
		}
		return result;
	}

	Matrix operator*(const MatrixT &that) //оператор переумножени€ матриц
	{
		Matrix result(getRowCount(), that.getColCount(), 0);
		for (int i = 0; i < getRowCount(); i++) {
			int value = 0;
			for (int j = 0; j < that.getColCount(); j++) {
				for (int k = 0; k < getColCount(); k++)	{
					value += get(i, k) * that.get(k, j);
					result.put(i, j, value);
				}
				value = 0;
			}
		}
		return result;
	}

	Matrix invert() //обратна€ матрица
	{
		int size = getRowCount();
		if (size != getColCount()){
			return *this;

		}
		Matrix result(size, size, 0);
		_Type det = determinant();

		if (det == 0)
		{
			return *this;

		}
		_Type temp;
		bool _invert = false;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				temp = _invert ? 0 : 1;
				temp = minor(i, j);
				temp /= det;
				result.put(i, j, temp);
				_invert = !_invert;

			}

		}
		result = result.transposition();
		return result;
	}

	MatrixT speed()
	{
		return *this;
	}

	_Type determinant() const //определитель матрицы
	{
		_Type result = 0;
		int len = getRowCount();
		if (len == getColCount()) {
			int x;
			_Type line;
			for (int invert = 0; invert < 2; invert++){
				for (int offest = 0; offest < len; offest++) {
					line = 1;
					for (int i = 0; i < len; i++) {
						x = offest + i;
						if (invert){
							x = -x;
							while (x < 0)
								x += len;
						}
						else {
							while (x >= len)
								x -= len;
						}
						line *= get(x, i);
					}
					result += invert ? -line : line;
				}
			}
		}
		return result;
	}
	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	bool isDegenerate() const 
	{
		return false;
	}

	bool isSpeed() const
	{
		return false;
	}

	bool isIdentity() const
	{
		return false;
	}

	bool isTriangular() const
	{
		return false;
	}
	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	bool isSymmetric() const //проверка на симметричность матриц
	{
		int len = getRowCount();
		if (!len || len != getColCount())
			return false;

		for (int i = 0; i < len; i++) {
			for (int k = i + 1; k < len; k++) {
				if (get(i, k) != get(k, i))
					return false;
			}
		}
		return true;
	}

	int getRowCount() const // получить количество строк
	{
		return _value.size();
	}

	int getColCount() const //получить количество столбцов
	{
		if (_value.empty())
			return 0;
		return _value[0].size();
	}

	MatrixT transposition() //транспонирование матрицы
	{
		MatrixT mtx = MatrixT(getColCount(), getRowCount(), 0);
		for (int i = 0; i < getRowCount(); i++) {
			for (int j = 0; j < getColCount(); j++) {
				mtx.put(j, i, get(i, j));
			}
		}
		return mtx;
	}

	Matrix minCol() // ƒана матрица размером n*m. Ќайти первый столбец с минимальным элементом и отсортировать строки матрицы по неубыванию значений элементов найденного столбца.
	{
		MatrixT mtx = MatrixT(getRowCount(), getColCount(), 0);
		_Type min = get(0, 0);
		int jmin;

		for (int i = 0; i < getRowCount(); i++) {
			for (int j = 0; j < getColCount(); j++) {
				mtx.put(i, j, get(i, j));
				if (_value[i][j] < min) {
					min = _value[i][j];
					jmin = j;
				}
			}
		}
		for (int i = 0; i < getRowCount(); i++) {
			for (int m = 0; m < getRowCount() - i - 1; m++) {
				if (mtx.get(m, jmin) > mtx.get(m + 1, jmin))
				{
					MatrixLine t = mtx._value[m];
					mtx._value[m] = mtx._value[m + 1];
					mtx._value[m + 1] = t;
				}
			}
		}
		return mtx;
	}

	_Type minor(int row, int col) const // нахождение минора матрицы
	{
		Matrix  my(_value.size() - 1, _value.size() - 1, 0);

		for (int i = 0, i2 = 0; i < my._value.size(); i++, i2++) {
			for (int j = 0, j2 = 0; j < my._value.size(); j++, j2++) {
				if (i == row) i++;
				if (j == col) j++;
				my.put(i2, j2, _value[i][j]);
			}
		}
		return my.determinant();
	}

	_Type get(int row, int col) const // получить значение элемента матрицы
	{
		if ((unsigned int)row >= _value.size())
			return 0;
		auto line = _value[row];
		if ((unsigned int)col >= line.size())
			return 0;
		return line[col];
	}

	void put(int row, int col, _Type value) // присвоить значение элементу матрицы
	{
		if (row < _value.size()){
			auto line = _value[row];
			if (col < line.size())
				_value[row][col] = value;
		}
	}
private:
	template<typename U> friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& m);
};

template<typename _Type>
std::ostream &operator<<(std::ostream &output, const Matrix<_Type> &m) // оператор вывода матрицы
{
	if (m.getRowCount()) {
		for each (auto line in m._value) {
			for each (auto item in line)
				std::cout << item << ' ';
			std::cout << std::endl;
		}
	}
	return output;
}

#endif /** _MATRIX_H_ */