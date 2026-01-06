#include "vec.h"
#include "math.h"

struct Canvas{
	int h,w;
	Vec3** contents;
};

struct Ray {
};

struct Material;
// negative t indicates no intersection
struct Intersection{
  float t;
  Vec4 p, normal;
  Material *mat;
};

union Triangle{
  struct{
    Vec4 v0,v1,v2;
  };
  
  Vec4 vertices[3];
};

struct Object{
  int triangle_count;
  Triangle **triangles;
};

struct Light{
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

struct SceneConfig{
  int object_count;
  Object **objects;
  Camera camera;
};

inline Vec4 ray_at(const Ray &r, float t){
  return r.origin + r.direction * t;
}

inline Intersection intersect_triangle(const Triangle &tr, const Ray &r){
  Vec4 e = tr.v2 - tr.v0, f = tr.v1 - tr.v0, b = r.origin - tr.v0;
  
  Vec4 q = cross(r.direction, e);
  float d = dot(f, q);
  Intersection it;
  it.t = -1; 
  
  //d test
  if(float_eq(d, 0.0f) || d < 0.0f) return it;
  
  float inv_d = 1.0f / d;
  float u = dot(b, q) * inv_d;
  if (u < 0.0f || u > 1.0f) return it;

  Vec4 p = cross(b, f);

  float v = dot(r.direction, p) * inv_d;
  if (v < 0.0f || u + v > 1.0f) return it;

  float t = dot(e, p) * inv_d; 
  
  if (t < 0.0f) return it;
  
  it.t = t;
  it.p = ray_at(r,t);
  return it;

}

inline Vec4 normal_at(const Triangle &tr, const Vec4 &p){
  return p-cross(tr.v2 - tr.v0, tr.v1 - tr.v0);
}

inline Vec4 reflect(const Vec4 &incident, const Vec4 &normal){
  return incident - normal * 2 * dot(incident, normal);
}
