#ifndef ISOTROPIC_HPP
#define ISOTROPIC_HPP

#include "Core/PDF.h"
#include "Math/Defs.h"
#include "Math/Vec.h"
#include "Core/Material.h"
#include "Texture/Solid_Color.hpp"

class Isotropic : public Material {
public:
	Isotropic(Color c) : albedo(std::make_shared<Solid_Color>(c)) {}
	Isotropic(std::shared_ptr<Texture> a) : albedo(a) {}

	virtual bool scatter(const Ray& r_in, const Object& rec, Color& attenuation, Ray& scattered) const override {
		scattered = Ray(rec.vertex.getPosition(), random_point_in_unit_sphere(), r_in.getTime());
		attenuation = albedo->value(rec.vertex.getU(), rec.vertex.getV(), rec.vertex.getPosition());
		return true;
	}

public:
	std::shared_ptr<Texture> albedo;
};

#endif // !ISOTROPIC_HPP