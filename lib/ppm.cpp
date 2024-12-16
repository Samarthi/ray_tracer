#include "../include/tuple.h"
#include <iostream>

void canvas_to_ppm(Matrix<Tuple> canvas) {
  freopen("scene.ppm", "w", stdout);
  // write header
  std::cout << "P3\n" << canvas.width << ' ' << canvas.length << "\n255\n";
  // write body
  for (int i = 0; i < canvas.length; ++i) {
    for (int j = 0; j < canvas.width; ++j)
      for (int k = 0; k < canvas.p_matrix[i][j].dim; ++k)
        std::cout << canvas.p_matrix[i][j].p_v[k] << ' ';
    std::cout << '\n';
  }
}
