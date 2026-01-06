#include <gtest/gtest.h> 
#include "../include/canvas.h"
#include <cmath>


TEST(HelloTest, Vec3_Addition){
  Vec3 a = {3,-2,5}, b = {-2,3,1}, exp = {1,1,6};
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
  EXPECT_EQ(abs(a),exp_a);
  EXPECT_EQ(abs(b),exp_b);
  EXPECT_EQ(abs(c),exp_c);
  EXPECT_EQ(abs(d),exp_d);

}

TEST(HelloTest, Vec3_Normalisation){
  Vec3 a = {4,0,0}, exp_a = {1, 0, 0}, b = {1,2,3}, exp_b = {0.2672, 0.5345, 0.8017};
  debug(norm(a));
  debug(norm(b));
  EXPECT_EQ(norm(a), exp_a);
  EXPECT_EQ(norm(b), exp_b);
}

TEST(HelloTest, Vec3Dot){
  Vec3 a = {1,2,3}, b = {2,3,4};
  float expected = 20;
  EXPECT_EQ(dot(a,b),expected);
}

TEST(HelloTest, Vec3_Cross){
  Vec3 a = {1,2,3}, b = {2,3,4}, expected = {-1, 2, -1};
  EXPECT_EQ(cross(a,b), expected);
  EXPECT_EQ(cross(b,a), -expected);
}

TEST(HelloTest, Vec4_Addition){
  Vec4 a = {3,-2,5,0}, b = {-2,3,1,1}, exp = {1,1,6, 1};
  Vec4 result = a+b;
  EXPECT_EQ(result, exp);
  a+=b;
  EXPECT_EQ(a,exp);
}

TEST(HelloTest, Vec4_Subtraction){
  Vec4 a = {3,2,1,0}, b = {5,6,7,0} ,exp = {-2,-4,-6,0};
  Vec4 result = a - b;
  EXPECT_EQ(result, exp);
  a-=b;
  EXPECT_EQ(a,exp); 
}

TEST(HelloTest, Vec4_Negation){
  Vec4 a = {1,2,-3,0},exp = {-1,-2,3,0};
  Vec4 result = -a;
  EXPECT_EQ(result, exp); 
}

TEST(HelloTest, Vec4_Scaling){
  Vec4 a = {1, -2, 3, 0}, exp1 = {1.5, -3, 4.5, 0}, exp2 = {1, -2, 3, 0};
  Vec4 result = a*1.5f;
  EXPECT_EQ(result,exp1);
  a*=1.5f;
  EXPECT_EQ(a,exp1);
  result= a/1.5f;
  EXPECT_EQ(result,exp2);
  a/=1.5f;
  EXPECT_EQ(a,exp2);
}

TEST(HelloTest, Vec4_Magnitude){
  Vec4 a = {0,1,0,0}, b = {0,0,1,1}, c={1,2,3,0}, d={-1,-2,-3, 1};
  float exp_a = 1, exp_b =1, exp_c = sqrt(14), exp_d = sqrt(14);
  EXPECT_EQ(abs(a),exp_a);
  EXPECT_EQ(abs(b),exp_b);
  EXPECT_EQ(abs(c),exp_c);
  EXPECT_EQ(abs(d),exp_d);

}

TEST(HelloTest, Vec4_Normalisation){
  Vec4 a = {4,0,0, 0}, exp_a = {1, 0, 0, 0}, b = {1,2,3, 0}, exp_b = {0.2672, 0.5345, 0.8017,0.000};
  EXPECT_EQ(norm(a), exp_a);
  EXPECT_EQ(norm(b), exp_b);
}

TEST(HelloTest, Vec4_Dot){
  Vec4 a = {1,2,3,0}, b = {2,3,4,0};
  float expected = 20;
  EXPECT_EQ(dot(a,b),expected);
}

TEST(HelloTest, Vec4_Cross){
  Vec4 a = {1,2,3,0}, b = {2,3,4,0}, expected = {-1, 2, -1, 0};
  EXPECT_EQ(cross(a,b), expected);
  EXPECT_EQ(cross(b,a), -expected);
}

TEST(HelloTest, Mat4_Inverse){
  Mat4 m = {-5,2,6,-8,1,-5,1,8,7,7,-6,-7,1,-3,7,4},
  expected = {0.21805,0.45113,0.24060,-0.04511,-0.80827,
			  -1.45677,-0.44361,0.52068,-0.07895,-0.22368,-0.05263,
			  0.19737,-0.52256,-0.81391,-0.30075,0.30639};
  Mat4 result = inverse(m);
  for(int i=0;i<4;++i){
    for(int j=0;j<4;++j)
      std::cout<<expected[i][j]<<' ';
  }
  std::cout<<std::endl;
  for(int i=0;i<4;++i){
    for (int j = 0; j < 4; ++j)
      std::cout<<result[i][j]<<' ';
  }
  std::cout<<std::endl;
  EXPECT_EQ(result,expected);
}

TEST(HelloTest, Geometry_Integration){
}

TEST(HelloTest, ReadPPM){
  Canvas cnv = ppm_to_canvas("../data/boolean_sphere.ppm");
  canvas_to_ppm(cnv, "scene.ppm");
}