#include "vec.h"
#include "math.h"

struct Canvas{
	int h,w;
	Vec3** contents;
};

struct Ray {
  Vec4 origin, direction;
};

struct Sphere{
  int id;
  Vec4 origin;
  float radius;
};

struct Material{
  Vec3 colour;
  union{
    struct{
      float ambient, diffuse, specular, shininess;
    };
    float props[4];
  };
};

struct Intersection{
  float t;
  Vec4 p, normal;
  Material *mat;
  bool tangent = false;
};

struct Light{
  Vec4 pos;
  Vec3 intensity;
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

struct SceneConfig{
  int object_count;
  Sphere *shape;
  Camera camera;
};

inline Vec4 ray_at(const Ray &r, float t){
  return r.origin + r.direction * t;
}
 
inline Intersection intersect_sphere(const Ray &r, const Sphere &s){  
  //uses implicit equation (O+tD-C)^2 - R^2 = 0

  //D^2t^2 + 2(O-C)D*t + (O-C)^2-R^2 = 0
  Vec4 oc = r.origin - s.origin;
  float a = dot(r.direction, r.direction);
  float b = 2*dot(r.origin - s.origin,r.direction);
  float c = dot(oc, oc) - s.radius*s.radius; 
  
  //DISCRIMINANT  
  float discriminant = b*b - 4*a*c;
  
  if (discriminant<0.0f){
    Intersection it = {0};
    return it;
  }
  
  float inv2a = 1.0f / (2.0f * a);
  
  if(float_eq(discriminant,0.0f)){
    Intersection it1; it1.t = -b*inv2a;
    it1.tangent = true;
    return it1;
  }
  
  Intersection it1; it1.t = (-b - sqrt(discriminant))*inv2a;
  Intersection it2; it2.t = (-b + sqrt(discriminant))*inv2a;
  return it1.t<it2.t?it1:it2;
}

inline Vec4 normal_at(const Sphere &s, const Vec4 &p){
  return p - s.origin;
}

inline Vec4 reflect(const Vec4 &incident, const Vec4 &normal){
  return incident - normal * 2 * dot(incident, normal);
}
