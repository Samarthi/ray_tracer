#include "../include/tuple.h"

#include <gtest/gtest.h>

TEST(TupleOperation, TupleAddition) {
  float f_a[3] = {3, -2, 5}, f_b[3] = {-2, 3, 1};
  Tuple a = point(f_a), b = vector(f_b);
  Tuple d = a + b;
  float f_c[3] = {1, 1, 6};
  Tuple c = point(f_c);
  EXPECT_EQ(d == c, true);
}
