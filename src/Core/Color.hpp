#ifndef COLOR_HPP
#define COLOR_HPP

#include "Math/Vec.h"
#include "Math/Defs.h"

// color实用函数
Color write_color(std::ostream& out, Color pixel_color, int samples_per_pixel) {

	float r = pixel_color.getX();
	float g = pixel_color.getY();
	float b = pixel_color.getZ();

	if (r != r) r = 0.0f;
	if (g != g) g = 0.0f;
	if (b != b) b = 0.0f;

	//根据样本数对颜色取平均值并进行gamma校正
	float scale = 1.0f / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	out << static_cast<int>(256 * clamp_to_num(r, 0.0f, 0.999f)) << ' '
		<< static_cast<int>(256 * clamp_to_num(g, 0.0f, 0.999f)) << ' '
		<< static_cast<int>(256 * clamp_to_num(b, 0.0f, 0.999f)) << std::endl;

	return Color(static_cast<int>(256 * clamp_to_num(r, 0.0f, 0.999f)), 
				 static_cast<int>(256 * clamp_to_num(g, 0.0f, 0.999f)), 
				 static_cast<int>(256 * clamp_to_num(b, 0.0f, 0.999f)));
}

#endif // !COLOR_HPP


