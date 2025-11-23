#pragma once
#include "vec.h"

template <typename T, size_t N, size_t M>
struct Matrix{
	Vec<T,M> arr[N];
}