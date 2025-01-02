#pragma once
#include "tuple.h"
#include <vector>
#include <unordered_map>

struct Material{
	Tuple color=color3(1,1,1);
	float ambient=0.1, 
	diffuse=0.9,
	specular=0.9,
	shininess=200; 
};

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
  Material material;
};

Tuple ray_position(Ray r, float t);
std::vector<Intersection>* intersect_sphere(Ray r, Sphere s, std::vector<Intersection> *p_intersection_list=nullptr);
Intersection* hit(std::vector<Intersection>& v);
Ray transform(Ray r, Matrix<float> m);
void debug(std::vector<Intersection>& v);
Tuple normal_at(Sphere s, Tuple p);
Tuple reflect(Tuple in, Tuple normal);

struct Light{
	Tuple position,intensity;
};

Tuple lighting(Material m, Light l, Tuple point, Tuple eye, Tuple normal);

struct World{
	std::vector<Light> light_source_list;
	std::vector<Sphere> sphere_list;
};

World world();
std::vector<Intersection>* intersect_world(Ray r, World w);
