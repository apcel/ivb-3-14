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
