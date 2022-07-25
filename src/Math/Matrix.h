#ifndef MATRIX_H
#define MATRIX_H

#include "Defs.h"
#include "Vec.h"

template <typename T>
class Mat2 {
public:
	T m[2][2];

	inline Vec2<T> 	operator()(const Vec2<T>& v) const {
		T x = m[0][0] * v.x + m[1][0] * v.y;
		T y = m[0][1] * v.x + m[1][1] * v.y;
		return Vec2<T>(x, y);
	}

	Mat2(const T& m00, const T& m01, const T& m10, const T& m11) {
		m[0][0] = m00;
		m[0][1] = m01;
		m[1][0] = m10;
		m[1][1] = m11;
	}
	Mat2<T>(const Mat2<T>& mat) {
		memcpy(this->m, mat.m, 4 * sizeof(T));
	}

	Mat2<T> operator=(const Mat2<T>& mat) {
		memcpy(this->m, mat.m, 4 * sizeof(T));
		return *this;
	}

	bool operator==(const Mat2<T>& mat) const {
		return memcmp(this->m, mat.m, 4 * sizeof(T)) == 0;
	}

	Mat2<T> operator*=(const Mat2<T>& mat) {
		Mat2<T> Mat;
		for (unsigned int i = 0; i < 2; ++i) {
			for (unsigned int j = 0; j < 2; ++j) {
				Mat.m[i][j] = this->m[i][0] * mat.m[0][j] +
							  this->m[i][1] * mat.m[1][j];
			}
		}
		return Mat;
	}
};

typedef Mat2<double> 	    Mat2d;
typedef Mat2<float> 		Mat2f;
typedef Mat2<int> 			Mat2i;
typedef Mat2<unsigned int>  Mat2u;

template <typename T>
inline Mat2<T> mat2_identity();
template <typename T>
inline Vec2<T> operator*(const Mat2<T>&, const Vec2<T>&);
template <typename T>
inline Mat2<T> operator*(const Mat2<T>&, const Mat2<T>&);
template <typename T>
inline Mat2<T> rotate2(const T&);
template <typename T>
inline std::ostream& operator<<(std::ostream&, const Mat2<T>&);


template <typename T>
class Mat3 {
public:
	T m[3][3];

	Mat3() {
		m[0][0] = 1, m[0][1] = 0, m[0][2] = 0,
		m[1][0] = 0, m[1][1] = 1, m[1][2] = 0,
		m[2][0] = 0, m[2][1] = 0, m[2][2] = 1;
	}
	Mat3(const T& m00, const T& m01, const T& m02,
		const T& m10, const T& m11, const T& m12,
		const T& m20, const T& m21, const T& m22) {
		m[0][0] = m00, m[0][1] = m01, m[0][2] = m02,
		m[1][0] = m10, m[1][1] = m11, m[1][2] = m12,
		m[2][0] = m20, m[2][1] = m21, m[2][2] = m22;
	}
	Mat3(const Vec3<T>& u, const Vec3<T>& v, const Vec3<T>& w) {
		m[0][0] = u.getX(), m[0][1] = v.getX(), m[0][2] = w.getX(),
		m[1][0] = u.getY(), m[1][1] = v.getY(), m[1][2] = w.getY(),
		m[2][0] = u.getZ(), m[2][1] = v.getZ(), m[2][2] = w.getZ();
	}
	Mat3<T>(const Mat3<T>& mat) {
		memcpy(this->m, mat.m, 9 * sizeof(T));
	}

	Mat3<T> operator=(const Mat3<T>& mat) {
		memcpy(this->m, mat.m, 9 * sizeof(T));
		return *this;
	}

	bool operator==(const Mat3<T>& mat) const {
		return memcmp(this->m, mat.m, 9 * sizeof(T)) == 0;
	}

	Mat3<T> operator*=(const Mat3<T>& mat) {
		Mat3<T> Mat;
		for (unsigned int i = 0; i < 3; ++i) {
			for (unsigned int j = 0; j < 3; ++j) {
				Mat.m[i][j] = this->m[i][0] * mat.m[0][j] +
							  this->m[i][1] * mat.m[1][j] +
						   	  this->m[i][2] * mat.m[2][j];
			}
		}
		return Mat;
	}
};

