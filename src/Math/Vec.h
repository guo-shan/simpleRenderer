#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <iostream>
#include "Defs.h"

template <typename T>
class Vec2 {
public:
	T x, y;

	Vec2() : x(0), y(0) {}
	Vec2(const T& _x, const T& _y) : x(_x), y(_y) {}
	Vec2(const Vec2<T>& v) : x(v.x), y(v.y) {}

	T getU() const { return x; }
	T getV() const { return y; }

	T operator[](const int i) const {
		return i == 0 ? x : y;
	}
	T& operator[](const int i) {
		return i == 0 ? x : y;
	}

	Vec2<T>& operator=(const Vec2<T>& v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	bool operator==(const Vec2<T>& v) const {
		return x == v.x && y == v.y;
	}

	Vec2<T> operator-() const { return Vec2<T>(-x, -y); }

	Vec2<T>& operator+=(const Vec2<T>& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	Vec2<T>& operator-=(const Vec2<T>& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vec2<T>& operator*=(const T t) {
		x *= t;
		y *= t;
		return *this;
	}

	Vec2<T>& operator/=(const T t) {
		return *this *= 1 / t;
	}

	T length() const { return std::sqrt(length_squared()); }
	T length_squared() const {
		return x * x + y * y;
	}

	bool near_zero() const {
		const auto s = 1e-8;
		return (fabs(x) < s) && (fabs(y) < s);
	}
};

typedef Vec2<double> 	    Vec2d;
typedef Vec2<float> 		Vec2f;
typedef Vec2<int> 			Vec2i;
typedef Vec2<unsigned int>  Vec2u;

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Vec2<T>& v) {
	return out << v.x << ' ' << v.y;
}

template <typename T>
inline Vec2<T> operator+(const Vec2<T>& u, const Vec2<T>& v) {
	return Vec2<T>(u.x + v.x, u.y + v.y);
}

template <typename T>
inline Vec2<T> operator-(const Vec2<T>& u, const Vec2<T>& v) {
	return Vec2<T>(u.x - v.x, u.y - v.y);
}

template <typename T>
inline Vec2<T> operator*(const Vec2<T>& u, const Vec2<T>& v) {
	return Vec2<T>(u.x * v.x, u.y * v.y);
}

template <typename T>
inline Vec2<T> operator*(const T t, const Vec2<T>& v) {
	return Vec2<T>(t * v.x, t * v.y);
}

template <typename T>
inline Vec2<T> operator*(const Vec2<T>& v, const T t) {
	return t * v;
}

template <typename T>
inline Vec2<T> operator/(const Vec2<T>& v, const T t) {
	return (1 / t) * v;
}

template <typename T>
inline Vec2<T> normalize(const Vec2<T>& v) {
	return v / v.length();
}


template <typename T>
class Vec3 {
public:
	T x, y, z;

	Vec3() : x(0), y(0), z(0) {}
	Vec3(const T &_x, const T &_y, const T &_z) : x(_x), y(_y), z(_z) {}
	Vec3(const Vec3<T>& v) : x(v.x), y(v.y), z(v.z) {}

	T getX() const { return x; }
	T getY() const { return y; }
	T getZ() const { return z; }

	T operator[](const int i) const {
		return i == 0 ? x : (i == 1 ? y : z);
	}
	T& operator[](const int i) {
		return i == 0 ? x : (i == 1 ? y : z);
	}

	Vec3<T>& operator=(const Vec3<T>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	bool operator==(const Vec3<T>& v) const { 
		return x == v.x && y == v.y && z == v.z; 
	}

	Vec3<T> operator-() const { return Vec3<T>(-x, -y, -z); }

	Vec3<T>& operator+=(const Vec3<T>& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vec3<T>& operator-=(const Vec3<T>& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vec3<T>& operator*=(const T t) {
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	Vec3<T>& operator/=(const T t) {
		return *this *= 1 / t;
	}

	T length() const { return std::sqrt(length_squared()); }
	T length_squared() const { 
		return x * x + y * y + z * z; 
	}

	bool near_zero() const {
		const auto s = 1e-8;
		return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
	}
};

typedef Vec3<double> 	    Vec3d;
typedef Vec3<float> 		Vec3f;
typedef Vec3<int> 			Vec3i;
typedef Vec3<unsigned int>  Vec3u;

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Vec3<T>& v) {
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

template <typename T>
inline Vec3<T> operator+(const Vec3<T>& u, const Vec3<T>& v) {
	return Vec3<T>(u.x + v.x, u.y + v.y, u.z + v.z);
}

template <typename T>
inline Vec3<T> operator-(const Vec3<T>& u, const Vec3<T>& v) {
	return Vec3<T>(u.x - v.x, u.y - v.y, u.z - v.z);
}

template <typename T>
inline Vec3<T> operator*(const Vec3<T>& u, const Vec3<T>& v) {
	return Vec3<T>(u.x * v.x, u.y * v.y, u.z * v.z);
}

template <typename T>
inline Vec3<T> operator*(const T t, const Vec3<T>& v) {
	return Vec3<T>(t * v.x, t * v.y, t * v.z);
}

template <typename T>
inline Vec3<T> operator*(const Vec3<T>& v, const T t) {
	return t * v;
}

template <typename T>
inline Vec3<T> operator/(const Vec3<T>& v, const T t) {
	return (1 / t) * v;
}

template <typename T>
inline T dot(const Vec3<T>& u, const Vec3<T> & v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

template <typename T>
inline Vec3<T> cross(const Vec3<T>& u, const Vec3<T>& v) {
	return Vec3<T>(u.y * v.z - u.z * v.y,
				   u.z * v.x - u.x * v.z,
				   u.x * v.y - u.y * v.x);
}

template <typename T>
inline Vec3<T> normalize(const Vec3<T>& v) {
	return v / v.length();
}

template <typename T, typename U>
inline Vec3<T>& lerp3(const Vec3<T>& u, const Vec3<T>& v, const U& t) {
	return Vec3<T>(lerp2(u.x, v.x, t), lerp2(u.y, v.y, t), lerp2(u.z, v.z, t));
}


template <typename T>
class Vec4 {
public:
	T x, y, z, w;

	Vec4() : x(0), y(0), z(0), w(1) {}
	Vec4(const T& _x, const T& _y, const T& _z, const T& _w = 0) : x(_x), y(_y), z(_z), w(_w) {}
	Vec4(const Vec3<T>& v, const T& _w = 0) : x(v.x), y(v.y), z(v.z), w(_w) {}
	Vec4(const Vec4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

	T getX() const { return x; }
	T getY() const { return y; }
	T getZ() const { return z; }
	T getW() const { return w; }

	T operator[](const int i) const {
		return i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w));
	}
	T& operator[](const int i) {
		return i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w));
	}

	Vec4<T>& operator=(const Vec4<T>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}

	bool operator==(const Vec4<T>& v) const {
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	Vec4<T> operator-() const { return Vec4<T>(-x, -y, -z, -w); }

	Vec4<T>& operator+=(const Vec4<T>& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	Vec4<T>& operator-=(const Vec4<T>& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	Vec4<T>& operator*=(const T t) {
		x *= t;
		y *= t;
		z *= t;
		w *= t;
		return *this;
	}

	Vec4<T>& operator/=(const T t) {
		return *this *= 1 / t;
	}

	T length() const { return std::sqrt(length_squared()); }
	T length_squared() const {
		return x * x + y * y + z * z + w * w;
	}

	bool near_zero() const {
		const auto s = 1e-8;
		return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s) && (fabs(w) < s);
	}
};

typedef Vec4<double> 	    Vec4d;
typedef Vec4<float> 		Vec4f;
typedef Vec4<int> 			Vec4i;
typedef Vec4<unsigned int>  Vec4u;

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Vec4<T>& v) {
	return out << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << ' ';
}

template <typename T>
inline Vec3<T>& vec4_to_vec3(const Vec4<T>& v) {
	return Vec3<T>(v.x, v.y, v.z);
}

template <typename T>
inline Vec4<T> vec3_to_vec4(const Vec3<T>& v, const T& w = 1.0) {
	return Vec4<T>(v.getX(), v.getY(), v.getZ(), w);
}

using Point3f = Vec3f;    // 3D point
using Color = Vec3f;    // RGB color

// æµ√Ê∑¥…‰
template <typename T>
inline Vec3<T> reflect(const Vec3<T>& ray, const Vec3<T>& normal) {
	return ray - 2 * dot(ray, normal) * normal;
}

// ’€…‰π‚
template <typename T>
inline Vec3<T> refract(const Vec3<T>& ray, const Vec3<T>& normal, const T& etai_over_etat) {
	T cos_theta_i = min(dot(-ray, normal), (T)1);
	Vec3<T> r_out_perpendicular = etai_over_etat * (ray + cos_theta_i * normal);
	Vec3<T> r_out_parallel = -sqrt(fabs(1 - r_out_perpendicular.length_squared())) * normal;
	return r_out_perpendicular + r_out_parallel;
}

// ∑∆ƒ˘∂˚œÓ
template <typename T>
void fresnel(const Vec3<T>& ray, const Vec3<T>& normal, const T& etai_over_etat, T& kr) {
	auto cos_theta_i = std::min(dot(-ray, normal), 1.0f);
	auto sin_theta_t = etai_over_etat * sqrt(std::max(0.f, 1 - cos_theta_i * cos_theta_i));
	if (sin_theta_t >= 1) {
		kr = 1.0;
	}
	else {
		T cos_theta_t = std::sqrt(std::max(0.f, 1 - sin_theta_t * sin_theta_t));
		cos_theta_i = fabs(cos_theta_i);
		float Rs = (cos_theta_i - etai_over_etat * cos_theta_t) / (cos_theta_i + etai_over_etat * cos_theta_t);
		float Rp = (cos_theta_t - etai_over_etat * cos_theta_i) / (cos_theta_t + etai_over_etat * cos_theta_i);
		kr = (Rs * Rs + Rp * Rp) / 2;
	}
}

#endif