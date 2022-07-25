#ifndef CHECKER_TEXTURE_HPP
#define CHECKER_TEXTURE_HPP

#include "Core/Texture.h"

class Checker_Texture : public Texture {
public:
	Checker_Texture() {}
	Checker_Texture(std::shared_ptr<Texture> _even, std::shared_ptr<Texture> _odd) : even(_even), odd(_odd) {}
	Checker_Texture(Color c1, Color c2) : even(std::make_shared<Solid_Color>(c1)), odd(std::make_shared<Solid_Color>(c2)) {}

	virtual Color value(float u, float v, const Point3f& p) const override {
		auto sines = sin(10 * p.getX()) * sin(10 * p.getY()) * sin(10 * p.getZ());
		if (sines < 0) return odd->value(u, v, p);
		else return even->value(u, v, p);
	}

public:
	std::shared_ptr<Texture> odd;
	std::shared_ptr<Texture> even;
};

#endif // !CHECKER_TEXTURE_HPP
