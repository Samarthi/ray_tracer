#include "../include/ray.h"
#include "../include/tuple.h"
#include <iostream>
#include <math.h>

Tuple ray_position(Ray r, float time) { return r.origin + r.direction * time; }

std::vector<Intersection>* intersect_sphere(Ray r, int obj_id) {
  Tuple sphere_to_ray = r.origin - origin();
  float a = dot(r.direction, r.direction), b = 2 * dot(r.direction, sphere_to_ray),
        c = dot(sphere_to_ray, sphere_to_ray) - 1;
  float d = (b * b) - (4 * a * c);
  if (d < 0)
    return NULL;
  std::vector<Intersection> *intersections =
      new std::vector<Intersection>{{obj_id, (-b + sqrt(d))/(2*a)}, {obj_id, (-b - sqrt(d))/(2*a)}};
  return intersections;
}

Intersection* hit(std::vector<Intersection>& v) {
  float mini = INT_MAX;
  Intersection *result = NULL;
  if (&v==NULL)
	return result;
  for (int i=0;i<v.size();i++) {
    if (v[i].t >= 0)
      if (v[i].t < mini) {
        mini = v[i].t;
        result = &v[i];
      }
  }
  return result;
}

Ray transform(Ray r,Matrix<float> m){
	Matrix<float> m_origin = tuple_to_matrix(r.origin),
				m_direction = tuple_to_matrix(r.direction);
	Ray transformed_ray={matrix_to_tuple(m_origin*m),matrix_to_tuple(m_direction*m)};
	return transformed_ray;	
}

void set_sphere_transform(Sphere *s,Matrix<float> m){
	s->transform=m;
}


void debug(std::vector<Intersection>& v){
	if(&v)
		for(int i=0;i<v.size();i++)
			std::cout<<"obj_id: "<<v[i].obj_id<<" t: "<<v[i].t<<std::endl;
}
