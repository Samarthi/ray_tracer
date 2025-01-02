#include "../include/tuple.h"
#include <iostream>
#include <malloc.h>
#include <math.h>
#include <stdexcept>
#include <assert.h>
#include <functional>
#include <vector>
#include <tuple>
#include <stack>
#include <algorithm>
#define EPS 0.001

bool eq(float f1, float f2) { return fabs(f1 - f2) <= EPS; }

bool Tuple::operator==(Tuple t1) {
  bool result = true;
  for (int i = 0; i < 4; i++)
    result &= (eq(this->p_v[i], t1.p_v[i]));
  return result;
}

Tuple Tuple::operator+(Tuple t1) {
  Tuple r = {this->dim, (float *)malloc(sizeof(float) * this->dim)};
  for (int i = 0; i < this->dim; ++i)
    r.p_v[i] = this->p_v[i] + t1.p_v[i];
  return r;
}

Tuple Tuple::operator-(Tuple t1) {
  Tuple r = {this->dim, (float *)malloc(sizeof(float) * this->dim)};
  for (int i = 0; i < this->dim; ++i)
    r.p_v[i] = this->p_v[i] - t1.p_v[i];
  return r;
}

Tuple Tuple::operator-() {
  Tuple r = {this->dim, (float *)malloc(sizeof(float) * this->dim)};
  for (int i = 0; i < this->dim; ++i)
    r.p_v[i] = -(this->p_v[i]);
  return r;
}

Tuple Tuple::operator*(float scalar) {
  Tuple r = {this->dim, (float *)malloc(sizeof(float) * this->dim)};
  for (int i = 0; i < this->dim; ++i)
    r.p_v[i] = this->p_v[i] * scalar;
  return r;
}

Tuple Tuple::operator/(float scalar) {
  Tuple r = {this->dim, (float *)malloc(sizeof(float) * this->dim)};
  for (int i = 0; i < this->dim; ++i)
    r.p_v[i] = this->p_v[i] /= scalar;
  return r;
}

Tuple Tuple::operator *(Matrix<float> m) {
	Tuple t = {this->dim,new float[this->dim]()};
	for(int i=0;i<this->dim;i++){
		t.p_v[i]=0;
		for(int j=0;j<this->dim;j++)
				t.p_v[i]+= this->p_v[j] * m.p_matrix[j][i];
	}
	return t;
}

//only for colors
Tuple Tuple::operator *(Tuple t) {
	Tuple result = {3, (float*)calloc(sizeof(float),3)};
	for(int i=0;i<t.dim;i++){
		result.p_v[i] = this->p_v[i]*t.p_v[i];	
	}
	return result;
}

void debug(Tuple t) {
  char coords[4] = {'x', 'y', 'z', 'w'};
  for (int i = 0; i < 4; i++)
    std::cout << coords[i] << ' ' << t.p_v[i] << std::endl;
}

float abs(Tuple t) {
  float result = 0;
  for (int i = 0; i < t.dim; i++)
    result += pow(t.p_v[i], 2);
  return sqrt(result);
}

Tuple norm(Tuple t) {
  float magnitude = abs(t);
  Tuple r = {t.dim, (float *)malloc(sizeof(float) * t.dim)};
  for (int i = 0; i < t.dim; ++i)
    r.p_v[i] = t.p_v[i] / magnitude;
  return r;
}

float dot(Tuple a, Tuple b) {
  float result = 0;
  for (int i = 0; i < a.dim; i++)
    result += a.p_v[i] * b.p_v[i];
  return result;
}

Tuple cross(Tuple a, Tuple b) {
  Tuple r = {a.dim, (float *)calloc(sizeof(float), a.dim)};
  int mod = a.dim - 1;
  for (int i = 0; i < a.dim - 1; i++)
    r.p_v[i] = a.p_v[(i + 1) % mod] * b.p_v[(i + 2) % mod] -
               a.p_v[(i + 2) % mod] * b.p_v[(i + 1) % mod];
  return r;
}

