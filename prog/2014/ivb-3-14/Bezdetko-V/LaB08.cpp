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
