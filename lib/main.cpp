#include "../include/tuple.h"
#include <math.h>

int main()
{
  float black[3] = {0.0, 0.0, 0.0};
  Matrix m = canvas(1000, 1000);
  int prev = -1;
  for (float i = 0; i < 1000; i += 0.8)
  {
    int x = i, y = ceil(x * x);
    while (++prev <= y)
      write_pixel(&m, x, prev, color(black));
  }
  canvas_to_ppm(m);
  return 0;
}
