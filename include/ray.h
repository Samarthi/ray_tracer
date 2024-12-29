#include "tuple.h"
#include <vector>

struct Ray {
  Tuple origin, direction;
};

struct Intersection {
  int obj_id;
  float t;
};

struct Sphere {
  int obj_id;
  Matrix<int> transform;
};

Intersection hit(vector<Intersection> &v);
Ray transform(Ray r, Matrix<int> m);
