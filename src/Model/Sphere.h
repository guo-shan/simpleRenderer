#ifndef SPHERE_H
#define SPHERE_H

#include "Math/Vec.h"
#include "Math/Ray.h"
#include "Math/Defs.h"
#include "Math/Random.h"
#include "Core/ONB.h"
#include "Core/Hittable.h"
#include "Accelerator/AABB.h"

class Sphere : public Hittable {
public:
	Sphere() {}
	Sphere(Point3f c, float r) : center(c), radius(r) {}
	Sphere(Point3f c, float r, std::shared_ptr<Material> m) : center(c), radius(r), mat_ptr(m) {}

	virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override;

	virtual float pdf_value(const Point3f& o, const Vec3f& v) const override;

	virtual Vec3f random(const Point3f& o) const override;

public:
	Point3f center;
	float radius;
	std::shared_ptr<Material> mat_ptr;
private:
	static void get_sphere_uv(const Point3f& p, Vec2f& uv) {
		auto theta = std::acos(-p.getY());
		auto phi = std::atan2(-p.getZ(), p.getX()) + PI;

		uv.x = phi / (2 * PI);
		uv.y = theta / PI;
	}
};

bool Sphere::hit(const Ray& r, float t_min, float t_max, Object& rec) const {
	Vec3f co = r.getOrigin() - center;
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

	rec.set_distance(t);
	rec.set_position(r.at(rec.t));
	Vec3f outward_normal = (rec.vertex.getPosition() - center) / radius;
	rec.set_face_normal(r, outward_normal);
	get_sphere_uv(outward_normal, rec.vertex.uv);
	rec.material_ptr = mat_ptr;

	return true;
}

bool Sphere::bounding_box(float time0, float time1, AABB& output_box) const {
	output_box = AABB(center - Vec3f(radius, radius, radius), center + Vec3f(radius, radius, radius));
	return true;
}

float Sphere::pdf_value(const Point3f& o, const Vec3f& v) const {
    Object rec;
    if (!this->hit(Ray(o, v), 0.001, Infinity, rec))
        return 0;

    auto cos_theta_max = std::sqrt(1 - radius * radius / (center - o).length_squared());
    auto solid_angle = 2 * PI * (1 - cos_theta_max);

    return  1 / solid_angle;
}

Vec3f Sphere::random(const Point3f& o) const {
    Vec3f direction = center - o;
    auto distance_squared = direction.length_squared();
    onb uvw;
    uvw.build_from_normal(direction);
    return uvw.local(random_to_sphere_direction(radius, distance_squared));
}

#endif // !SPHERE_H
