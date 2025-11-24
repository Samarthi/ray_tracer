#pragma once
#include "vec.h"
#include "matrix.h"
#include <cmath>
#define EQ 0.0000008
#include <iostream>

template <typename T, size_t N>
bool Vec<T, N>::operator==(const Vec<T, N> &v)
{
	for (int i = 0; i < N; ++i)
	{
		T abs_val = this->arr[i] - v.arr[i];
		abs_val = abs_val > 0 ? abs_val : -1 * abs_val;
		if (abs_val > EQ)
			return false;
	}
	return true;
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator+(const Vec<T, N> &v)
{
	Vec<T, N> result;
	for (int i = 0; i < N; ++i)
		result.arr[i] = this->arr[i] + v.arr[i];
	return result;
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator-(const Vec<T, N> &v)
{
	Vec<T, N> result;
	for (int i = 0; i < N; ++i)
		result.arr[i] = this->arr[i] - v.arr[i];
	return result;
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator-()
{
	Vec<T,N> result;
	for (int i = 0; i < N; ++i)
		result.arr[i] = this->arr[i] *-1;
	return result;
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator*(T scalar)
{
	Vec<T, N> result;
	for (int i = 0; i < N; ++i)
	{
		result.arr[i] = this->arr[i] * scalar;
	}
	return result;
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator/(T scalar)
{
	Vec<T, N> result;
	for (int i = 0; i < N; ++i)
	{
		result.arr[i] = this->arr[i] / scalar;
	}
	return result;
}

template <typename T, size_t N, size_t M>
Vec<T, M> Vec<T, N>::operator*(const Matrix<T, N, M> &m)
{
	Vec<T, M> result;
	for (int i = 0; i < M; ++i)
	{
		result.arr[i] = 0;
		for (int j = 1; j < N; ++j)
			result.arr[i] += this->arr[i] * m.arr[i].arr[j];
	}
	return result;
}

template <typename T, size_t N>
Vec<T, N> cross(const Vec<T, N> &v1, const Vec<T, N> &v2)
{
	Vec<T, N> result;
	for (int i = 0; i < N; i++)
	{
		result.arr[i] = v1.arr[(i + 1) % N] * v2.arr[(i + 2) % N] - v1.arr[(i + 2) % N] * v2.arr[(i + 1) % N];
	}
	return result;
}

template <typename T, size_t N>
T dot(const Vec<T, N> &v1, const Vec<T, N> &v2)
{
	T result=0;
	for (int i = 0; i < N; ++i)
		result += v1.arr[i] * v2.arr[i];
	return result;
}

template <typename T, size_t N>
Vec<T, N> hadamard(const Vec<T, N> &v1, const Vec<T, N> &v2){
	Vec<T, N> result;
	for (int i = 0; i < N; ++i)
		result.arr[i] = v1.arr[i] * v2.arr[i];
	return result;
}

template <typename T, size_t N>
void debug(const Vec<T, N> &v){
	for (int i = 0; i < N; ++i){
		std::cout << i << ' ' << v.arr[i] << ' ';
	}
	std::cout << endl;
}

template <typename T, size_t N>
T abs(const Vec<T, N> &v){
	T result = 0;
	for (int i = 0; i < N; ++i)
	{
		result += v.arr[i] * v.arr[i];
	}
	return sqrt(result);
}
