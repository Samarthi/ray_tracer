#include "../include/tuple.h"
#include "../include/ray.h"
#include <math.h>
#include <assert.h>
#include <iostream>

void testTupleAddition() 
{
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
	Tuple y = t*3.5f;
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

void testTupletoMatrix()
{	
	float p_v[3]={1,2,3};
	Tuple t=point(p_v);
	//debug(t);
	Matrix<float> m=tuple_to_matrix(t);
	float p_m[4]={1,2,3,1};
	Matrix<float> expected = create_matrix(1,4,p_m);
	//debug(m),debug(expected);
	assert(m==expected);	
}

void testDeterminant()
{
	float p_v[16]={-2,-8,3,5,-3,1,7,3,1,2,-9,6,-6,7,7,-9};
	Matrix<float> m=create_matrix(4,4,p_v);
	float det=abs(m),expected=-4071;
	assert(det==expected);
}

void testInverse()
{
	float m_v[16]={-5,2,6,-8,1,-5,1,8,7,7,-6,-7,1,-3,7,4},
		  inverse_v[16]={0.21805,0.45113,0.24060,-0.04511,-0.80827,
			  -1.45677,-0.44361,0.52068,-0.07895,-0.22368,-0.05263,
			  0.19737,-0.52256,-0.81391,-0.30075,0.30639};
	Matrix<float> m=create_matrix(4,4,m_v),expected=create_matrix(4,4,inverse_v);
	Matrix<float> m_inverse=inverse(m);
	assert(m_inverse==expected);
}

void testNormal1()
{
	Sphere s={1,translate(0,1,0)};
	float intersection_v[3]={0,1.70711,-0.70711},expected_v[3]={0,0.70711,-0.70711};
	Tuple normal=normal_at(s,point(intersection_v));
	Tuple expected=vector(expected_v);
	//debug(normal);
	assert(normal==expected);
}

void testNormal()
{
	Matrix<float> transform=rot_z(PI/5)*scale(1,0.5,1);
	Sphere s={1,transform};
	float intersection_v[3]={0.0,sqrt(2)/2,-sqrt(2)/2},expected_v[3]={0.0,0.97014,-0.24254};
	Tuple normal=normal_at(s,point(intersection_v));
	Tuple expected=vector(expected_v);
	assert(normal==expected);	
}

void testRotz()
{
	float p_v[3]={0,1,0};
	Tuple p=point(p_v);
	Tuple half_quarter=p*rot_z(PI/4),full_quarter=p*rot_z(PI/2);
	float expected_hq_v[3]={-sqrt(2)/2,sqrt(2)/2,0},expected_fq_v[3]={-1,0,0};
	Tuple expected_hq=point(expected_hq_v),expected_fq=point(expected_fq_v);
	assert(half_quarter==expected_hq);
	assert(full_quarter==expected_fq);	
}

void testScale()
{
	float p_v[3]={-4,6,8},expected_v[3]={-8,18,32};
	Tuple p=point(p_v),expected=point(expected_v);
	Tuple scaled=p*scale(2,3,4);
	assert(scaled==expected);	
}

void testLighting()
{
	//eye between light and surface
	Tuple position=point3(0,0,0), eyev=vec3(0,0,-1), normalv=vec3(0,0,-1);
	Light light = {point3(0,0,-10),color3(1,1,1)};
	Material m;
	Tuple result = lighting(m,light,position,eyev,normalv);
	assert(result==color3(1.9,1.9,1.9)); 
	
	//eye between light and surface, eye offset at 45deg
	eyev=vec3(0,sqrt(2)/2,-sqrt(2)/2);
	result = lighting(m, light, position, eyev,normalv);
	assert(result==color3(1.0,1.0,1.0));
	
	//lighting with eye opposite surface
	eyev = vec3(0,0,-1);
	light.position=point3(0,10,-10);
	result = lighting(m, light, position, eyev,normalv);
	assert(result==color3(0.7364,0.7364,0.7364));	
	
	//eye in the path of the reflection vector
	eyev=vec3(0,-sqrt(2)/2,-sqrt(2)/2);
	result = lighting(m, light, position, eyev,normalv);
	assert(result==color3(1.6364,1.6364,1.6364));	
}

void testIntersectWorld() {
	World w=world();
	Ray r = { point3(0,0,-5),vec3(0,0,1)};
	std::vector<Intersection> * p_il=intersect_world(r,w);
	assert((*p_il).size()==4);
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
	testTupletoMatrix();
	testDeterminant();
	testInverse();
	testNormal();
	testNormal1();
	testRotz();
	testLighting();
	testIntersectWorld();	
}
