#pragma once
#define PI 3.14f

bool eq(float f1, float f2);

template <typename T> struct Matrix {
  int length, width;
  T **p_matrix;

  Matrix<T> operator+(Matrix<T> m);
  bool operator==(Matrix<T> m);
  Matrix<T> operator*(Matrix<T> m);
  Matrix<T> operator-();
};
\

struct Tuple {
  int dim;
  float *p_v;
  bool operator==(Tuple t1);
  Tuple operator+(Tuple t1);
  Tuple operator-(Tuple t1);
  Tuple operator-();
  Tuple operator*(float scalar);
  Tuple operator/(float scalar);
  Tuple operator*(Matrix<float> m);
  Tuple operator*(Tuple t);
};
Tuple origin();
Tuple black();
void debug(Tuple t);
float abs(Tuple t);
Tuple norm(Tuple t);
float dot(Tuple a, Tuple b);
Tuple cross(Tuple a, Tuple b);
Tuple point(float p_v[3]);
Tuple vector(float p_v[3]);
Tuple color(float p_v[3]);
Tuple point3(float x,float y, float z);
Tuple vec3(float x, float y, float z);
Tuple color3(float red, float blue, float green);

Matrix<float> identity(int n);
template <typename T> Matrix<T> transpose(Matrix<T> m);
template <typename T> float abs(Matrix<T> M);
Matrix<Tuple> canvas(int length, int width);
void canvas_to_ppm(Matrix<Tuple> canvas);
void write_pixel(Matrix<Tuple> *canvas, int height, int width, Tuple color);
Matrix<float> tuple_to_matrix(Tuple t);
Tuple matrix_to_tuple(Matrix<float> m);
void debug(Matrix<float> m);
float abs(Matrix<float> m);
Matrix<float> transpose(Matrix<float> m);
Matrix<float> inverse(Matrix<float> m);
Matrix<float> create_matrix(int l, int w, float *p_v);
Matrix<float> translate(int x, int y, int z);
Matrix<float> scale(float x, float y, float z);
Matrix<float> rot_x(float radians);
Matrix<float> rot_y(float radians);
Matrix<float> rot_z(float radians);
Matrix<float> shear(float xy, float xz, float yx, float yz, float zx, float zy);