typedef Mat3<double> 	    Mat3d;
typedef Mat3<float> 		Mat3f;
typedef Mat3<int> 			Mat3i;
typedef Mat3<unsigned int>  Mat3u;

template <typename T>
inline Mat3<T> mat3_identity();
template <typename T>
inline Vec3<T> operator*(const Mat3<T>&, const Vec3<T>&);
template <typename T>
inline Mat3<T> operator*(const Mat3<T>&, const Mat3<T>&);
template <typename T>
inline Mat3<T> scale3(const T&, const T&);
template <typename T>
inline Mat3<T> translate3(const Vec2<T>&);
template <typename T>
inline Mat3<T> rotate3(const T&);
template <typename T>
inline Mat3<T> transpose3(const Mat3<T>&);
template <typename T>
inline T determinant3(const Mat3<T>&);
template <typename T>
inline Mat3<T> cofactor3(Mat3<T>&, int, int);
template <typename T>
inline Mat3<T> adjoint3(const Mat3<T>&);
template <typename T>
inline Mat3<T> inverse3(const Mat3<T>&);
template <typename T>
inline std::ostream& operator<<(std::ostream&, const Mat3<T>&);

template <typename T>
class Mat4 {
public:
	T m[4][4];

	Mat4() {
		m[0][0] = 1, m[0][1] = 0, m[0][2] = 0, m[0][3] = 0,
		m[1][0] = 0, m[1][1] = 1, m[1][2] = 0, m[1][3] = 0,
		m[2][0] = 0, m[2][1] = 0, m[2][2] = 1, m[2][3] = 0,
		m[3][0] = 0, m[3][1] = 0, m[3][2] = 0, m[3][3] = 1;
	}
	Mat4(const T& m00, const T& m01, const T& m02, const T& m03,
		 const T& m10, const T& m11, const T& m12, const T& m13,
		 const T& m20, const T& m21, const T& m22, const T& m23,
		 const T& m30, const T& m31, const T& m32, const T& m33) {
		m[0][0] = m00, m[0][1] = m01, m[0][2] = m02, m[0][3] = m03,
		m[1][0] = m10, m[1][1] = m11, m[1][2] = m12, m[1][3] = m13,
		m[2][0] = m20, m[2][1] = m21, m[2][2] = m22, m[2][3] = m23,
		m[3][0] = m30, m[3][1] = m31, m[3][2] = m32, m[3][3] = m33;
	}
	Mat4<T>(const Mat4<T>& mat) {
		memcpy(this->m, mat.m, 16 * sizeof(T));
	}

	Mat4<T> operator=(const Mat4<T>& mat) {
		memcpy(this->m, mat.m, 16 * sizeof(T));
		return *this;
	}

	bool operator==(const Mat4<T>& mat) const {
		return memcmp(this->m, mat.m, 16 * sizeof(T)) == 0;
	}

	Mat4<T> operator*=(const Mat4<T>& mat) {
		Mat4<T> Mat;
		for (unsigned int i = 0; i < 4; ++i) {
			for (unsigned int j = 0; j < 4; ++j) {
				Mat.m[i][j] = this->m[i][0] * mat.m[0][j] +
					this->m[i][1] * mat.m[1][j] +
					this->m[i][2] * mat.m[2][j] +
					this->m[i][3] * mat.m[3][j];
			}
		}
		return Mat;
	}
};

typedef Mat4<double> 	    Mat4d;
typedef Mat4<float> 		Mat4f;
typedef Mat4<int> 			Mat4i;
typedef Mat4<unsigned int>  Mat4u;

template <typename T>
inline Mat4<T> mat4_identity();
template <typename T>
inline Vec4<T> operator*(const Mat4<T>&, const Vec4<T>&);
template <typename T>
inline Mat4<T> operator*(const Mat4<T>&, const Mat4<T>&);
template <typename T>
inline Mat4<T> scale4(const T&, const T&, const T&);
template <typename T>
inline Mat4<T> translate4(const Vec3<T>&);
template <typename T>
inline Mat4<T> rotate4X(const T&);
template <typename T>
inline Mat4<T> rotate4Y(const T&);
template <typename T>
inline Mat4<T> rotate4Z(const T&);
template <typename T>
inline std::ostream& operator<<(std::ostream&, const Mat4<T>&);



#endif