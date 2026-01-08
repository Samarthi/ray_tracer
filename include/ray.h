#pragma once
#include "vec.h"
#include "math.h"

#define T_MAX 0x7f7fffff

inline float max(float a, float b){
  return a > b ? a : b;
}

inline float min(float a, float b){
  return a < b ? a: b;
}

struct Canvas{
	int h,w;
	Vec3** contents;
};

struct Material{
  Vec3 colour;
  float ambient, diffuse, specular, shininess;
};

struct Ray {
  Vec4 origin, direction;
};

// negative t indicates no intersection
struct Intersection{
  float t;
  Vec4 p, normal;
  const Material *mat;
};

union Triangle{
  struct{
    Vec4 v0,v1,v2;
  };
  
  Vec4 vertices[3];
};

struct Sphere{
  Vec4 origin;
  float radius;
  Material mat;
};

struct Object{
  int triangle_count;
  Triangle *triangles;
  Material material;
};

struct Light{
  Vec4 position;
  Vec3 ambient_colour;
};

struct Camera{
  Mat4 view;
  Mat4 proj;
  Vec4 origin;
};

struct SceneConfig{
  int object_count;
  Object *objects;
  
  int sphere_count;
  Sphere *spheres;
  
  Camera camera;
  
  int light_count;
  Light* lights;
};

inline Vec4 ray_at(const Ray &r, float t){
  return r.origin + r.direction * t;
}

inline Vec4 normal_at_tr(const Triangle &tr, const Vec4 &p){
  return p - cross(tr.v2 - tr.v0, tr.v1 - tr.v0);
}

inline Vec4 normal_at_sph(const Sphere &sph, const Vec4 &p){
  return p - sph.origin;
}

inline Intersection intersect_sphere(const Ray &r, const Sphere &s){
  //uses implicit equation (O+tD-C)^2 - R^2 = 0
  
  //D^2t^2 + 2(O-C)D*t + (O-C)^2-R^2 = 0
  
  Vec4 oc = r.origin - s.origin;
  float a = dot(r.direction, r.direction);
  float b = 2 * dot(r.origin - s.origin,r.direction);
  float c = dot(oc, oc) - s.radius * s.radius; 
  
  Intersection it;
  //DISCRIMINANT  
  float discriminant = b * b - 4 * a * c;
  
  if (discriminant < 0.0f){
    it = {-1};
    return it;
  }
  
  float inv2a = 1.0f / (2.0f * a);

  if(float_eq(discriminant, 0.0f)) it.t = -b * inv2a;
  else it.t = min((-b - sqrt(discriminant)), (-b + sqrt(discriminant))) * inv2a;
  it.p = ray_at(r, it.t);
  it.normal = normal_at_sph(s, it.p);
  it.mat = &s.mat;
  return it;
}

inline Intersection intersect_triangle(const Ray &r, const Triangle &tr){
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
  it.p = ray_at(r, t);
  it.normal = normal_at_tr(tr, p);
  return it;

}

inline Vec4 reflect(const Vec4 &incident, const Vec4 &normal){
  return incident - normal * 2 * dot(incident, normal);
}

inline Vec3 shade(const Intersection &it, int light_count, const Light *lights, const Camera &cam){
  Vec3 colour = {0,0,0};
  float inv_light_count = 1/light_count;
  for(int i = 0; i < light_count; ++i){
    // light direction
    Vec4 l_dir = norm(lights[i].position - it.p);
    Vec4 reflected = norm(reflect(l_dir, it.normal));
    Material mat = *it.mat;
    
    // diffuse
    float diffuse_intensity = dot(it.normal, l_dir);
    Vec3 diffuse = mat.colour * mat.diffuse * max(diffuse_intensity, 0);

    // specular
    Vec3 specular = mat.colour * mat.specular * pow(max(0, dot(reflected, norm(cam.origin - it.p))), mat.shininess);

    // ambient
    Vec3 ambient = lights[i].ambient_colour * mat.ambient;
    colour =  (diffuse + specular + ambient) * inv_light_count;
  }
  return colour;
}

inline Vec3 intersect_scene(const Ray &r, const SceneConfig &sc){
  float t = T_MAX;
  Intersection it;
  for(int i = 0; i < sc.sphere_count; ++i){
    Intersection temp = intersect_sphere(r, sc.spheres[0]);
    if (t > 0 && t > temp.t) it = temp;
  }
  
  for(int i = 0; i < sc.object_count; ++i){
    for(int j = 0; j < sc.objects[i].triangle_count; ++j){
      Intersection temp = intersect_triangle(r, sc.objects[i].triangles[j]);
      if (t > 0 && t > temp.t) it = temp;
    }
  }
  
  if (t == T_MAX)
    return {0.0, 0.0, 0.0};
  
  return shade(it, sc.light_count, sc.lights, sc.camera);
}