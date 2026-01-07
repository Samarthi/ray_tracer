#include "vec.h"
#include "math.h"

inline max(float a, float b){
  return a>b?a:b;
}

struct Canvas{
	int h,w;
	Vec3** contents;
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

struct Ray {
  Vec4 origin, direction;
};

// negative t indicates no intersection
struct Intersection{
  float t;
  Vec4 p, normal;
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
  Material material;
};

struct Light{
  Vec4 position;
  Vec3 color;
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
  Light light;
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
  it.p = ray_at(r, t);
  it.normal = norm(p - cross(e, f));
  return it;

}

inline Vec4 normal_at(const Triangle &tr, const Vec4 &p){
  return p-cross(tr.v2 - tr.v0, tr.v1 - tr.v0);
}

inline Vec4 reflect(const Vec4 &incident, const Vec4 &normal){
  return incident - normal * 2 * dot(incident, normal);
}

inline Vec3 shade(const Intersection &it, const Light &light, const Material &mat, const Camera &cam){
  Vec3 color;
  // light direction
  Vec4 l_dir = norm(light.position - it.p);
  Vec4 reflected = norm(reflect(l_dir, it.normal));
  
  // diffuse
  float diffuse_intensity = dot(it.normal, l_dir)
  Vec3 diffuse = mat.color * mat.diffuse * max(diffuse_intensity, 0);

  // specular
  Vec3 specular = mat.color * mat.specular * pow(max(0, dot(reflected, norm(cam.origin - it.p))), shininess);

  // ambient
  Vec3 ambient = mat.color * mat.ambient;

  return diffuse+specular+ambient;
}