Tuple point(float *p_v) {
  Tuple t = {4, (float *)malloc(sizeof(float) * 4)};
  for (int i = 0; i < 3; i++)
    t.p_v[i] = p_v[i];
  t.p_v[3] = 1;
  return t;
}

Tuple vector(float *p_v) {
  Tuple t = {4, (float *)malloc(sizeof(float) * 4)};
  for (int i = 0; i < 3; i++)
    t.p_v[i] = p_v[i];
  t.p_v[3] = 0;
  return t;
}

Tuple origin() {
  float p_origin[3] = {0, 0, 0};
  return point(p_origin);
}

Tuple black() {
	float p_black[3] = {0, 0, 0};
	return color(p_black);
}
Tuple point3(float x, float y, float z) {
	float arr[3]={x,y,z};
	return point(arr);
}

Tuple vec3(float x, float y, float z) {
	float arr[3]={x,y,z};
	return vector(arr);
}

template <typename T> bool Matrix<T>::operator==(Matrix<T> m) {
  if (this->length != m.length)
    return false;
  if (this->width != m.width)
    return false;
  for (int i = 0; i < this->length; i++)
    for (int j = 0; j < this->width; j++)
      if (!eq(this->p_matrix[i][j], m.p_matrix[i][j]))
        return false;
  return true;
}
template <typename T> Matrix<T> Matrix<T>::operator*(Matrix<T> m) {
  if (this->width != m.length)
    throw std::invalid_argument("this->width!=m.length");
  Matrix result;
  result.length = this->length;
  result.width = m.width;
  result.p_matrix=(float **)calloc(sizeof(float *),result.length);
  for (int i = 0; i < result.length; i++)
    result.p_matrix[i] = (T *)calloc(sizeof(T), result.width);
  for (int i = 0; i < this->length; i++) {
    for (int j = 0; j < m.width; j++)
      for (int k = 0; k < this->width; k++) {
        result.p_matrix[i][j] += this->p_matrix[i][k] * m.p_matrix[k][j];
      }
  }
  return result;
}

template<>
 Matrix<float> Matrix<float>::operator*(Matrix<float> m) {
  if (this->width != m.length)
    throw std::invalid_argument("this->width!=m.length");
  Matrix result;
  result.length = this->length;
  result.width = m.width;
  result.p_matrix=(float **)calloc(sizeof(float *),result.length);
  for (int i = 0; i < result.length; i++)
    result.p_matrix[i] = (float *)calloc(sizeof(float), result.width);
  for (int i = 0; i < this->length; i++) {
    for (int j = 0; j < m.width; j++)
      for (int k = 0; k < this->width; k++) {
        result.p_matrix[i][j] += this->p_matrix[i][k] * m.p_matrix[k][j];
      }
  }
  return result;
}

template <> 
bool Matrix<float>::operator==(Matrix<float> m) {
  if (this->length != m.length)
    return false;
  if (this->width != m.width)
    return false;
  for (int i = 0; i < this->length; i++)
    for (int j = 0; j < this->width; j++)
      if (!eq(this->p_matrix[i][j], m.p_matrix[i][j]))
        return false;
  return true;
}

float abs(Matrix<float> m) {
	if(m.length==2)
		return m.p_matrix[0][0] * m.p_matrix[1][1] - m.p_matrix[0][1] * m.p_matrix[1][0];
	float det = 0;
	for (int j = 0; j < m.width; j++) {
		Matrix<float> subMatrix;
        subMatrix.length = m.length - 1;
        subMatrix.width = m.width - 1;
        subMatrix.p_matrix = new float *[subMatrix.length];
        for (int row = 1; row < m.length; row++) {
            subMatrix.p_matrix[row - 1] = new float[subMatrix.width];
            int subColIndex = 0;
            for (int col = 0; col < m.width; col++) {
                if (col == j) continue;
                subMatrix.p_matrix[row - 1][subColIndex] = m.p_matrix[row][col];
                subColIndex++;
            }
        }
        float subDet = abs(subMatrix);
        for (int row = 0; row < subMatrix.length; row++) {
            delete[] subMatrix.p_matrix[row];
        }
        delete[] subMatrix.p_matrix;
        det += (j % 2 == 0 ? 1 : -1) * m.p_matrix[0][j] * subDet;
    }
    return det;
}

