#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include "Math/Vec.h"
#include "Math/Ray.h"
#include "Core/Hittable.h"
#include "Material/Isotropic.hpp"

class Constant_Medium : public Hittable {
public:
	Constant_Medium(std::shared_ptr<Hittable> b, float d, std::shared_ptr<Texture> a)
		: boundary(b), neg_inv_density(-1 / d), phase_function(std::make_shared<Isotropic>(a)) {}

	Constant_Medium(std::shared_ptr<Hittable> b, float d, Color c)
		: boundary(b), neg_inv_density(-1 / d), phase_function(std::make_shared<Isotropic>(c)) {}

	virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override {
		return boundary->bounding_box(time0, time1, output_box);
	}

public:
	std::shared_ptr<Hittable> boundary;
	std::shared_ptr<Material> phase_function;
	float neg_inv_density;
};

bool Constant_Medium::hit(const Ray& r, float t_min, float t_max, Object& rec) const {
	const bool enableDebug = false;
	const bool debugging = enableDebug && random_float() < 0.00001;

	Object rec1, rec2;

	if (!boundary->hit(r, -Infinity, Infinity, rec1)) return false;
	if (!boundary->hit(r, rec1.t + 0.0001, Infinity, rec2)) return false;

	if (debugging) std::cerr << "\nt_min = " << rec1.t << ", t_max = " << rec2.t << std::endl;

	if (rec1.t < t_min) rec1.t = t_min;
	if (rec2.t > t_max) rec2.t = t_max;

	if (rec1.t >= rec2.t) return false;

	if (rec1.t < 0) rec1.t = 0;

	const auto Ray_length = r.getDirection().length();
	const auto distance_inside_boundary = (rec2.t - rec1.t) * Ray_length;
	const auto hit_distance = neg_inv_density * log(random_float());

	if (hit_distance > distance_inside_boundary) return false;

	rec.t = rec1.t + hit_distance / Ray_length;
	rec.vertex.setPosition(r.at(rec.t));

	if (debugging) std::cerr << "hit_distance = " << hit_distance << std::endl
							 << "rec.t = " << rec.t << std::endl
							 << "rec.p = " << rec.vertex.getPosition() << std::endl;

	rec.vertex.setNormal(Vec3f(1, 0, 0));	// 随意设置
	rec.front_face = true;      // 随意设置
	rec.material_ptr = phase_function;

	return true;
}

#endif