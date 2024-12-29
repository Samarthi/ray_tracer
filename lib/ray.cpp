#include "../include/ray.h"
#include "../include/tuple.h"
#include <iostream>
#include <pair>
#include <vector>

Tuple ray_position(Ray r, float time) { return r.origin + r.direction * time; }

std::vector<Intersection> *intersect_sphere(Ray r, int obj_id) {
  Tuple sphere_to_ray = r.origin - point(origin());
  float a = dot(r.origin, r.direction), b = 2 * dot(r.direction, sphere_to_ray),
        c = dot(sphere_to_ray, sphere_to_ray) - 1;
  float d = b * b - 4 * a * c;
  if (d < 0)
    return NULL;
  std::vector<Intersection> *intersections =
      new vector<Intersection>{{obj_id, -b + d}, {obj_id, -b - d}};
  return intersections;
}

Intersection *hit(vector<Intersection> &v) {
  float mini = 0;
  Intersection *result = NULL;
  for (auto &i : v) {
    if (v.t >= 0)
      if (v.t < mini) {
        mini = v.t;
        result = &(*i);
      }
  }
  return result;
}
