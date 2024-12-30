#include "../include/tuple.h"
#include <iostream>
#include <malloc.h>
#include <math.h>
#include <stdexcept>
#include <assert.h>

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
// TODO: decouple cross product from 3 dimensions
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
float abs(Matrix<float> m) {
  float result = 0;
  for (int j = 0; j < m.width; j++) {
    if (m.length <= 3) {
      float inner_det = (m.p_matrix[1][(j + 1) % 3] * m.p_matrix[2][(j + 2) % 3] -
                       m.p_matrix[1][(j + 2) % 3] * m.p_matrix[2][(j + 1) % 3]);
      result += m.p_matrix[0][j] * inner_det;
    } else {
      Matrix<float> inner_m = {m.length - 1, m.width - 1,
                             (float **)calloc(sizeof(float *), m.length - 1)};
      for (int i = 0; i < m.length - 1; i++)
        inner_m.p_matrix[i] = (float *)calloc(sizeof(float), m.length - 1);
      for (int i = 1; i <= m.length - 1; i++)
        for (int k = 1; k <= m.width - 1; k++)
          inner_m.p_matrix[i - 1][k - 1] = m.p_matrix[i][(j + k) % m.width];
      result += m.p_matrix[0][j] * abs(inner_m);
    }
  }
  return result;
}
Matrix<float> identity(int n) {
  Matrix<float> identity = {n, n, (float **)calloc(sizeof(float *), n)};
  for (int i = 0; i < n; i++)
    identity.p_matrix[i] = (float *)calloc(sizeof(float), n);
  for (int i = 0; i < n; i++)
    identity.p_matrix[i][i] = 1;
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
  Matrix<float> cofactor = {m.length, m.width,
                          (float **)calloc(sizeof(float *), m.length)};
  for (int i = 0; i < m.length; i++)
    cofactor.p_matrix[i] = (float *)calloc(sizeof(float), m.width);
  if (det) {
    for (int i = 0; i < m.length; i++)
      for (int j = 0; j < m.width; j++) {
        Matrix<float> minor = {m.length - 1, m.width - 1,
                             (float **)calloc(sizeof(float *), m.length)};
        for (int k = 0; k < m.length - 1; k++)
          minor.p_matrix[k] = (float *)calloc(sizeof(float), m.width - 1);
        // creating minor
        for (int k = 1; k <= m.length - 1; k++) {
          int col = 0;
          for (int l = 0; l < m.width; l++) {
            if (l == j)
              continue;
            minor.p_matrix[k - 1][col++] = m.p_matrix[(i + k) % m.length][l];
          }
        }
        float min_det = abs(minor);
        cofactor.p_matrix[i][j] = min_det;
        if ((i + j) & 1)
          cofactor.p_matrix[i][j] *= -1;
      }
    Matrix<float> adjugate = transpose(cofactor);
    for (int i = 0; i < adjugate.length; i++)
      for (int j = 0; j < adjugate.width; j++)
        adjugate.p_matrix[i][j] /= det;
    return adjugate;
  } else
    throw std::invalid_argument("Matrix not invertible");
  // find minors of each element
}

// creates a row matrix from a point
Matrix<float> tuple_to_matrix(Tuple T) {
  Matrix<float> m = {1, T.dim, (float **)malloc(sizeof(float *))};
  float* row_m=(float*)calloc(sizeof(float),T.dim);
  m.p_matrix = &row_m;
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

Matrix<float> scale(int x, int y, int z) {
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
  rot_z_tr.p_matrix[0][0] = rot_z_tr.p_matrix[1][1] = cos(radians);
  rot_z_tr.p_matrix[1][0] = sin(radians);
  rot_z_tr.p_matrix[0][1] = -1 * sin(radians);
  return rot_z_tr;
}

Matrix<float> shear(int xy, int xz, int yx, int yz, int zx, int zy) {
  Matrix<float> shear_tr = identity(4);
  shear_tr.p_matrix[1][0] = yx, shear_tr.p_matrix[0][2] = zx,
  shear_tr.p_matrix[0][1] = xy, shear_tr.p_matrix[1][2] = zy,
  shear_tr.p_matrix[0][2] = xz, shear_tr.p_matrix[2][1] = yz;
  return shear_tr;
}
