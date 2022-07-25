#ifndef DIFFUSE_HPP
#define DIFFUSE_HPP

#include "../Core/PDF.h"
#include "../Math/Defs.h"
#include "../Math/Vec.h"
#include "../Core/Material.h"
#include "../Core/Texture.h"

class Diffuse : public Material {
public:
	Diffuse(std::shared_ptr<Texture> a) : emit(a) {}
	Diffuse(Color c) : emit(std::make_shared<Solid_Color>(c)) {}

	virtual bool scatter(const Ray& r_in, const Object& rec, Color& attenuation, Ray& scattered) const override {
		return false;
	}

	virtual Color emitted(float u, float v, const Vec3f& p) const override {
		return emit->value(u, v, p);
	}

	virtual Color emitted(const Ray& r_in, const Object& obj, float u, float v, const Point3f& p) const override {
		if (!obj.front_face)
			return Color(0, 0, 0);
		return emit->value(u, v, p);
	}
public:
	std::shared_ptr<Texture> emit;
};

#endif // !DIFFUSE_HPP