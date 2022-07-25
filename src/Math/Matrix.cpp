#include "Matrix.h"

template <typename T>
inline Mat2<T> mat2_identity() {
	return Mat2<T>(1, 0, 0, 1);
}

template <typename T>
inline Vec2<T> operator*(const Mat2<T>& mat, const Vec2<T>& v) {
	return Vec2<T>(mat.m[0][0] * v.x + mat.m[0][1] * v.y,
				   mat.m[1][0] * v.x + mat.m[1][1] * v.y);
}

template <typename T>
inline Mat2<T> operator*(const Mat2<T>& mat1, const Mat2<T>& mat2) {
	Mat2<T> Mat;
	for (unsigned int i = 0; i < 2; ++i) {
		for (unsigned int j = 0; j < 2; ++j) {
			Mat.m[i][j] = mat1.m[i][0] * mat2.m[0][j] + mat1.m[i][1] * mat2.m[1][j];
		}
	}
	return Mat;
}

template <typename T>
inline Mat2<T> rotate2(const T& angle) {
	T c = std::cos(degrees_to_radians(angle));
	T s = std::sin(degrees_to_radians(angle));
	return Mat2<T>(c, -s, s, c);
}

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Mat2<T>& mat) {
	for (unsigned int i = 0; i < 2; ++i) {
		for (unsigned int j = 0; j < 2; ++j) {
			out << mat.m[i][j] << ' ';
		}
		out << std::endl;
	}
	return out;
}



template <typename T>
inline Mat3<T> mat3_identity() {
	return Mat3<T>(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

template <typename T>
inline Vec3<T> operator*(const Mat3<T>& mat, const Vec3<T>& v) {
	return Vec3<T>(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z,
				   mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z, 
				   mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z);
}

template <typename T>
inline Mat3<T> operator*(const Mat3<T>& mat1, const Mat3<T>& mat2) {
	Mat3<T> Mat;
	for (unsigned int i = 0; i < 3; ++i) {
		for (unsigned int j = 0; j < 3; ++j) {
			Mat.m[i][j] = mat1.m[i][0] * mat2.m[0][j] +
				mat1.m[i][1] * mat2.m[1][j] +
				mat1.m[i][2] * mat2.m[2][j];
		}
	}
	return Mat;
}

template <typename T>
inline Mat3<T> scale3(const T& sx, const T& sy) {
	assert(sx != 0 && sy != 0);
	return Mat3<T>(x, 0, 0, 0, y, 0, 0, 0, 1);
}

template <typename T>
inline Mat3<T> translate3(const Vec2<T>& v) {
	return Mat3<T>(1, 0, v.x, 0, 1, v.y, 0, 0, 1);
}

template <typename T>
inline Mat3<T> rotate3(const T& angle) {
	T c = std::cos(degrees_to_radians(angle));
	T s = std::sin(degrees_to_radians(angle));
	return Mat3<T>(c, -s, 0, s, c, 0, 0, 0, 1);
}

template <typename T>
inline Mat3<T> transpose3(const Mat3<T>& mat) {
	Mat3<T> transpose;
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			transpose.m[i][j] = mat.m[j][i];
		}
	}
	return transpose;
}

template <typename T>
inline T determinant3(const Mat3<T>& mat) {
	return mat.m[0][0] * (mat.m[1][1] * mat.m[2][2] - mat.m[2][1] * mat.m[1][2])
		 - mat.m[0][1] * (mat.m[1][0] * mat.m[2][2] - mat.m[2][0] * mat.m[1][2])
		 + mat.m[0][2] * (mat.m[1][0] * mat.m[2][1] - mat.m[2][0] * mat.m[1][1]);
}

template <typename T>
inline T cofactor3(Mat3<T>& mat, int row, int col) {
	Mat2<T> cut_down;
	for (unsigned int i = 0; i < 2; i++) {
		for (unsigned int j = 0; j < 2; j++) {
			unsigned int r = i < row ? i : i + 1;
			unsigned int c = j < col ? j : j + 1;
			cut_down.m[i][j] = mat.m[r][c];
		}
	}
	T minor = cut_down.m[0][0] * cut_down.m[1][1] - cut_down.m[1][0] * cut_down.m[0][1];
	return (row + col) % 2 == 0 ? minor : -minor;
}

