#include "../include/tuple.h"
#include <algorithm>
#include <malloc.h>

Matrix<Tuple> canvas(int length, int width) {
  float white[3] = {255, 255, 255};
  Matrix<Tuple> m = {length, width, (Tuple **)malloc(sizeof(Tuple *) * length)};
  for (int i = 0; i < length; ++i) {
    m.p_matrix[i] = (Tuple *)malloc(sizeof(Tuple) * width);
    std::fill(m.p_matrix[i], m.p_matrix[i] + width, color(white));
  }
  return m;
}
bool is_within_canvas_bounds(Matrix<Tuple> *canvas, int height, int width) {
  if (height < 0 or height > canvas->length)
    return false;
  if (width < 0 or width > canvas->width)
    return false;
  return true;
}
void write_pixel(Matrix<Tuple> *canvas, int height, int width, Tuple color) {
  if (is_within_canvas_bounds(canvas, height, width))
    canvas->p_matrix[height][width] = color;
}
