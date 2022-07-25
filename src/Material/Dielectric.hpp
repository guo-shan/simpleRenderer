#ifndef DIELECTRIC_HPP
#define DIELECTRIC_HPP

#include "../Core/PDF.h"
#include "../Math/Defs.h"
#include "../Math/Vec.h"
#include "../Core/Material.h"
#include "../Core/Texture.h"

class Dielectric : public Material {
public:
	Dielectric(float ir) : index_of_refraction(ir) {}

	virtual bool scatter(const Ray& r_in, const Object& rec, Color& attenuation, Ray& scattered) const override {
		attenuation = Color(1.0, 1.0, 1.0);
		// 折射率, 判断交点是在外部还是内部 front_face为true时-->外部
		float refraction_ratio = rec.front_face ? (1.0 / index_of_refraction) : index_of_refraction;

		Vec3f unit_direction = normalize(r_in.getDirection());
		float cos_theta = fmin(dot(-unit_direction, rec.vertex.getNormal()), 1.0);
		float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

		// 全内反射 total internal reflection
		bool TIR = refraction_ratio * sin_theta > 1.0;
		// 反射率
		float reflection_coefficient = schlick(cos_theta, refraction_ratio);
		Vec3f r_out;
		if (TIR || reflection_coefficient > random_float()) {
			r_out = reflect(unit_direction, rec.vertex.getNormal());
		}
		else {
			r_out = refract(unit_direction, rec.vertex.getNormal(), refraction_ratio);
		}

		scattered = Ray(rec.vertex.getPosition(), r_out, r_in.getTime());
		return true;
	}

	/*virtual bool scatter(const Ray& r_in, const Object& obj, Scatter_Object& sobj) const override {
		sobj.is_specular = true;
		sobj.pdf_ptr = nullptr;
		sobj.attenuation = Color(1.0, 1.0, 1.0);
		float refraction_ratio = obj.front_face ? (1.0 / index_of_refraction) : index_of_refraction;

		Vec3f unit_direction = normalize(r_in.getDirection());
		float cos_theta = std::fmin(dot(-unit_direction, obj.vertex.getNormal()), 1.0);
		float sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

		bool cannot_refract = refraction_ratio * sin_theta > 1.0;
		Vec3f direction;

		if (cannot_refract || schlick(cos_theta, refraction_ratio) > random_float())
			direction = reflect(unit_direction, obj.vertex.getNormal());
		else
			direction = refract(unit_direction, obj.vertex.getNormal(), refraction_ratio);

		sobj.specular_ray = Ray(obj.vertex.getPosition(), direction, r_in.getTime());
		return true;
	}*/

public:
	float index_of_refraction;

private:
	// Schlick近似
	static float schlick(float cos_theta, float ref_idx) {
		float r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 *= r0;
		return r0 + (1 - r0) * pow((1 - cos_theta), 5);
	}
};

#endif // ! DIELECTRIC_HPP