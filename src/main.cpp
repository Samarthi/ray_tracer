#include "../include/tuple.h"
#include "../include/ray.h"
#include <math.h>
#include <iostream>

int main() {
  Tuple r_origin = origin();  
  r_origin.p_v[2] = -5;
  float wall_z = 10, wall_size = 7, canvas_size = 100, pixel_size = wall_size/canvas_size, half = wall_size/2 ;
  float black[3] = {0.0, 0.0, 0.0};
  Matrix<Tuple> m = canvas(canvas_size, canvas_size);
  Sphere s = {1,identity(4)};

  for (int i = 0; i < canvas_size; ++i) {
    float world_y = half - pixel_size * i;
    for(int j = 0; j < canvas_size; ++j){
		float world_x = -half + pixel_size * j;
		float f_position[3] = {world_x, world_y, wall_z};
		Tuple t_position = point(f_position);
		Tuple direction = norm(t_position - r_origin);
		Ray r= {r_origin, norm( t_position - r_origin )};
		std::vector<Intersection>* intersection_list = intersect_sphere(r,1);
		if (hit(*intersection_list)!=NULL){
			write_pixel(&m, j, i, color(black));
		}
    }
  }
  canvas_to_ppm(m);
}
