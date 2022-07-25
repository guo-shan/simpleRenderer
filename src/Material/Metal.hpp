#ifndef METAL_HPP
#define METAL_HPP

#include "../Core/PDF.h"
#include "../Math/Defs.h"
#include "../Math/Vec.h"
#include "../Core/Material.h"
#include "../Core/Texture.h"

class Metal : public Material {
public:
	Metal(const Color& a) : albedo(a) {}
	Metal(const Color& a, float f) : albedo(a), fuzzy(f < 1 ? f : 1) {}

	virtual bool scatter(const Ray& r_in, const Object& obj, Color& attenuation, Ray& scattered) const override {
		Vec3f reflected = reflect(normalize(r_in.getDirection()), obj.vertex.getNormal());
		scattered = Ray(obj.vertex.getPosition(), reflected + fuzzy * random_point_in_unit_sphere(), r_in.getTime());
		attenuation = albedo;
		return (dot(scattered.getDirection(), obj.vertex.getNormal()) > 0);
	}

	virtual bool scatter(const Ray& r_in, const Object& obj, Scatter_Object& sobj) const override {
		Vec3f reflected = reflect(normalize(r_in.getDirection()), obj.vertex.getNormal());
		sobj.specular_ray = Ray(obj.vertex.getPosition(), reflected + fuzzy * random_point_in_unit_sphere(), r_in.getTime());
		sobj.attenuation = albedo;
		sobj.is_specular = true;
		sobj.pdf_ptr = nullptr;
		return true;
	}

public:
	Color albedo;
	float fuzzy;
};

#endif // !METAL_HPP
