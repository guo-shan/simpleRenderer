#ifndef Moving_Sphere_H
#define Moving_Sphere_H

#include "Math/Vec.h"
#include "Math/Ray.h"
#include "../Core/Hittable.h"
#include "../Accelerator/AABB.h"

class Moving_Sphere : public Hittable {
public:
	Moving_Sphere() {}
	Moving_Sphere(Point3f cen0, Point3f cen1, float _time0, float _time1, float r, std::shared_ptr<Material> m)
		: center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), material_ptr(m) {}
	
	virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override;
	
	virtual bool bounding_box(float _time0, float _time1, AABB& output_box) const override;

	Point3f center(float time) const;

public:
	Point3f center0, center1;
	float time0, time1;
	float radius;
	std::shared_ptr<Material> material_ptr;
};

Point3f Moving_Sphere::center(float time) const {
	return center0 + (time - time0) / (time1 - time0) * (center1 - center0);
}

bool Moving_Sphere::hit(const Ray& r, float t_min, float t_max, Object& rec) const {
	Vec3f co = r.getOrigin() - center(r.getTime());
	float a = r.getDirection().length_squared();
	float half_b = dot(r.getDirection(), co);
	float c = co.length_squared() - radius * radius;
	float discriminant = half_b * half_b - a * c;

	if (discriminant < 0) return false;
	float root = sqrt(discriminant);
	float t = (-half_b - root) / a;
	if (t < t_min || t > t_max) {
		t = (-half_b + root) / a;
		if (t < t_min || t > t_max)
			return false;
	}

	rec.t = t;
	rec.vertex.setPosition(r.at(rec.t));
	Vec3f outward_normal = (rec.vertex.getPosition() - center(r.getTime())) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.material_ptr = material_ptr;

	return true;
}

bool Moving_Sphere::bounding_box(float _time0, float _time1, AABB& output_box) const {
	AABB box0(center(_time0) - Vec3f(radius, radius, radius), center(_time0) + Vec3f(radius, radius, radius));
	AABB box1(center(_time1) - Vec3f(radius, radius, radius), center(_time1) + Vec3f(radius, radius, radius));
	output_box = surrounding_box(box0, box1);
	return true;
}

#endif