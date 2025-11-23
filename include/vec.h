#pragma once
#include "matrix.h"


template <typename T, size_t N>
struct Vec{
	T arr[N];
	bool operator==(Vec<T,N> t1);
	Tuple operator+(Vec<T,N> t1);
	Tuple operator-(Vec<T,N> t1);
	Tuple operator-();
	Tuple operator*(T scalar);
	Tuple operator/(T scalar);
	Tuple operator*(Matrix<T, N, M> m);
  	Tuple operator*(Vec<T,N> t);
}
