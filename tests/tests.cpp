#include "../include/tuple.h"
#include <assert.h>

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
	Tuple d = b-a;
	float f_c[3] = {-2,-4,-6};
	Tuple c = vector(f_c);
	assert(d==c);
}

void testVectorSubtraction()
{
	float f_a[3] = {3, 2, 1}, f_b[3] = {5, 6, 7};
	Tuple a = vector(f_a), b = vector(f_b);
	Tuple d = b-a;
	float f_c[3] = {-2,-4,-6};
	Tuple c = vector(f_c);
	assert(d==c);
}
	

int main()
{
	testTupleAddition();
	testTupleSubtraction();
	testVectorSubtraction();	
}
