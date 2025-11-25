#include "../include/tuple.h"
#include "../include/ray.h"
#include <math.h>
#include <iostream>

int main() {
  Tuple r_origin = origin();  
  r_origin.p_v[2] = -5.0;
  float wall_z = 10, wall_size = 7, canvas_size = 500, pixel_size = wall_size/canvas_size, half = wall_size/2 ;
  float black[3] = {0.0, 0.0, 0.0};
  Matrix<Tuple> m = canvas(canvas_size, canvas_size);
  Material mat;
  Sphere s = {1,identity(4),mat};
  s.material.color=color3(95,0,133);
  Light light={point3(-10,10,-10),color3(1,1,1)};
  	
  for (int i = 0; i < canvas_size; ++i) {
    float world_y = half - pixel_size * i;
    for(int j = 0; j < canvas_size; ++j){
			float world_x = -half + pixel_size * j;
			float f_position[3] = {world_x, world_y, wall_z};
			Tuple t_position = point(f_position);
			Tuple direction = norm(t_position - r_origin);
			Ray r= {r_origin, norm( t_position - r_origin )};
			std::vector<Intersection>* intersection_list = intersect_sphere(r,s);
			Intersection* hit_p = hit(*intersection_list);
			if (hit_p!=NULL){
				Tuple p = ray_position(r,hit_p->t);
				Tuple normal = normal_at(s,p);
				Tuple eye = r.direction*-1; 
				Tuple pixel_color = lighting(s.material, light, p, eye, normal);
				write_pixel(&m, j, i, pixel_color);
			}
    }
  }
  canvas_to_ppm(m);
}
