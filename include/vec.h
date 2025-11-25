#pragma once
#define EQ 0.0008
#include <cmath>
#include <iostream>

union Vec3 {
	struct{
		float x,y,z;	
	};
	
	float elements[3];
	
	inline bool operator==(const Vec3 &v) const{
		for (int i = 0; i < 3; ++i){
			float abs_val = this->elements[i] - v.elements[i];
			abs_val = abs_val > 0 ? abs_val : -1 * abs_val;
			if (abs_val > EQ)
				return false;
		}
		return true;
	}


	inline Vec3 operator+(const Vec3 &v) const{
		Vec3 result;
		for (int i = 0; i < 3; ++i)
			result.elements[i] = this->elements[i] + v.elements[i];
		return result;
	}


	inline Vec3& operator+=(const Vec3 &v){
		for (int i = 0; i < 3; ++i)
			this->elements[i] += v.elements[i];
		return *this;
	}

	inline Vec3 operator-(const Vec3 &v) const{
		Vec3 result;
		for (int i = 0; i < 3; ++i)
			result.elements[i] = this->elements[i] - v.elements[i];
		return result;
	}

	inline Vec3& operator-=(const Vec3 &v){
		for (int i = 0; i < 3; ++i)
			this->elements[i] -= v.elements[i];
		return *this;
	}

	inline Vec3 operator-() const{
		Vec3 result;
		for (int i = 0; i < 3; ++i)
			result.elements[i] = -1*this->elements[i];
		return result;
	}

	inline Vec3 operator*(float scalar) const{
		Vec3 result;
		for (int i = 0; i < 3; ++i)
			result.elements[i] = this->elements[i] * scalar;
		return result;
	}

	inline Vec3& operator*=(float scalar){
		for (int i = 0; i < 3; ++i)
			this->elements[i] *= scalar;
		return *this;
	}

	inline Vec3 operator/(float scalar) const{
		Vec3 result;
		for (int i = 0; i < 3; ++i)
			result.elements[i] = this->elements[i] / scalar;
		return result;
	}

	inline Vec3& operator/=(float scalar){
		for (int i = 0; i < 3; ++i)
			this->elements[i] /= scalar;
		return *this;
	}
};


inline Vec3 cross(const Vec3 &v1, const Vec3 &v2){
	Vec3 result;
	for (int i = 0; i < 3; i++)
		result.elements[i] = v1.elements[(i + 1) % 3] * v2.elements[(i + 2) % 3] - v1.elements[(i + 2) % 3] * v2.elements[(i + 1) % 3];
	return result;
}


inline float dot(const Vec3 &v1, const Vec3 &v2) {
	float result=0;
	for (int i = 0; i < 3; ++i)
		result += v1.elements[i] * v2.elements[i];
	return result;
}

inline Vec3 hadamard(const Vec3 &v1, const Vec3 &v2){
	Vec3 result;
	for (int i = 0; i < 3; ++i)
		result.elements[i] = v1.elements[i] * v2.elements[i];
	return result;
}

inline void debug(const Vec3 &v) {
	for (int i = 0; i < 3; ++i)
		std::cout << i << ' ' << v.elements[i] << ' ';
	std::cout << std::endl;
}

inline float abs(const Vec3 &v){
	float result = 0;
	for (int i = 0; i < 3; ++i)
		result += v.elements[i] * v.elements[i];
	return sqrt(result);
}

inline Vec3 norm(const Vec3 &v);
inline Vec3 point(float x, float y, float z);
inline Vec3 vector(float x, float y, float z);
inline Vec3 reflect(const Vec3 &incident, const Vec3 &normal);


union Vec4{
	struct{
		float x,y,z,w;
	};

	float elements[4];
};

struct Mat4{
	Vec4 elements[4];

	bool operator== (Mat4 &m);
	inline Mat4 operator+ (const Mat4 &m)const;
	inline Mat4 operator- (const Mat4 &m)const;
	inline Mat4 operator* (const Mat4 &m)const;
	inline Mat4 operator- ()const;
	inline Mat4& operator+= (const Mat4 &m);
	inline Mat4& operator-= (const Mat4 &m);
	inline Mat4& operator*= (const Mat4 &m);	
};


inline Mat4 identity();
inline Mat4 transpose(Mat4 &m);
inline float abs(Mat4 &m);
