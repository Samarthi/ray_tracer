#include "vec.h"
#include <cmath>

inline Vec4 point(float x, float y, float z){
	Vec4 result  = {x,y,z,1};
	return result;
}

inline Vec4 vector(float x, float y, float z){
	Vec4 result  = {x,y,z,0};
	return result;
}

inline Mat4 mat_translate(float tx, float ty, float tz){
	Mat4 result = identity();
	result[0][3] = tx;
	result[1][3] = ty;
	result[2][3] = tz;
	return result;
}

inline Mat4 mat_scale(float sx, float sy, float sz){
	Mat4 result = identity();
	result[0][0]=sx;
	result[1][1]=sy;
	result[2][2]=sz;
	return result;
}

inline Mat4 mat_rot_x(float theta){
	Mat4 result = identity();
	float cosine = cos(theta), sine = sin(theta);
	result[1][1] = cosine;
	result[2][1] = -sine;
	result[1][2] = sine;
	result[2][2] = cosine;
	return result;
}

inline Mat4 mat_rot_y(float theta){
	Mat4 result = identity();
	float cosine = cos(theta), sine = sin(theta);
	result[0][0] = cosine;
	result[2][0] = -sine;
	result[0][2] = sine;
	result[2][2] = cosine;
	return result;
}

inline Mat4 mat_rot_z(float theta){
	Mat4 result = identity();
	float cosine = cos(theta), sine = sin(theta);
	result[0][0] = cosine;
	result[1][0] = -sine;
	result[0][1] = sine;
	result[1][1] = cosine;
	return result;
}

inline Mat4 mat_ortho_projection(float L, float R, float T, float B, float N, float F){
	Mat4 result = identity();
	// camera points down negative z
	//            scale factors            translational factors
	result[0][0] = 2/(R-L), result[0][3] = -(R+L)/(R-L);
	result[1][1] = 2/(T-B), result[1][3] = -(T+B)/(T-B);
	result[2][2] = 2/(N-F), result[2][3] = -(N+F)/(N-F);

	return result;	
}

inline Mat4 mat_persp_projection(float L, float R, float T, float B, float N, float F){
	Mat4 result = identity();
	
	result[0][0] = 2*N/(R-L), result[0][2] = (R+L)/(R-L);
	result[1][1] = 2*N/(T-B), result[1][2] = (T+B)/(T-B);
	result[2][2] = -(F+N)/(F-N), result[2][3] = -2*F*N/(F-N);
	result[3][2] = -1;

	return result;
}

inline Vec4 transform(const Vec4 &v, const Mat4 &m){
	Vec4 result;
	for(int i=0;i<4;++i){
		result[i] = 0;
		for(int j=0;j<4;++j)
			result[i] += v[j]*m[i][j]; 
	}
	return result;
}