template <typename T>
inline Mat3<T> adjoint3(const Mat3<T>& mat) {
	Mat3<T> adjoint;
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			adjoint.m[i][j] = cofactor3(mat, i, j);
		}
	}
	adjoint = transpose3(adjoint);
	return adjoint;
}

template <typename T>
inline Mat3<T> inverse3(const Mat3<T>& mat) {
	Mat3<T> adjoint = adjoint3(mat);
	Mat3<T> inverse;
	T determinant = 0;

	for (unsigned int i = 0; i < 3; i++) {
		determinant += mat.m[0][i] * adjoint.m[0][i];
	}
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			inverse.m[i][j] = adjoint.m[i][j] / determinant;
		}
	}
	return inverse;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Mat3<T>& mat) {
	for (unsigned int i = 0; i < 3; ++i) {
		for (unsigned int j = 0; j < 3; ++j) {
			out << mat.m[i][j] << ' ';
		}
		out << std::endl;
	}
	return out;
}



template <typename T>
inline Mat4<T> mat4_identity() {
	return Mat4<T>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

template <typename T>
inline Vec4<T> operator*(const Mat4<T>& mat, const Vec4<T>& v) {
	return Vec4<T>(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z + mat.m[0][3] * v.w,
				   mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z + mat.m[1][3] * v.w,
				   mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z + mat.m[2][3] * v.w,
				   mat.m[3][0] * v.x + mat.m[3][1] * v.y + mat.m[3][2] * v.z + mat.m[3][3] * v.w);
}

template <typename T>
inline Mat4<T> operator*(const Mat4<T>& mat1, const Mat4<T>& mat2) {
	Mat4<T> Mat;
	for (unsigned int i = 0; i < 4; ++i) {
		for (unsigned int j = 0; j < 4; ++j) {
			Mat.m[i][j] = mat1.m[i][0] * mat2.m[0][j] +
						  mat1.m[i][1] * mat2.m[1][j] +
						  mat1.m[i][2] * mat2.m[2][j] +
						  mat1.m[i][3] * mat2.m[3][j];
		}
	}
	return Mat;
}

template <typename T>
inline Mat4<T> scale4(const T& sx, const T& sy, const T& sz) {
	assert(sx != 0 && sy != 0 && sz != 0);
	return Mat4<T>(sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
}

template <typename T>
inline Mat4<T> translate4(const Vec3<T>& v) {
	return Mat4<T>(1, 0, 0, v.x, 0, 1, 0, v.y, 0, 0, 1, v.z, 0, 0, 0, 1);
}

template <typename T>
inline Mat4<T> rotate4X(const T& angle) {
	T c = std::cos(degrees_to_radians(angle));
	T s = std::sin(degrees_to_radians(angle));
	return Mat4<T>(1, 0, 0, 0, 0, c, -s, 0, 0, s, c, 0, 0, 0, 0, 1);
}

template <typename T>
inline Mat4<T> rotate4Y(const T& angle) {
	T c = std::cos(degrees_to_radians(angle));
	T s = std::sin(degrees_to_radians(angle));
	return Mat4<T>(c, 0, s, 0, 0, 1, 0, 0, -s, 0, c, 0, 0, 0, 0, 1);
}

template <typename T>
inline Mat4<T> rotate4Z(const T& angle) {
	T c = std::cos(degrees_to_radians(angle));
	T s = std::sin(degrees_to_radians(angle));
	return Mat4<T>(c, -s, 0, 0, s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

template <typename T>
inline Mat4<T> transpose4(const Mat4<T>& mat) {
	Mat4<T> transpose;
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			transpose.m[i][j] = mat.m[j][i];
		}
	}
	return transpose;
}

template <typename T>
inline T cofactor4(const Mat4<T>& mat, int row, int col) { 
	Mat3<T> cut_down;
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			unsigned int r = i < row ? i : i + 1;
			unsigned int c = j < col ? j : j + 1;
			cut_down.m[i][j] = mat.m[r][c];
		}
	}
	return (row + col) % 2 == 0 ? determinant3(cut_down) : -determinant3(cut_down);
}

template <typename T>
inline Mat4<T> adjoint4(const Mat4<T>& mat) {
	Mat4<T> adjoint;
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			adjoint.m[i][j] = cofactor4(mat, i, j);
		}
	}
	adjoint = transpose4(adjoint);
	return adjoint;
}

