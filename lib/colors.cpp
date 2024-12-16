#include "../include/tuple.h"
#include <malloc.h>

Tuple color(float *p_v) {
  Tuple t = {3, (float *)malloc(sizeof(float) * 3)};
  for (int i = 0; i < 3; ++i)
    t.p_v[i] = p_v[i];
  return t;
}
