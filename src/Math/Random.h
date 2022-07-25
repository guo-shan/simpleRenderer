#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib> // 随机数rand()
#include "Defs.h"
#include "Vec.h"

// 生成随机数
inline float random_float() {
	// 返回[0,1)
	return rand() / (RAND_MAX + 1.0);
}
inline float random_float(float min, float max) {
	// 返回[min,max)
	return min + (max - min) * random_float();
}
inline int random_int(int min, int max) {
	// 返回[min,max]
	return static_cast<int>(random_float(min, max + 1));
}

// 生成随机向量
inline Vec3f random_vec3() {
	return Vec3f(random_float(), random_float(), random_float());
}
inline Vec3f random_vec3(float min, float max) {
	return Vec3f(random_float(min, max), random_float(min, max), random_float(min, max));
}
// 生成单位随机向量
inline Vec3f random_unit_vector() {
	auto a = random_float(0.0, 2 * PI);
	auto z = random_float(-1.0, 1.0);
	auto r = std::sqrt(1 - z * z);
	return Vec3f(r * std::cos(a), r * std::sin(a), z);
}

// 单位球内生成随机点
inline Vec3f random_point_in_unit_sphere() {
	while (true) {
		Vec3f p = random_vec3(-1, 1);
		if (p.length_squared() < 1) return p;
	}
}
// 球内生成随机点
inline Vec3f random_cosine_sphere_direction(float roughness) {
	auto r = random_float();
	auto phi = 2 * PI * r;

	auto x = std::sin(degrees_to_radians(roughness)) * std::cos(phi);
	auto y = std::sin(degrees_to_radians(roughness)) * std::sin(phi);
	auto z = std::cos(degrees_to_radians(roughness));

	return Vec3f(x, y, z);
}
inline Vec3f random_to_sphere_direction(float radius, float distance_squared) {
	auto r1 = random_float();
	auto r2 = random_float();
	auto z = 1 + r2 * (sqrt(1 - radius * radius / distance_squared) - 1);

	auto phi = 2 * PI * r1;
	auto x = cos(phi) * sqrt(1 - z * z);
	auto y = sin(phi) * sqrt(1 - z * z);

	return Vec3f(x, y, z);
}

// 半球内生成随机点
inline Vec3f random_point_in_hemisphere(const Vec3f& normal) {
	Vec3f in_unit_sphere = random_point_in_unit_sphere();
	// 与法线在同一个半球
	if (dot(in_unit_sphere, normal) > 0.0) return in_unit_sphere;
	else return -in_unit_sphere;
}
// 半球内生成随机点
inline Vec3f random_cosine_hemisphere_direction() {
	auto r1 = random_float();
	auto r2 = random_float();
	auto z = std::sqrt(1 - r2);

	auto phi = 2 * PI * r1;
	auto x = std::cos(phi) * std::sqrt(r2);
	auto y = std::sin(phi) * std::sqrt(r2);

	return Vec3f(x, y, z);
}

// 圆盘中心(lookfrom)生成随机场景光线
inline Vec3f random_in_unit_disk() {
	while (true) {
		auto p = Vec3f(random_float(-1, 1), random_float(-1, 1), 0);
		if (p.length_squared() < 1) return p;
	}
}
#endif