template <typename T>
inline Mat4<T> inverse4(const Mat4<T>& mat) {
	Mat4<T> adjoint = adjoint4(mat);
	Mat4<T> inverse;
	T determinant = 0, inv_determinant;

	for (unsigned int i = 0; i < 4; i++) {
		determinant += mat.m[0][i] * adjoint.m[0][i];
	}
	inv_determinant = 1 / determinant;
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			inverse.m[i][j] = adjoint.m[i][j] * inv_determinant;
		}
	}
	return inverse;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Mat4<T>& mat) {
	for (unsigned int i = 0; i < 4; ++i) {
		for (unsigned int j = 0; j < 4; ++j) {
			out << mat.m[i][j] << ' ';
		}
		out << std::endl;
	}
	return out;
}

// 2/(r-l)          0           0	 -(r+l)/(r-l)
//       0    2/(t-b)           0	 -(t+b)/(t-b)
//		 0          0    -2/(f-n)    -(f+n)/(f-n)
//		 0          0          0                1
template <typename T>
inline Mat4<T> ortho(const T& left, const T& right, const T& bottom, const T& top) {
	return Mat4<T>(-2 / (left - right), 0, 0, (left + right) / (left - right),
				   0, -2 / (bottom - top), 0, (bottom + top) / (bottom - top),
				   0, 0, 2 / (near - far), (near + far) / (near - far),
				   0, 0, 0, 1);
}

// 2n/(r-l)           0     (r+l)/(r-l)            0
//		  0    2n/(t-b)     (t+b)/(t-b)            0
//	      0           0    -(f+n)/(f-n)    -2fn/(f-n)
//		  0           0              -1            0

template <typename T>
inline Mat4<T> frustum(const T& left, const T& right, const T& bottom, const T& top, const T& near, const T& far) {
	return Mat4<T>(-2 * near / (left - right), 0, -(left + right) / (left - right), 0,
				   0, -2 * near / (bottom - top), -(bottom + top) / (bottom - top), 0,
				   0, 0, (near + far) / (near - far), 2 * near * far / (near - far), 
				   0, 0, -1, 0);
}

// r = -l, t = -b
//    1/r      0     (r+l)/(r-l)            0
//      0    1/t     (t+b)/(t-b)            0
//	    0      0    -(f+n)/(f-n)    -2fn/(f-n)
//		0      0              -1            0

template <typename T>
inline Mat4<T> orthographic(const T& right, const T& top, const T& near, const T& far) {
	return Mat4<T>(1 / right, 0, 0, 0,
				   0, 1 / top, 0, 0,
				   0, 0, 2 / (near - far), (near + far) / (near - far),
				   0, 0, 0, 1);
}
// 1/(aspect*tan(fovy/2))                0               0             0
//					    0    1/tan(fovy/2)               0             0
//						0                0    -(f+n)/(f-n)    -2fn/(f-n)
//						0                0				-1             0
template <typename T>
inline Mat4<T> perspective(const T& fovy, const T& aspect, const T& near, const T& far) {
	return Mat4<T>(1 / (aspect * std::tan(fovy / 2)), 0, 0, 0, 
				   0, 1 / std::tan(fovy / 2), 0, 0,
				   0, 0, (near + far) / (near - far), 2 * near * far / (near - far),
				   0, 0, -1, 0);
}

template <typename T>
inline Mat4<T> view(const Vec3<T>& eye_pos, const Vec3<T>& target, const Vec3<T>& up) {
	Vec3<T> z_axis = normalize(target - eye_pos);
	Vec3<T> x_axis = normalize(cross(z_axis, up));
	Vec3<T> y_axis = cross(x_axis, z_axis);


	return Mat4<T>(x_axis.x, x_axis.y, x_axis.z, -dot(x_axis, eye_pos), 
				   y_axis.x, y_axis.y, y_axis.z, -dot(y_axis, eye_pos),
				   -z_axis.x, -z_axis.y, -z_axis.z, dot(z_axis, eye_pos),
				   0, 0, 0, 1);
}

template <typename T>
inline Mat4<T> view(const Vec3<T>& eye_pos) {
	return Mat4<T>(1, 0, 0, -eye_pos[0],
				   0, 1, 0, -eye_pos[1],
				   0, 0, 1, -eye_pos[2],
				   0, 0, 0, 1);
}