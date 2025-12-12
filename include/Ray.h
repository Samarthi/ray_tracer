#include "vec.h"

struct Ray {
  Vec4 origin, direction;
};

struct Sphere{
  int id;
  Vec4 center;
  float radius;
};

struct Intersection{
  int id;
  float t;
  Vec4 p, normal;
  Material *mat;
};

struct Light{
  Vec4 pos;
  Vec3 intensity;
};

struct Material{
  Vec4 colour;
  union{
    struct{
      float ambient, diffuse, specular, shininess;
    };
    float props[4];
  };
};

struct Camera{
  Mat4 view;
  Mat4 proj;
  Vec4 origin;
};

struct SphereIntersections{
  Intersection hit1, hit2;
  int hits;
};

inline Vec4 ray_at(const Ray &r, float t){
  return r.origin + r.direction * t;
}

SphereIntersections intersect_sphere(const Ray &r, const Sphere &s);
Intersection hit(const SphereIntersections &);
Vec4 normal_at(const Sphere &s, const Vec4 &p);
Vec4 reflect(const Vec4 &incident, const Vec4 &normal);