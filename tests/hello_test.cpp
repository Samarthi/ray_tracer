#include <gtest/gtest.h>
#include "../include/vec.h"
#include <cmath>

TEST(HelloTest, Vec3_Addition){
  Vec3 a = {3,-2,5};
  const Vec3 b = {-2,3,1}, exp = {1,1,6};
  Vec3 result = a+b;
  EXPECT_EQ(result, exp);
  a+=b;
  EXPECT_EQ(a,exp);
}

TEST(HelloTest, Vec3_Subtraction){
  Vec3 a = {3,2,1}, b = {5,6,7} ,exp = {-2,-4,-6};
  Vec3 result = a - b;
  EXPECT_EQ(result, exp);
  a-=b;
  EXPECT_EQ(a,exp); 
}

TEST(HelloTest, Vec3_Negation){
  Vec3 a = {1,2,-3},exp = {-1,-2,3};
  Vec3 result = -a;
  EXPECT_EQ(result, exp); 
}


TEST(HelloTest, Vec3_Scaling){
  Vec3 a = {1, -2, 3}, exp1 = {1.5, -3, 4.5}, exp2 = {1, -2, 3};
  Vec3 result = a*1.5f;
  EXPECT_EQ(result,exp1);
  a*=1.5f;
  EXPECT_EQ(a,exp1);
  result= a/1.5f;
  EXPECT_EQ(result,exp2);
  a/=1.5f;
  EXPECT_EQ(a,exp2);
}

TEST(HelloTest, Vec3_Magnitude){
  Vec3 a = {0,1,0}, b = {0,0,1}, c={1,2,3}, d={-1,-2,-3};
  float exp_a = 1, exp_b =1, exp_c = sqrt(14), exp_d = sqrt(14);
  EXPECT_EQ(a,exp_a);
  EXPECT_EQ(b,exp_b);
  EXPECT_EQ(c,exp_c);
  EXPECT_EQ(d,exp_d);

}
