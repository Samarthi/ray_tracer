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

Tuple normal_at(Sphere s, Tuple p){
	Tuple object_point = p*inverse(s.transform);
	Tuple normal=object_point-origin();
	//debug(inverse(s.transform));
	Tuple transformed_normal = normal*transpose(inverse(s.transform));
	transformed_normal.p_v[3]=0;
	return norm(transformed_normal);
}

void debug(std::vector<Intersection>& v){
	if(&v)
		for(int i=0;i<v.size();i++)
			std::cout<<"obj_id: "<<v[i].obj_id<<" t: "<<v[i].t<<std::endl;
}

Tuple reflect(Tuple in, Tuple normal){
	return in - normal * 2 * dot(in,normal);
}

Tuple lighting(Material m, Light l, Tuple point, Tuple eye, Tuple normal){
	Tuple effective_color = m.color * l.intensity;
	Tuple lightv = norm(l.position - point);
	Tuple ambient = effective_color * m.ambient;
	float ldn = dot(lightv,normal);
	Tuple diffuse, specular;
	if(ldn<0){
		diffuse = black();
		specular = black();
	}
	else {
		diffuse = effective_color * m.diffuse * ldn;
		Tuple reflectv = reflect(-lightv, normal);
		float reflect_dot_eye = dot(reflectv, eye);
		if (reflect_dot_eye<=0)
			specular = black();
		else {
			float factor = pow(reflect_dot_eye, m.shininess);
			specular = l.intensity * m.specular * factor;
		}	
	}
	return ambient + diffuse + specular;
}










