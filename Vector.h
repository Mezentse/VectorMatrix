#pragma once
#include <iostream>
using namespace std;

template<class T>
class TVector
{
protected:
	T* mas;
	int len;

public:
	TVector(const TVector<T>& _mas);
	TVector(int _len = 0);
	~TVector();

	void PushBack(T variable);
	T GetLen();
	void Resize(int NewLength);
	T& operator [](int number);
	TVector<T> operator + (const TVector<T>& _vector);
	TVector<T> operator - (const TVector<T>& _vector);
	TVector<T> operator / (const TVector<T>& _vector);
	TVector<T> operator * (const TVector<T>& _vector);
	TVector<T>& operator = (const TVector<T>& _vector);
	
	bool operator == (const TVector<T>& _vector);
};

template<class T>
TVector<T>::TVector(int _len)
{
	mas = 0;
	mas = new T[_len];
	len = _len;
}

template<class T>
TVector<T>::TVector(const TVector<T>& _mas)
{
	if (_mas.mas == 0) throw "varriable of vector is empty!";
	else
	{
		if (mas != 0)
		{
			mas = 0;
			delete[] mas;
			mas = 0;
			mas = new T[_mas.len];
		}
		else
			mas = new T[_mas.len];
		len = _mas.len;
		for (int q = 0; q < len; q++)
		{
			mas[q] = _mas.mas[q];
		}
	}
}

template<class T>
TVector<T>::~TVector()
{
	delete [] mas;
}

template<class T>
inline T TVector<T>::GetLen()
{
	return len;
}

template<class T>
void TVector<T>::PushBack(T var)
{
	T* _mas = new T[len];
	for (int i = 0; i < len; i++)
	{
		_mas[i] = mas[i];
	}
	
	delete[] mas;
	mas = 0;
	mas = new T[len + 1];

	for(int i = 0; i < len; i++)
	{
		mas[i] = _mas[i];
	}

	mas[len] = var;
	len++;
}

template<class T>
void TVector<T>::Resize(int NewLength)
{
	if (NewLength < 0) throw "The new length (or equals) less than zero";
	if (NewLength >= 0)
	{
		T* temporary = new T[NewLength];
		for (int q = 0; q < NewLength; q++)
		{
			temporary[q] = mas[q];
		}

		mas = 0;
		delete[] mas;
		mas = 0;

		mas = new T[NewLength];
		len = NewLength;

		for (int q = 0; q < len; q++)
			mas[q] = temporary[q];
		temporary = 0;
		delete[] temporary;
		temporary = 0;
	}

}

template<class T>
istream& operator>>(istream& stream, TVector<T>& _vector)
{
	int _len = _vector.GetLen();
	T number;
	_vector.Resize(0);
	for (int i = 0; i < _len; i++)
	{
		stream >> number;
		_vector.PushBack(number);
	}
	return stream;
}

template<class T>
ostream& operator<<(ostream& stream, TVector<T>& _vector)
{
	for (int i = 0; i < _vector.GetLen(); i++) {
		stream << _vector[i];
	}
	return stream;
}

template<class T>
T& TVector<T>::operator[](int i)
{
	return mas[i];
}

template<class T>
TVector<T> TVector<T>::operator+ (const TVector<T>& _vector)
{
	if (_vector.mas == 0 && _vector.len < 0) throw "empty variable";
	if (_vector.len != this->len) throw "len of 1-st vector isn't equals to the 2-d vector";
	else
	{
		TVector<T> result(*this);
		for (int q = 0; q < len; q++)
		{
			result.mas[q] = (this->mas[q]) + _vector.mas[q];
		}

		return result;
	}
}

template<class T>
TVector<T> TVector<T>::operator-(const TVector<T>& _vector)
{
	if (_vector.mas == 0 && _vector.len < 0) throw "empty variable";
	if (_vector.len != this->len) throw "len of 1-st vector isn't equals to the 2-d vector";
	else
	{
		TVector<T> result(*this);
		for (int q = 0; q < len; q++)
		{
			result.mas[q] = (this->mas[q]) - _vector.mas[q];
		}

		return result;
	}
}

template<class T>
TVector<T> TVector<T>::operator/(const TVector<T>& _vector)
{
	if (_vector.mas == 0 && _vector.len < 0) throw "empty variable";
	if (_vector.len != this->len) throw "len of 1-st vector isn't equals to the 2-d vector";
	else
	{
		TVector<T> result(*this);
		for (int q = 0; q < len; q++)
		{
			if (_vector.mas[q] != 0)
				result.mas[q] = (this->mas[q]) / _vector.mas[q];
			else throw "division by zero";
		}

		return result;
	}
}

template<class T>
TVector<T>& TVector<T>::operator=(const TVector<T>& _vector)
{
	if (mas == 0) mas = new T[_vector.len];
	else if (mas != 0)
	{
		mas = 0;
		delete[] mas;
		mas = 0;
		mas = new T[_vector.len];
	}

	len = _vector.len;
	for (int q = 0; q < len; q++)
	{
		mas[q] = _vector.mas[q];
	}
	return *this;
}

template<class T>
TVector<T> TVector<T>::operator*(const TVector<T>& _vector)
{
  if (_vector.len != len) throw "Error!";
  TVector<T> result(*this);
  for (int q = 0; q < result.len; q++)
  {
  	result.mas[q] = result.mas[q] * _vector.mas[q];
  }
  return result;
}

template<class T>
bool TVector<T>::operator==(const TVector<T>& _vector)
{
	if (len != _vector.len) return false;
	for (int q = 0; q < len; q++)
	{
		if (mas[q] != _vector.mas[q]) return false;
	}
	return true;
}