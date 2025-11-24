#pragma once
#include "matrix.h"


template <typename T, size_t N>
struct Vec{
	T arr[N];
	bool operator==(const Vec<T,N> &t1);
	Vec<T,N> operator+(const Vec<T,N> &t1);
	Vec<T,N> operator-(const Vec<T,N> &t1);
	Vec<T,N> operator-();
	Vec<T,N> operator*(T scalar);
	Vec<T,N> operator/(T scalar);
	Vec<T,N> operator*(const Matrix<T, N, M> &m);
  	Vec<T,N> operator*(const Vec<T,N> &t);
};
