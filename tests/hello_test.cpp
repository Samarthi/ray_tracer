#include <gtest/gtest.h>
#include "../include/vec.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest, Vec3_Addition){
  Vec3 a = {3,-2,5};
  const Vec3 b = {-2,3,1}, exp = {1,1,6};
  Vec3 result = a+b;
  EXPECT_EQ(result, exp);
  a+=b;
  EXPECT_EQ(a,exp);
}

