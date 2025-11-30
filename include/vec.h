#pragma once
#define EQ 0.0008
#include <cmath>
#include <iostream>

union Vec3 {
	struct{
		float x,y,z;	
	};
	
	float elements[3];
	
	inline float operator[](int idx) const{
		return this->elements[idx];
	}

	inline float& operator[](int idx){
		return this->elements[idx];
	}
	
	inline bool operator==(const Vec3 &v) const{
		for (int i = 0; i < 3; ++i){
			float abs_val = (*this)[i] - v[i];
			abs_val = abs_val > 0 ? abs_val : -1 * abs_val;
			if (abs_val > EQ)
				return false;
		}
		return true;
	}


	inline Vec3 operator+(const Vec3 &v) const{
		Vec3 result;
		for (int i = 0; i < 3; ++i)
			result[i] = (*this)[i] + v[i];
		return result;
	}


	inline Vec3& operator+=(const Vec3 &v){
		for (int i = 0; i < 3; ++i)
			(*this)[i] += v[i];
		return *this;
	}

	inline Vec3 operator-(const Vec3 &v) const{
		Vec3 result;
		for (int i = 0; i < 3; ++i)
			result[i] = (*this)[i] - v[i];
		return result;
	}

	inline Vec3& operator-=(const Vec3 &v){
		for (int i = 0; i < 3; ++i)
			(*this)[i] -= v[i];
		return *this;
	}

	inline Vec3 operator-() const{
		Vec3 result;
		for (int i = 0; i < 3; ++i)
			result[i] = -1*(*this)[i];
		return result;
	}

	inline Vec3 operator*(float scalar) const{
		Vec3 result;
		for (int i = 0; i < 3; ++i)
			result[i] = (*this)[i] * scalar;
		return result;
	}

	inline Vec3& operator*=(float scalar){
		for (int i = 0; i < 3; ++i)
			(*this)[i] *= scalar;
		return *this;
	}

	inline Vec3 operator/(float scalar) const{
		Vec3 result;
		for (int i = 0; i < 3; ++i)
			result[i] = (*this)[i] / scalar;
		return result;
	}

	inline Vec3& operator/=(float scalar){
		for (int i = 0; i < 3; ++i)
			(*this)[i] /= scalar;
		return *this;
	}
};


inline Vec3 cross(const Vec3 &v1, const Vec3 &v2){
	Vec3 result;
	for (int i = 0; i < 3; i++)
		result[i] = v1[(i + 1) % 3] * v2[(i + 2) % 3] - v1[(i + 2) % 3] * v2[(i + 1) % 3];
	return result;
}


inline float dot(const Vec3 &v1, const Vec3 &v2) {
	float result=0;
	for (int i = 0; i < 3; ++i)
		result += v1[i] * v2[i];
	return result;
}

inline Vec3 hadamard(const Vec3 &v1, const Vec3 &v2){
	Vec3 result;
	for (int i = 0; i < 3; ++i)
		result[i] = v1[i] * v2[i];
	return result;
}

inline void debug(const Vec3 &v) {
	for (int i = 0; i < 3; ++i)
		std::cout << i << ' ' << v[i] << ' ';
	std::cout << std::endl;
}

inline float abs(const Vec3 &v){
	float result = 0;
	for (int i = 0; i < 3; ++i)
		result += v[i] * v[i];
	return sqrt(result);
}

inline Vec3 norm(const Vec3 &v){
	float v_abs =abs(v);
	Vec3 result;
	for(int i=0;i<3;++i)
		result[i] = v[i]/v_abs;
	return result;
}

union Vec4{
	struct{
		Vec3 v;
		float w;
	};
	float elements[4];

	inline float operator[](int idx) const{
		return this->elements[idx];
	}

	inline float& operator[](int idx){
		return this->elements[idx];
	}
	

	inline bool operator==(const Vec4 &vec) const{
		return this->v==vec.v && this->w == vec.w;
	}

	inline Vec4 operator+(const Vec4 &vec) const{
		Vec4 result = {this->v+vec.v, this->w+vec.w};
		return result;
	}

	inline Vec4& operator+=(const Vec4 &vec){
		this->v+=vec.v;
		this->w+=vec.w;
		return *this;
	}

	inline Vec4 operator-(const Vec4 &vec) const{
		Vec4 result = {this->v-vec.v, this->w-vec.w};
		return result;
	}

	inline Vec4& operator-=(const Vec4 &vec){
		this->v-=vec.v;
		this->w-=vec.w;
		return *this;
	}

	inline Vec4 operator-() const{
		Vec4 result = {-this->v,-this->w};
		return result;
	}

