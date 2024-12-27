#include "../include/tuple.h"
#include <assert.h>
#include <iostream>

void testTupleAddition() {
  float f_a[3] = {3, -2, 5}, f_b[3] = {-2, 3, 1};
  Tuple a = point(f_a), b = vector(f_b);
  Tuple d = a + b;
  float f_c[3] = {1, 1, 6};
  Tuple c = point(f_c);
  assert(d == c);
}

void testTupleSubtraction()
{
	float f_a[3] = {3, 2, 1}, f_b[3] = {5, 6, 7};
	Tuple a = point(f_a), b = point(f_b);
	Tuple d = a-b;
	float f_c[3] = {-2,-4,-6};
	Tuple c = vector(f_c);	
	assert(d==c);
}

void testVectorSubtraction()
{
	float f_a[3] = {3, 2, 1}, f_b[3] = {5, 6, 7};
	Tuple a = vector(f_a), b = vector(f_b);
	Tuple d = a-b;
	float f_c[3] = {-2,-4,-6};
	Tuple c = vector(f_c);
	assert(d==c);
}

void testTupleNegation()
{
	float f_a[4] = {1, 2, -3, 4}, f_b[4] = {-1, -2, 3,-4};
	Tuple t={4,f_a};
	Tuple y=-t;
	Tuple r={4, f_b};
	assert(y==r);
}	

void testTupleScalarMultiplication()
{
	float f_a[4] = {1,-2,3,-4}, f_b[4] = {3.5, -7, 10.5, -14};
	Tuple t = {4,f_a};
	Tuple y = t*3.5;
	Tuple r = {4, f_b};
	assert(y==r);
}

void testTupleScalarDivision()
{
	float f_a[4] = {1,-2,3,-4}, f_b[4] = {0.5, -1, 1.5, -2};
	Tuple t = {4,f_a};
	Tuple y = t/2;
	Tuple r = {4, f_b};
	assert(y==r);
}
int main()
{
	testTupleAddition();
	testTupleSubtraction();
	testVectorSubtraction();
	testTupleNegation();
	testTupleScalarMultiplication();
	testTupleScalarDivision();
		
}
