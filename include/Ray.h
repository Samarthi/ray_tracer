#include "vec.h"
#include "math.h"

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
 
inline SphereIntersections intersect_sphere(const Ray &r, const Sphere &s){
  SphereIntersections it;

  //uses implicit equation (O+tD-C)^2 - R^2 = 0

  //D^2t^2 + 2(O-C)D*t + (O-C)^2-R^2 = 0
  Vec4 oc = r.origin - s.origin;
  float a = dot(r.direction, r.direction);
  float b = 2*dot(r.origin - s.origin,r.direction);
  float c = dot(oc, oc) - s.radius*s.radius; 
  
  //DISCRIMINANT  
  float discriminant = b*b - 4*a*c;
  
  if (discriminant<0.0f){
    it.hits = 0;
    return it;
  }
  
  float inv2a = 1.0f / (2.0f * a);
  
  if(float_eq(discriminant,0.0f)){
    it.hits = 1;
    it.hit1 = -b*inv2a;
    return it;
  }
  
  it.hits = 2;
  it.hit1 = (-b - sqrt(discriminant))*inv2a;
  it.hit2 = (-b + sqrt(discriminant))*inv2a;
  return it;
}

Intersection hit(const SphereIntersections &s){

}
Vec4 normal_at(const Sphere &s, const Vec4 &p);
Vec4 reflect(const Vec4 &incident, const Vec4 &normal);