Matrix<float> identity(int n) {
  Matrix<float> identity = {n, n, (float **)calloc(sizeof(float *), n)};
  for (int i = 0; i < n; i++)
    identity.p_matrix[i] = (float *)calloc(sizeof(float), n);
  for (int i = 0; i < n; i++)
    identity.p_matrix[i][i] = 1.0f;
  return identity;
}

Matrix<float> transpose(Matrix<float> m) {
  for (int i = 0; i < m.length; i++)
    for (int j = i + 1; j < m.width; j++)
      std::swap(m.p_matrix[i][j], m.p_matrix[j][i]);
  return m;
}

Matrix<float> inverse(Matrix<float> m) {
  float det = abs(m);
  if (det) {
    Matrix<float> inverse;
    inverse.length = m.length;
    inverse.width = m.width;
    inverse.p_matrix = new float*[inverse.length];
    for (int i = 0; i < inverse.length; i++) 
        inverse.p_matrix[i] = new float[inverse.width];
    
    for (int i = 0; i < inverse.length; i++) {
        for (int j = 0; j < inverse.width; j++) {
            Matrix<float> subMatrix;
            subMatrix.length = inverse.length - 1;
            subMatrix.width = inverse.width - 1;
            subMatrix.p_matrix = new float*[subMatrix.length];
            for (int row = 0, subRow = 0; row < inverse.length; row++) {
                if (row == i) continue;
                subMatrix.p_matrix[subRow] = new float[subMatrix.width];
                for (int col = 0, subCol = 0; col < inverse.width; col++) {
                    if (col == j) continue;
                    subMatrix.p_matrix[subRow][subCol] = m.p_matrix[row][col];
                    subCol++;
                }
                subRow++;
            }
            float subDet = abs(subMatrix);
            for (int row = 0; row < subMatrix.length; row++) {
                delete[] subMatrix.p_matrix[row];
            }
            delete[] subMatrix.p_matrix;
            inverse.p_matrix[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * subDet / det;
        }
    }
	return inverse;
  } 
  else throw std::invalid_argument("Matrix not invertible");
}

// creates a row matrix from a point
Matrix<float> tuple_to_matrix(Tuple T) {
	float **p_v=(float**)malloc(sizeof(float*));
	p_v[0]=(float*)calloc(sizeof(float),T.dim);
	Matrix<float> m = {1, T.dim, p_v};
	for (int i = 0; i < T.dim; i++)
		m.p_matrix[0][i] = T.p_v[i];
	return m;
}

//creates a Tuple from a row matrix
Tuple matrix_to_tuple(Matrix<float> m){
	assert(m.length==1);
	Tuple t={m.width,(float*)calloc(sizeof(float),m.width)};
	for(int i=0;i<m.width;i++)
		t.p_v[i] = m.p_matrix[0][i];
	return t; 
}

Matrix<float> translate(int x, int y, int z) {
  Matrix<float> translate_tr = identity(4);
  translate_tr.p_matrix[3][0] = x;
  translate_tr.p_matrix[3][1] = y;
  translate_tr.p_matrix[3][2] = z;
  return translate_tr;
}

Matrix<float> scale(float x, float y, float z) {
  Matrix<float> scale_tr = identity(4);
  scale_tr.p_matrix[0][0] = x;
  scale_tr.p_matrix[1][1] = y;
  scale_tr.p_matrix[2][2] = z;
  return scale_tr;
}
// implement rot_x, rot_y, rot_z
// r'_y=r'cos(theta+phi)=r'cos(theta)cos(phi)-sin(theta)sin(phi)
// similar derivation for r'_z
//|1|0    |0     |0|
//|0|cos r|-sin r|0|
//|0|sin r|cos r |0|
//|0|0    |0     |1|

Matrix<float> rot_x(float radians) {
  Matrix<float> rot_x_tr = identity(4);
  rot_x_tr.p_matrix[1][1] = rot_x_tr.p_matrix[2][2] = cos(radians);
  rot_x_tr.p_matrix[2][1] = sin(radians);
  rot_x_tr.p_matrix[1][2] = -1 * sin(radians);
  return rot_x_tr;
}

Matrix<float> rot_y(float radians) {
  Matrix<float> rot_y_tr = identity(4);
  rot_y_tr.p_matrix[0][0] = rot_y_tr.p_matrix[2][2] = cos(radians);
  rot_y_tr.p_matrix[2][0] = sin(radians);
  rot_y_tr.p_matrix[2][2] = -1 * sin(radians);
  return rot_y_tr;
}

Matrix<float> rot_z(float radians) {
  Matrix<float> rot_z_tr = identity(4);
  rot_z_tr.p_matrix[0][0] = cos(radians), rot_z_tr.p_matrix[1][1] = cos(radians),
  rot_z_tr.p_matrix[1][0] = -1 * sin(radians),  rot_z_tr.p_matrix[0][1] = sin(radians);
  return rot_z_tr;
}

Matrix<float> shear(float xy, float xz, float yx, float yz, float zx, float zy) {
  Matrix<float> shear_tr = identity(4);
  shear_tr.p_matrix[0][1] = yx, shear_tr.p_matrix[0][2] = zx,
  shear_tr.p_matrix[1][0] = xy, shear_tr.p_matrix[1][2] = zy,
  shear_tr.p_matrix[2][0] = xz, shear_tr.p_matrix[2][1] = yz;
  return shear_tr;
}
void executeFunctions(const std::vector<std::pair<std::function<void()>, std::function<void()>>>& functions) {
    for (const auto& func_pair : functions) {
        func_pair.first();
        func_pair.second();
    }
}

void debug(Matrix<float> m){
	for(int i=0;i<m.length;i++){
		for(int j=0;j<m.width;j++)
			std::cout<<m.p_matrix[i][j]<<' ';
		std::cout<<std::endl;	
	}
}

Matrix<float> create_matrix(int l, int w, float* p_v){
	Matrix<float> m = {l,w,(float**)calloc(sizeof(float*),l)};
	for(int i=0;i<w;++i)
		m.p_matrix[i]=(float*)calloc(sizeof(float),w);
	for(int i=0;i<l;i++)
		for (int j = 0; j < w; j++)
			m.p_matrix[i][j] = p_v[i*w+j];
	return m;
}

Matrix<float> final_transform(Matrix<float> t1,Matrix<float> t2){
	return t2*t1;
}

Tuple color(float *p_v)
{
  Tuple t = {3, (float *)malloc(sizeof(float) * 3)};
  for (int i = 0; i < 3; ++i)
    t.p_v[i] = p_v[i];
  return t;
}

Tuple color3(float red, float blue, float green)
{
	float arr[3]={red,blue,green};
	return color(arr);
}

Matrix<Tuple> canvas(int length, int width)
{
  float white[3] = {255, 255, 255};
  Matrix<Tuple> m = {length, width, (Tuple **)malloc(sizeof(Tuple *) * length)};
  for (int i = 0; i < length; ++i)
  {
    m.p_matrix[i] = (Tuple *)malloc(sizeof(Tuple) * width);
    std::fill(m.p_matrix[i], m.p_matrix[i] + width, color(white));
  }
  return m;
}

bool is_within_canvas_bounds(Matrix<Tuple> *canvas, int height, int width)
{
  if (height < 0 or height > canvas->length)
    return false;
  if (width < 0 or width > canvas->width)
    return false;
  return true;
}

void write_pixel(Matrix<Tuple> *canvas, int height, int width, Tuple color)
{
  if (is_within_canvas_bounds(canvas, height, width))
    canvas->p_matrix[height][width] = color;
}
