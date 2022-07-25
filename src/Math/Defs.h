#ifndef DEFS_H
#define DEFS_H

#include <cmath>
#include <limits>
#include <memory>

#include "Math/Vec.h"

const float kEpsilon = 1e-4;
const float Infinity = std::numeric_limits<float>::infinity(); // 无穷大
const float PI = 3.1415926535897932385;

const int image_width = 320;
const int image_height = 180;
const auto aspect_ratio = 16.0f / 9.0f;

// 度数转弧度
template <typename T>
inline T degrees_to_radians(T angle) {
	return angle * PI / 180.0;
}
// 比较大小
template <typename T>
inline T min(const T& x, const T& y) {
	return x < y ? x : y;
}
template <typename T>
inline T max(const T& x, const T& y) {
	return x > y ? x : y;
}
// 二次插值
template <typename T, typename U>
inline T lerp2(const T& x, const T& y, const U& t) {
	return x + (y - x) * t;
}
// 将值 x 限制在 [min,max] 范围
template <typename T>
inline T clamp_to_num(const T& x, const T& min, const T& max) {
	return x < min ? min : (x > max ? max : x);
}
// 将值 x 限制在 [0,1] 范围
template <typename T>
inline T clamp_to_one(const T& x) {
	return x < 0 ? 0 : (x > 1 ? 1 : x);
}

//float float_from_uchar(unsigned char value) {
//	return value / 255.0f;
//}
//
//unsigned char float_to_uchar(float value) {
//	return (unsigned char)(value * 255);
//}
//
//float srgb_to_linear(float value) {
//	return pow(value, 2.2);
//}
//
//float linear_to_srgb(float value) {
//	return pow(value, 1 / 2.2);
//}

inline void UpdateProgress(float progress) {
	int barWidth = 70;

	std::cout << "[";
	int pos = barWidth * progress;
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	}
	std::cout << "] " << int(progress * 100.0) << " %\r";
	std::cout.flush();
}

#endif