	inline Vec4 operator*(float scalar) const{
		Vec4 result={this->v*scalar, this->w};
		return result;
	}

	inline Vec4& operator*=(float scalar){
		this->v*=scalar;
		return *this;
	}

	inline Vec4 operator/(float scalar) const{
		Vec4 result = {this->v/scalar,this->w};
		return result;
	}

	inline Vec4& operator/=(float scalar){
		this->v/=scalar;
		return *this;
	}

};

inline Vec4 cross(const Vec4 &v1, const Vec4 &v2){
	Vec4 result = {cross(v1.v,v2.v),v1.w*v2.w};
	return result;
}

inline float dot(const Vec4 &v1, const Vec4 &v2) {
	return dot(v1.v,v2.v);
}

inline Vec4 hadamard(const Vec4 &v1, const Vec4 &v2){
	Vec4 result = {hadamard(v1.v,v2.v),v1.w*v2.w};
	return result;
}

inline void debug(const Vec4 &v) {
	for (int i = 0; i < 4; ++i)
		std::cout << i << ' ' << v[i] << ' ';
	std::cout << std::endl;
}

inline float abs(const Vec4 &v){
	return abs(v.v);
}

inline Vec4 norm(const Vec4 &v){
	float v_abs =abs(v);
	Vec4 result = {norm(v.v),v.w};
	return result;
}


union Mat4;
inline Mat4 identity();

union Mat4{
	struct{
		Vec4 vectors[4]; //columns
	};
	float elements[16];

	inline Vec4 operator[](int idx) const {
		return this->vectors[idx];
	}

	inline Vec4& operator[](int idx){
		return this->vectors[idx];
	}

	bool operator== (Mat4 &m)const {
		for(int i=0;i<4;++i){
			for(int j=0;j<4;++j)
				if(not ((*this)[i][j]==m[i][j])) return false;	
		}
		return true;
	}

	inline Mat4 operator+ (const Mat4 &m)const{
		Mat4 result = identity();
		for(int i=0;i<4;++i)
			for(int j=0;j<4;++j)
				result[i][j] = (*this)[i][j] + m[i][j];
		return result; 
	}
	
	inline Mat4 operator- (const Mat4 &m)const{
		Mat4 result = identity();
		for(int i=0;i<4;++i)
			for(int j=0;j<4;++j)
				result[i][j] = (*this)[i][j] - m[i][j];
		return result;
	}
	
	inline Mat4 operator* (const Mat4 &m)const{
		Mat4 result = identity();
		for(int i=0;i<4;++i)
			for(int j=0;j<4;++j){
				result[i][j] = 0;
				for(int k=0;k<4;++k)
					result[i][j] += (*this)[i][k] - m[k][i];
			}
		return result;
	}
	
	inline Mat4 operator- ()const{
		//LU decomposition
		Mat4 L = identity(), U=identity();
		for(int i=0;i<4;++i){
			for (int j = i; j < 4; ++j){
				float subtract = 0.0;
				for (int k = 0; k < i; ++k)
					subtract+= L[i][k] * U[k][j]; 
				U[i][j] = (*this)[i][j] - subtract;
			}
			for (int j = i+1; j < 4; ++j){
				float subtract = 0.0;
				for (int k = 0; k < i; ++k)
					subtract+=L[j][k] * U[k][i];
				L[j][i] = ((*this)[j][i] - subtract)/U[i][i];
			}
		}		

		//Y = L^-1, X = A^-1
		
		Mat4 X = identity(), Y = identity();
		 
		for(int i=0;i<4;++i){
			for(int j=0;j<i;++j){
				float subtract = 0.0;
				for(int k=j;k<i;++k)
					subtract+=Y[k][j]*L[i][k];
				
				Y[i][j] = -subtract;
			}
		}
	
		for(int i=3;i>=0;--i){
			for(int j=0;j<4;++j){
				float subtract = 0.0;
				for(int k=i+1;k<4;++k)
					subtract += U[i][k]*X[k][j];
				X[i][j] = (Y[i][j] - subtract)/U[i][i];
			}
		}
		return X;
	}

	inline Mat4& operator+= (const Mat4 &m){
		for(int i=0;i<4;++i)
			for(int j=0;j<4;++j)
				(*this)[i][j] += m[i][j];
		return (*this);
	}
	inline Mat4& operator-= (const Mat4 &m){
		for(int i=0;i<4;++i)
			for(int j=0;j<4;++j)
				(*this)[i][j] -= m[i][j];
		return (*this);
	}	
};


inline Mat4 identity(){
	Mat4 m =  {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	return m;
}

inline Mat4 transpose(Mat4 &m);
inline float abs(Mat4 &m);
