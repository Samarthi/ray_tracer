#pragma once
#include "tuple.h"
#include <bits/stdc++.h>
#include <iostream>

struct Ray {
  Tuple origin, direction;
};

struct Intersection {
  int obj_id;
  float t;
};

struct Sphere {
  int obj_id;
  Matrix<float> transform;
};

Tuple ray_position(Ray r, float t);
std::vector<Intersection>* intersect_sphere(Ray r, int obj_id);
Intersection* hit(std::vector<Intersection>& v);
Ray transform(Ray r, Matrix<float> m);
void debug(std::vector<Intersection>& v);
