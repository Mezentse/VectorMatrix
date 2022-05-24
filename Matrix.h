#pragma once
#include "Vector.h"
#include <iostream>
using namespace std;

template <class T>
class TMatrix : public TVector<TVector<T>>
{
protected:

	int height;
public:
	TMatrix();
	~TMatrix();
	TMatrix(int _len, int _height);
	TMatrix(int _len, int _height, T variable);
	TMatrix(const TMatrix<T>& _matrix);
	int GetHeight();
	int GetLen();
	TMatrix<T> operator + (const TMatrix<T>& _matrix);
	TMatrix<T> operator - (const TMatrix<T>& _matrix);
	TMatrix<T>& operator = (const TMatrix<T>& _matrix);
	TMatrix<T> operator * (const TMatrix<T>& _matrix);
	TMatrix<T> operator * (const TVector<T>& _vector);
	bool operator == (const TMatrix<T>& _matrix);
};

template<class T>
TMatrix<T>::TMatrix()
{
	this->mas = 0;
	this->len = 0;
	this->height = 0;
}

template<class T>
TMatrix<T>::TMatrix(int _len, int _height)
{
	this->len = _len;
	this->height = _height;
	this->mas = new TVector<T>[height];
	for (int i = 0; i < _height; i++)
	{
		this->mas[i] = TVector<T>(_len);
	}
	
}

template<class T>
TMatrix<T>::TMatrix(int _len, int _height, T variable)
{
	this->len = _len;
	this->height = _height;
	this->mas = new TVector<T>[height];
	for (int i = 0; i < _height; i++)
	{
		this->mas[i] = TVector<T>(_len);
	}
	
	for (int x = 0; x < _height; x++)
		for (int y = 0; y < _len; y++)
			this->mas[x][y] = variable;
}

template<class T>
TMatrix<T>::TMatrix(const TMatrix<T>& _matrix)
{
	this->height = _matrix.height;
	this->len = _matrix.len;
	this->mas = new TVector<T>[this->height];
	for (int i = 0; i < this->height; i++)
	{
		this->mas[i] = TVector<T>(this->len);
	}

	for (int x = 0; x < this->height; x++)
		for (int y = 0; y < this->len; y++)
			this->mas[x][y] = _matrix.mas[x][y];
}

/*template<class T>
TMatrix<T>::~TMatrix()
{
	for (int i = 0; i < height; i++) {
		this->mas[i].~TVector();
		this->mas[i] = 0;
	}
	delete[] this->mas;
	this->mas = 0;
}*/

template<class T>
int TMatrix<T>::GetHeight()
{
	return this->height;
}

template<class T>
int TMatrix<T>::GetLen()
{
	return this->len;
}

template<class T>
ostream& operator<<(ostream& stream, TMatrix<T>& _matrix)
{
	for (int q = 0; q < _matrix.GetHeight(); q++)
	{
		for (int i = 0; i < _matrix.GetLen(); i++)
			stream << _matrix[q][i];
	}
	return stream;
}

template<class T>
istream& operator>>(istream& stream, TMatrix<T>& _matrix)
{
	T var = 0;
	for (int q = 0; q < _matrix.GetHeight(); q++)
	{
		for (int i = 0; i < _matrix.GetLen(); i++)
		{
			stream >> var;
			_matrix[q][i] = var;
		}

	}
	return stream;
}

template<class T>
TMatrix<T> TMatrix<T>::operator+(const TMatrix& _matrix)
{
	if ((this->height == _matrix.height) && (this->len == _matrix.len)) {
		TMatrix result(*this);
			for (int i = 0; i < this->height; i++) {
				for (int j = 0; j < this->len; j++) {
					result.mas[i][j] = this->mas[i][j] + _matrix.mas[i][j];
				}
			}
			
		return result;
	}
	else {
		cout << "The number of rows does not match the number of columns in the matrices. Check the matrices." << endl;
			abort();
	}
}



template<class T>
TMatrix<T> TMatrix<T>::operator-(const TMatrix<T>& _matrix)
{
	if ((this->height == _matrix.height) && (this->len == _matrix.len)) {
		TMatrix result(*this);
		for (int i = 0; i < this->height; i++) {
			for (int j = 0; j < this->len; j++) {
				result.mas[i][j] = this->mas[i][j] - _matrix.mas[i][j];
			}
		}
		return result;
	}
	else {
		cout << "The number of rows does not match the number of columns in the matrices. Check the matrices." << endl;
		abort();
	}
}

template<class T>
TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T>& _matrix)
{
	if (this == &_matrix) return *this;
	if (this->len != _matrix.len || height != _matrix.height) throw "the len or height of first matrix isn't equals to len of height of second matrix";
	for (int q = 0; q < height; q++)
		for (int w = 0; w < this->len; w++)
			this->mas[q][w] = _matrix.mas[q][w];
	return *this;
}

template<class T>
TMatrix<T> TMatrix<T>::operator*(const TMatrix<T>& _matrix)
{
	if (this->len == _matrix.height) {
		TMatrix<T> result(_matrix.len, height, 0);
		for (int i = 0; i < this->height; i++) {
			for (int j = 0; j < _matrix.height; j++) {
				for (int k = 0; k < this->len; k++) {
					result.mas[i][j] += this->mas[i][k] * _matrix.mas[k][j];
				}
			}
		}
		return result;
	}
	else {
		cout << "The number of rows does not match the number of columns in the matrices. Check the matrices." << endl;
		abort();
	}
}

template<class T>
TMatrix<T> TMatrix<T>::operator*(const TVector<T>& _vector)
{
	TVector<T> temp(_vector);
	if ((this->len) != temp.GetLen()) throw "size of matrines aren't correct";

	TMatrix<T> result(1, height, 0);
	for (int i = 0; i < height; i++)
	{
		for (int x = 0; x < this->len; x++)
			result[i][0] += this->mas[i][x] * temp[x];
	}

	return result;
}

template<class T>
inline bool TMatrix<T>::operator==(const TMatrix<T>& _matrix)
{
	if (this == &_matrix) return true;
	if (this->len != _matrix.length || height != _matrix.height) return false;
	for (int q = 0; q < height; q++)
	{
		for (int w = 0; w < this->length; w++)
			if (this->mas[q][w] != _matrix.mas[q][w]) return false;
	}
	return true;
}