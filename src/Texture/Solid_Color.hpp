#ifndef SOLID_COLOR_HPP
#define SOLID_COLOR_HPP

#include "Math/Vec.h"
#include "Core/Texture.h"

class Solid_Color : public Texture {
public:
	Solid_Color() {}
	Solid_Color(Color c) : color_value(c) {}
	Solid_Color(float red, float green, float blue) : Solid_Color(Color(red, green, blue)) {}

	virtual Color value(float u, float v, const Vec3f& p) const override {
		return color_value;
	}

private:
	Color color_value;
};

#endif // !SOLID_COLOR_HPP