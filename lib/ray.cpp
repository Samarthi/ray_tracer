#include "../include/ray.h"
#include "../include/tuple.h"
#include <iostream>
#include <math.h>
#include <climits>

Tuple ray_position(Ray r, float time) { return r.origin + r.direction * time; }

Ray transform(Ray r,Matrix<float> m){
	Matrix<float> m_origin = tuple_to_matrix(r.origin),
				m_direction = tuple_to_matrix(r.direction);
	Ray transformed_ray={matrix_to_tuple(m_origin*m),matrix_to_tuple(m_direction*m)};
	return transformed_ray;	
}

std::vector<Intersection>* intersect_sphere(Ray r, Sphere s) {
	Ray transformed_ray=transform(r,inverse(s.transform));
	Tuple sphere_to_ray = transformed_ray.origin - origin();
	float a = dot(transformed_ray.direction, transformed_ray.direction), b = 2 * dot(transformed_ray.direction, sphere_to_ray),
        c = dot(sphere_to_ray, sphere_to_ray) - 1;
    float d = (b * b) - (4 * a * c);
    if (d < 0)
		return NULL;
	std::vector<Intersection> *intersections = new std::vector<Intersection>{{s.obj_id, (-b + sqrt(d))/(2*a)}, {s.obj_id, (-b - sqrt(d))/(2*a)}};
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

void set_sphere_transform(Sphere *s,Matrix<float> m){
	s->transform=m;
}

void debug(std::vector<Intersection>& v){
	if(&v)
		for(int i=0;i<v.size();i++)
			std::cout<<"obj_id: "<<v[i].obj_id<<" t: "<<v[i].t<<std::endl;
}
