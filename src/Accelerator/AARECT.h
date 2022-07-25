#ifndef AARECT_H
#define AARECT_H

#include "../Math/Vec.h"
#include "../Core/Hittable.h"

// 位于 z = k 处的 (x0, x1), (y0, y1) 的 xy_rect light
class xy_rect : public Hittable {
public:
	xy_rect() {}

	xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, std::shared_ptr<Material> m)
		: x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mat_ptr(m) {}

	virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override {
		// 边界框在每个维度上必须有非零宽度，所以Z维度填充少量。
		output_box = AABB(Point3f(x0, y0, k - 0.0001), Point3f(x1, y1, k + 0.0001));
		return true;
}
	

public:
	std::shared_ptr<Material> mat_ptr;
	float x0, x1, y0, y1, k;
};

bool xy_rect::hit(const Ray& r, float t_min, float t_max, Object& rec) const {
	auto t = (k - r.getOrigin().getZ()) / r.getDirection().getZ();
	if (t < t_min || t > t_max) return false;
	auto x = r.getOrigin().getX() + t * r.getDirection().getX();
	auto y = r.getOrigin().getY() + t * r.getDirection().getY();
	if (x < x0 || x > x1 || y < y0 || y > y1) return false;
	rec.vertex.uv.x = (x - x0) / (x1 - x0);
	rec.vertex.uv.y = (y - y0) / (y1 - y0);
	rec.t = t;
	auto outward_normal = Vec3f(0.f, 0.f, 1.f);
	rec.set_face_normal(r, outward_normal);
	rec.material_ptr = mat_ptr;
	rec.vertex.setPosition(r.at(t));
	return true;
}

class xz_rect : public Hittable {
public:
	xz_rect() {}

	xz_rect(float _x0, float _x1, float _z0, float _z1, float _k, std::shared_ptr<Material> m)
		: x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mat_ptr(m) {}

	virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override {
		// 边界框在每个维度上必须有非零宽度，所以Z维度填充少量。
		output_box = AABB(Point3f(x0, k - 0.0001, z0), Point3f(x1, k + 0.0001, z1));
		return true;
	}

public:
	std::shared_ptr<Material> mat_ptr;
	float x0, x1, z0, z1, k;
};

bool xz_rect::hit(const Ray& r, float t_min, float t_max, Object& rec) const {
	auto t = (k - r.getOrigin().getY()) / r.getDirection().getY();
	if (t < t_min || t > t_max) return false;
	auto x = r.getOrigin().getX() + t * r.getDirection().getX();
	auto z = r.getOrigin().getZ() + t * r.getDirection().getZ();
	if (x < x0 || x > x1 || z < z0 || z > z1) return false;
	rec.vertex.uv.x = (x - x0) / (x1 - x0);
	rec.vertex.uv.y = (z - z0) / (z1 - z0);
	rec.t = t;
	auto outward_normal = Vec3f(0.f, 1.f, 0.f);
	rec.set_face_normal(r, outward_normal);
	rec.material_ptr = mat_ptr;
	rec.vertex.setPosition(r.at(t));
	return true;
}

class yz_rect : public Hittable {
public:
	yz_rect() {}

	yz_rect(float _y0, float _y1, float _z0, float _z1, float _k, std::shared_ptr<Material> m)
		: y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mat_ptr(m) {}

	virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override {
		// 边界框在每个维度上必须有非零宽度，所以Z维度填充少量。
		output_box = AABB(Point3f(k - 0.0001, y0, z0), Point3f(k + 0.0001, y1, z1));
		return true;
	}

public:
	std::shared_ptr<Material> mat_ptr;
	float y0, y1, z0, z1, k;
};

bool yz_rect::hit(const Ray& r, float t_min, float t_max, Object& rec) const {
	auto t = (k - r.getOrigin().getX()) / r.getDirection().getX();
	if (t < t_min || t > t_max) return false;
	auto y = r.getOrigin().getY() + t * r.getDirection().getY();
	auto z = r.getOrigin().getZ() + t * r.getDirection().getZ();
	if (y < y0 || y > y1 || z < z0 || z > z1) return false;
	rec.vertex.uv.x = (y - y0) / (y1 - y0);
	rec.vertex.uv.y = (z - z0) / (z1 - z0);
	rec.t = t;
	auto outward_normal = Vec3f(1.f, 0.f, 0.f);
	rec.set_face_normal(r, outward_normal);
	rec.material_ptr = mat_ptr;
	rec.vertex.setPosition(r.at(t));
	return true;
}

#endif // !AARECT_H
