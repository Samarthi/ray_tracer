#include "Vec.h"
#include <cmath>

inline Vec4 point(float x, float y, float z){
	Vec4 result  = {x,y,z,1};
	return result;
}

inline Vec4 vector(float x, float y, float z){
	Vec4 result  = {x,y,z,0};
	return result;
}

inline Mat4 translate(float tx, float ty, float tz){
	Mat4 result = identity();
	result[0][3] = tx;
	result[1][3] = ty;
	result[2][3] = tz;
	return result;
}

inline Mat4 scale(float sx, float sy, float sz){
	Mat4 result = identity();
	result[0][0]=sx;
	result[1][1]=sy;
	result[2][2]=sz;
	return result;
}


Mat4 rot_x(float theta){
	Mat4 result = identity();
	float cosine = cos(theta), sine = sin(theta);
	result[1][1] = cosine;
	result[2][1] = -sine;
	result[1][2] = sine;
	result[2][2] = cosine;
	return result;
}

Mat4 rot_y(float theta){
	Mat4 result = identity();
	float cosine = cos(theta), sine = sin(theta);
	result[0][0] = cosine;
	result[2][0] = -sine;
	result[0][2] = sine;
	result[2][2] = cosine;
	return result;
}

Mat4 rot_z(float theta){
	Mat4 result = identity();
	float cosine = cos(theta), sine = sin(theta);
	result[0][0] = cosine;
	result[1][0] = -sine;
	result[0][1] = sine;
	result[1][1] = cosine;
	return result;
}


Mat4 look_at(const Vec4 &eye, const Vec4 &center, const Vec4 &up)
