#include "../include/tuple.h"
#include <math.h>
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

void testTupleMagnitude()
{
	float f_a[3]={0,1,0},f_b[3]={0,0,1},f_c[3]={1,2,3},f_d[3]={-1,-2,-3};
	Tuple t=vector(f_a);
	float expected_magnitude=1;
	float magnitude = abs(t);
	assert(magnitude==expected_magnitude);
	t=vector(f_b);
	magnitude = abs(t); 
	assert(magnitude==expected_magnitude);
	t=vector(f_c);
	expected_magnitude=sqrt(14);
	assert(abs(t)==expected_magnitude);
	t=vector(f_d);
	assert(abs(t)==expected_magnitude);
}

void testTupleNormalization()
{
	float f_a[3]={4,0,0},f_b[3]={1,0,0},f_c[3]={1,2,3},f_d[3]={0.267261,0.5342,0.80178};
	Tuple t=vector(f_a),expected=vector(f_b);
	Tuple result=norm(t);
	assert(result==expected);
	t=vector(f_c);
	result=norm(t);
	expected=vector(f_d);
	//debug(expected);debug(result);	
	assert(result==expected);		
}

void testTupleDotProduct()
{
	float f_c[3]={1,2,3},f_b[3]={2,3,4};
	Tuple t1=vector(f_c),t2=vector(f_b);
	float dot_p=dot(t1,t2);
	float expected=20;
	assert(dot_p==expected);		
}

void testTupleCrossProduct()
{
	float f_c[3]={1,2,3},f_b[3]={2,3,4},f_cb[3]={-1,2,-1};
	Tuple t1=vector(f_c),t2=vector(f_b),t12=vector(f_cb);
	Tuple t21=-t12;
	Tuple cross_p12=cross(t1,t2);
	Tuple cross_p21=cross(t2,t1);
	//debug(cross_p12);debug(cross_p21);
	assert(cross_p12==t12);
	assert(cross_p21==t21);
}
int main()
{
	testTupleAddition();
	testTupleSubtraction();
	testVectorSubtraction();
	testTupleNegation();
	testTupleScalarMultiplication();
	testTupleScalarDivision();
	testTupleMagnitude();
	testTupleNormalization();
	testTupleDotProduct();
	testTupleCrossProduct();
		
}
