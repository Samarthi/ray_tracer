struct Tuple
{
  int dim;
  float *p_v;

  Tuple operator+(Tuple t1);
  Tuple operator-(Tuple t1);
  Tuple operator-();
  Tuple operator*(float scalar);
  Tuple operator/(float scalar);
};

float abs(Tuple t);
Tuple norm(Tuple t);
float dot(Tuple a, Tuple b);
Tuple cross(Tuple a, Tuple b);
Tuple point(float p_v[3]);
Tuple vector(float p_v[3]);
Tuple color(float p_v[3]);

template <typename T>
struct Matrix
{
  int length, width;
  T **p_matrix;

  Matrix<T> operator+(Matrix<T> m);
  bool operator==(Matrix<T> m);
  Matrix<T> operator*(Matrix<T> m);
  Matrix<T> operator-();
};
template <typename T>
Matrix<T> transpose(Matrix<T> m);
template <typename T>
float abs(Matrix<T> M);
Matrix<Tuple> canvas(int length, int width);
void canvas_to_ppm(Matrix<Tuple> canvas);
void write_pixel(Matrix<Tuple> *canvas, int height, int width, Tuple color);
