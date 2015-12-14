#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <vector>
#include <map>
#include <exception>
#include <algorithm>
#include <ostream>
#include <iomanip>
#include <sstream>

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
	/* Alexandr-Pankratov */
	bool operator==(const Matrix<_Type> &other)
	{
		for (int i = 0; i < getRowCount(); i++) {
			for (int j = 0; j < getColCount(); j++) {
				if (get(i, j) != other.get(i, j))
					return false;
			}
		}
		return true;
	}

	bool operator>=(const Matrix<_Type> &other)
	{
		return determinant() >= other.determinant();
	}

	bool operator<=(const Matrix<_Type> &other)
	{
		return determinant() <= other.determinant();
	}

	bool operator!=(const Matrix<_Type> &other)
	{
		return !operator==(other);
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
	/* Safronov.I.A */
	Matrix<_Type> operator*(_Type number)
	{
		Matrix <_Type> result(getRowCount(), getColCount(), 0);

		for (int i = 0; i < getRowCount(); i++) {
			for (int j = 0; j < getColCount(); j++) {
				result.put(i, j, get(i, j) * number);
			}
		}
		return result;
	}

	/** Умножение матриц. Вариант 5 */
	/* Ilina V.D. */
	Matrix<_Type> operator*(const Matrix<_Type> &that)
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
	/* Быковский */
	Matrix<_Type>  operator^(const int number)
	{
		if(getRowCount() != getColCount()){
			throw MatrixException("Invalid Size!");
		}

		Matrix<_Type> result(getColCount(), getColCount(), 0);
		for (int i = 0; i < getColCount(); i++) {
			result.put(i, i, 1);
		}
		for (int i = 1; i <= number; i++){
			result = result * (*this);
		}
		return result;
	}

	Matrix<_Type> & operator^(int number)
	{
		if (m.getRowCount() != m.getColCount())
			throw MatrixException("Invalid size");
		Matrix<_Type> result(m.getRowCount(), m.getRowCount(), 0)
			for (int i = 0; i < m.getRowCount; i++)
				result.put(i, i, 1);
		//Теперь у нас есть единичная матрица нужного размера
		std::cout « result « std::endl;
		//если это не так, надо что-то редактиовать
		for (int i = 1; i <= number; i++)
			result = result * m;
		return result;
	}

	/**Обратная матрица. Вариант 8 (2)*/
	/* Folomkin A.A. */
	Matrix<_Type> invert()
	{
		int size = getRowCount();
		if (size != getColCount()){
			throw MatrixException("Invalid size");
			return *this;

		}
	Matrix<_Type> result(size, size, 0);
	_Type det = determinant();

	if (det == 0)
	{
		throw MatrixException("Determinant = 0");
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
	/*Zalyaliev R.R.*/
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

	/* Транспониромание. Вариант 7 */
	/* Богомазов Степан */
	Matrix<_Type> & transposition()
	{
		for (int n = 0; n <= number; n++) {
			for (int i = 0; i < getRowCount(); i++)	{
				for (int j = 0; j < getColCount(); j++)	{
					for (int k = 0; k < getColCount(); k++)	{
						transpArray[j][i] = array[i][j];
						result.put(i, j, value);
					}
				}
			}
		}
		return *this;
	}


	/**Минор. Вариант 13 (2) Панасенко А.В. */
	/* Basin G.J. */
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
	std::stringstream element;
	std::streamsize maxSize = 0;
	std::streamsize tmpSize = 0;
	_Type testElement = '\0';

	int colCount = m.getColCount();
	int rowCount = m.getRowCount();

	maxSize = 0;
	for(int i = 0; i < rowCount; ++i) {
		//output << std::setw(3) << maxSize << " | " << testElement << " | " <<  tmpSize << std::endl;
		for(int j = 0; j < colCount; ++j) {
			//output << m.get(i, j) << std::endl;
			element << m.get(i, j) << ' ';
			element.ignore(256, ' ');
			tmpSize = element.gcount();
			//std::cout << element.gcount();
			//std::cout << testElement << std::endl;

			if(maxSize < tmpSize) {
				maxSize = tmpSize;
			};
		};
	};
	//return output;
	//std::cout << maxSize;
	for(int i = 0; i < rowCount; ++i) {
		for(int j = 0; j < colCount; ++j) {
			output << std::setw(maxSize + 1) << m.get(i, j);
		}
		output << std::endl;
	}
	return output;
}

#endif /** _MATRIX_H_ */
