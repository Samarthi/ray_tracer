#include <malloc.h>
#include <math.h>
#include <stdexcept>
#define EPS 0.00001

struct Tuple {
  int dim = 4;
  float *p_v;

  Tuple operator+(Tuple t1) {
    Tuple r = {this->dim, (float *)malloc(sizeof(float) * this->dim)};
    for (int i = 0; i < this->dim; ++i)
      r.p_v[i] = this->p_v[i] + t1.p_v[i];
    return r;
  }

  Tuple operator-(Tuple t1) {
    Tuple r = {this->dim, (float *)malloc(sizeof(float) * this->dim)};
    for (int i = 0; i < this->dim; ++i)
      r.p_v[i] = this->p_v[i] - t1.p_v[i];
    return r;
  }

  Tuple operator-() {

    Tuple r = {this->dim, (float *)malloc(sizeof(float) * this->dim)};
    for (int i = 0; i < this->dim; ++i)
      r.p_v[i] = -(this->p_v[i]);
    return r;
  }

  Tuple operator*(float scalar) {
    Tuple r = {this->dim, (float *)malloc(sizeof(float) * this->dim)};
    for (int i = 0; i < this->dim; ++i)
      r.p_v[i] = this->p_v[i] * scalar;
    return r;
  }

  Tuple operator/(float scalar) {
    Tuple r = {this->dim, (float *)malloc(sizeof(float) * this->dim)};
    for (int i = 0; i < this->dim; ++i)
      r.p_v[i] = this->p_v[i] /= scalar;
    return r;
  }
};
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
  Tuple r = {a.dim, (float *)malloc(sizeof(float) * a.dim)};
  int mod = a.dim - 1;
  for (int i = 0; i < a.dim; i++)
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
template <class T> struct Matrix {
  int length, width;
  T **p_matrix;

  bool operator==(Matrix m) {
    if (this->length != m.length)
      return false;
    if (this->width != m.width)
      return false;
    for (int i = 0; i < this->length; i++)
      for (int j = 0; j < this->width; j++)
        if (this->p_matrix[i][j] != m.p_matrix[i][j])
          return false;
    return true;
  }

  Matrix operator*(Matrix m) {
    if (this->width != m.length)
      throw std::invalid_argument("this->width!=m.length");
    Matrix result;
    result.length = this->length;
    result.width = m.width;
    for (int i = 0; i < result.length; i++)
      result.p_matrix[i] = (T *)calloc(result.width, sizeof(T));
    for (int i = 0; i < this->length; i++) {
      for (int j = 0; j < m.width; j++)
        for (int k = 0; k < this->width; k++) {
          result.p_matrix[i][j] += this->p_matrix[i][k] * m.p_matrix[k][i];
        }
    }
  }
};

int abs(Matrix<int> m) {
  int result=0;
  for(int i=0;i<m.width;i++){
    if(m.length<=3){
      int inner_det=(m.p_matrix[1][(j+1)%3]*m.p_matrix[2][(j+2)%3]-m.p_matrix[1][(j+2)%m]*m.p_matrix[2][(j+1)%3]);
      result+=m.p_matrix[0][i]*inner_det;
    }
    else{
      Matrix<int> inner_m={m.length-1,m.width-1,(int**)calloc(m.length-1,sizeof(int*))};
      for(int j=0;j<m.length-1;j++)
        inner_m.p_matrix[j]=(int)calloc(m.length-1,sizeof(int));
      for(int j=1;j<=m.length-1;j++)
        for(int k=1;k<=m.width-1;k++)
          inner_m.p_matrix[j-1][i]=m.p_matrix[j][(j+k)%m.width];
      result+=m.p_matrix[0][i]*abs(inner_m);   
    }
  }
  return result;
}
Matrix<int> transpose(Matrix<int> m){
  for(int i=0;i<m.length;i++)
    for(int j=i+1;j<m.width;j++)
      std::swap(m.p_matrix[i][j],m.p_matrix[j][i]);
  return m;
}

Matrix<int> inverse(Matrix<int> m) {
  int det=abs(m);
  Matrix<int> cofactor={m.length,m.width,(int**)calloc(m.length,sizeof(int*))};
  for(auto &p_c:cofactor)
    p_c=(int)calloc(m.width,sizeof(int));
  if(det){
    for(int i=0;i<m.length;i++)
      for(int j=0;j<m.width;j++){
        Matrix<int> minor={m.length-1,m.width-1,(int**)calloc(m.length,sizeof(int*))};
        for(auto &p_m:minor)
          p_m=(int)calloc(m.width-1,sizeof(int));
        //TODO: prove changing order of rows in matrix doesn't change determinant: (seems obvious tho)
        //creating minor 
        for(int k=1; k<=m.length-1; k++){
          int col=0;
          for(int l=0; l<m.width; l++)
            if(l==j)
              continue;
            minor.p_matrix[k-1][col++]=m.p_matrix[(i+k)%m.length][l];
        }
        int min_det=abs(minor);
        cofactor.p_matrix[i][j]=min_det;
        if((i+j)&1)
          cofactor.p_matrix[i][j]*=-1;
      }
    Matrix<int> adjugate=transpose(cofactor);
    for(auto &row:adjugate)
      for(auto &cell:row)
        cell/=det;
    return adjugate;    
  }
  else throw std::invalid_argument<"Matrix not invertible">;
  // find minors of each element
}
