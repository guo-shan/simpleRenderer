#ifndef MATERIAL_H
#define MATERIAL_H

#include "Math/Vec.h"
#include "Core/Hittable.h"
#include "PDF.h"

struct Scatter_Object {
	Ray specular_ray;
	bool is_specular;
	Color attenuation;
	std::shared_ptr<PDF> pdf_ptr;
};


class Material {
public:
	virtual Color emitted(float u, float v, const Point3f& p) const {
		return Color(0, 0, 0);
	}

	virtual Color emitted(const Ray& r_in, const Object& rec, float u, float v, const Point3f& p) const {
		return Color(0, 0, 0);
	}

	virtual bool scatter(const Ray& r_in, const Object& rec, Color& attenuation, Ray& scattered) const = 0;

	virtual bool scatter(const Ray& r_in, const Object& rec, Scatter_Object& srec) const {
		return false;
	}

	virtual float scattering_pdf(const Ray& r_in, const Object& rec, const Ray& scattered) const {
		return 0;
	}
};

#endif // !Material_H