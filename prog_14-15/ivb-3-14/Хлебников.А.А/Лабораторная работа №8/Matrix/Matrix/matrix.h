#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <vector>
#include <map>
#include <exception>
#include <algorithm>
#include <ostream>

class MatrixException : public std::exception {
	const char *_msg;
public:
	MatrixException(const char *msg)
		: _msg(msg)
	{}

	virtual const char* what() const throw()
	{
		return _msg;
	}
};

template<typename _Type>
class Matrix {
	typedef std::vector<_Type>      MatrixLine;
	typedef std::vector<MatrixLine> MatrixValue;

	MatrixValue _value;
public:
	Matrix(int rows, int cols, _Type def)
	{
		clear(rows, cols, def);
	}

	void clear(int rows, int cols, _Type def)
	{
		_value.clear();
		for (auto i = 0; i < rows; i++) {
			auto line = MatrixLine(cols);
			std::fill(line.begin(), line.end(), def);
			_value.push_back(line);
		}
	}

	/**Сравнение матриц. Вариант 1*/
	bool operator==(const Matrix<_Type> &other)
	{
		return false;
	}

	bool operator>=(const Matrix<_Type> &other)
	{
		return false;
	}

	bool operator<=(const Matrix<_Type> &other)
	{
		return false;
	}

	bool operator!=(const Matrix<_Type> &other)
	{
		return false;
	}


	/* Сложение матриц. Вариант 2 */
	/** Avshalumov H.N. **/
	Matrix<_Type> operator+(const Matrix<_Type> &that)
	{
		if (getRowCount() != that.getRowCount() ||
			getColCount() != that.getColCount()) {
			throw MatrixException("Invalid size");
			return *this;
		}

		Matrix<_Type> result(getRowCount(), getColCount(), 0);
		for (int i = 0; i < getRowCount(); i++) {
			for (int j = 0; j < getColCount(); j++) {
				result.put(i, j, get(i, j) + that.get(i, j));
			}
		}
		return result;
	}

	/** Вычитание матриц. Вариант 3*/
	/** Allyamov I.Z. **/
	Matrix<_Type> & operator-(const Matrix<_Type> &that)
	{
		if (getRowCount() != that.getRowCount() ||
			getColCount() != that.getColCount()) {
			throw MatrixException("Invalid size");
			return *this;
		}

		Matrix<_Type> result(getRowCount(), getColCount(), 0);
		for (int i = 0; i < getRowCount(); i++) {
			for (int j = 0; j < getColCount(); j++) {
				result.put(i, j, get(i, j) - that.get(i, j));
			}
		}
		return result;
	}

	/** Умножение на число. Вариант 4*/
	Matrix<_Type> & operator*(_Type number)
	{
		return *this;
	}

	/** Умножение матриц. Вариант 5 */
	/* Ilina V.D. */
	Matrix<_Type> & operator*(const Matrix<_Type> &that)
	{
		Matrix<_Type> result(getRowCount(), that.getColCount(), 0);
		for (int i = 0; i < getRowCount(); i++) {
			for (int j = 0; j < that.getColCount(); j++) {
				for (int k = 0; k < getColCount(); k++)	{
					int value = get(i, k) * that.get(k, j);
					result.put(i, j, value);
				}
			}
		}
	return result;
	}

	/** Возведение в степень. Вариант 6*/
	/* Korotkov D.A. */
	Matrix<_Type> & operator^(_Type number)
	{
		for (int n = 0; n <= number; n++) {
			for (int i = 0; i < getRowCount(); i++)	{
				for (int j = 0; j < getColCount(); j++)	{
					for (int k = 0; k < getColCount(); k++)	{
						int value = get (i, k) * get (k, i);
						this.put(i, j, value);
					}
				}
			}
		}
		return *this;
	}

	/** Транспониромание. Вариант 7 (2)*/
	Matrix<_Type> & transposition()
	{
		return *this;
	}

	/**Обратная матрица. Вариант 8 (2)*/
	Matrix<_Type> & invert()
	{
		return *this;
	}

	/**Ступенчатая матрица. Вариант 9 (2)*/
	Matrix<_Type> & speed()
	{
		return *this;
	}

	/**Определитель матрицы. Вариант 10 (2)*/
	/*Лавринович  Иван*/
	_Type determinant() const
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
						} else {
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

	/** Вырожденная. Вариант 11*/
	bool isDegenerate() const
	{
		return false;
	}

	/** Ступенчатая. Вариант 11*/
	bool isSpeed() const
	{
		return false;
	}

	/** Единичная. Вариант 11*/
	bool isIdentity() const
	{
		return false;
	}

	/** Треугольная. Вариант 11*/
	bool isTriangular() const
	{
		return false;
	}

	/** Симметричная. Вариант 12*/
	/**	Кривошея Михаил **/
	bool isSymmetric() const
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

	int getRowCount() const
	{
		return _value.size();
	}

	int getColCount() const
	{
		if (_value.empty())
			return 0;
		return _value[0].size();
	}

	/**Минор. Вариант 13 (2) Панасенко А.В. */
	_Type minor(int row, int col) const
	{
		Matrix <_Type> my(_value.size() - 1, _value.size() - 1, 0);

		for (int i = 0, i2 = 0; i < my._value.size(); i++, i2++) {
			for (int j = 0, j2 = 0; j < my._value.size(); j++, j2++) {
				if (i == row) i++;
				if (j == col) j++;
				my.put(i2, j2, _value[i][j]);
			}
		}
		return my.determinant();
	}

	_Type get(int row, int col) const
	{
		if ((unsigned int)row >= _value.size())
			throw MatrixException("Row");
		auto line = _value[row];
		if ((unsigned int)col >= line.size())
			throw MatrixException("Col");
		return line[col];
	}

	void put(int row, int col, _Type value)
	{
		if (row >= _value.size())
			throw MatrixException("Row");
		auto line = _value[row];
		if (col >= line.size())
			throw MatrixException("Col");
		_value[row][col] = value;
	}
private:
	template<typename U> friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& m);
};

template<typename _Type>
std::ostream &operator<<(std::ostream &output, const Matrix<_Type> &m)
{
	/** Вариант 14. Максимов*/
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
