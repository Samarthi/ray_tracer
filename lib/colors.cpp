#include "../include/tuple.h"
#include <malloc.h>

Tuple color(float *p_v)
{
  Tuple t = {3, (float *)malloc(sizeof(float) * 3)};
  for (int i = 0; i < 3; ++i)
    t.p_v[i] = p_v[i];
  return t;
}

Tuple color3(float red, float blue, float green)
{
	float arr[3]={red,blue,green};
	return color(arr);
}
