#ifndef HITTABLE_H
#define HITTABLE_H

#include "Math/Defs.h"
#include "Math/Vertex.h"
#include "Accelerator/AABB.h"

class Material;

// hittable物体抽象类
struct Object {
	float  t;			// 距离
	Vertex vertex;		// 顶点含: Point3d p 交点位置	、Vec3f normal 法向量、Vec2d uv 纹理坐标
	bool front_face;
	std::shared_ptr<Material> material_ptr;

	inline void set_face_normal(const Ray& r, const Vec3f& outward_normal) {
		front_face = dot(r.getDirection(), outward_normal) < 0;
		front_face ? set_normal(outward_normal) : set_normal(-outward_normal);
	}

	inline void set_distance(const float& distance) { t = distance; }
	inline void set_position(const Point3f& position) { vertex.setPosition(position); }
	inline void set_normal(const Vec3f& normal) { vertex.setNormal(normal); }
};

class Hittable {
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const = 0;
	virtual bool bounding_box(float time0, float time1, AABB& output_box) const = 0;
	virtual float pdf_value(const Vec3f& o, const Vec3f& v) const { return 0.0; }
	virtual Vec3f random(const Vec3f& o) const { return Vec3f(1.0, 0.0, 0.0); }
};


class flip_face : public Hittable {
public:
	flip_face(std::shared_ptr<Hittable> p) : ptr(p) {}

	virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override {
		if (!ptr->hit(r, t_min, t_max, rec))
			return false;

		rec.front_face = !rec.front_face;
		return true;
	}

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override {
		return ptr->bounding_box(time0, time1, output_box);
	}

public:
	std::shared_ptr<Hittable> ptr;
};

class Translate : public Hittable {
public:
	Translate(std::shared_ptr<Hittable> p, const Vec3f& displacement) : ptr(p), offset(displacement) {}

	virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override;

public:
	std::shared_ptr<Hittable> ptr;
	Vec3f offset;
};

bool Translate::hit(const Ray& r, float t_min, float t_max, Object& rec) const {
	Ray moved_r(r.getOrigin() - offset, r.getDirection(), r.getTime());
	if (!ptr->hit(moved_r, t_min, t_max, rec)) return false;

	rec.vertex.position += offset;
	rec.set_face_normal(moved_r, rec.vertex.getNormal());

	return true;
}

bool Translate::bounding_box(float time0, float time1, AABB& output_box) const {
	if (!ptr->bounding_box(time0, time1, output_box)) return false;

	output_box = AABB(output_box.min() + offset, output_box.max() + offset);

	return true;
}


class rotate_y : public Hittable {
public:
	rotate_y(std::shared_ptr<Hittable> p, float angle);

	virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override {
		output_box = bbox;
		return hasbox;
	}

public:
	std::shared_ptr<Hittable> ptr;
	float sin_theta;
	float cos_theta;
	bool hasbox;
	AABB bbox;
};

rotate_y::rotate_y(std::shared_ptr<Hittable> p, float angle) : ptr(p) {
	auto radians = degrees_to_radians(angle);
	sin_theta = sin(radians);
	cos_theta = cos(radians);
	hasbox = ptr->bounding_box(0, 1, bbox);

	Point3f min(Infinity, Infinity, Infinity);
	Point3f max(-Infinity, -Infinity, -Infinity);

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			for (int k = 0; k < 2; ++k) {
				auto x = i * bbox.max().getX() + (1 - i) * bbox.min().getX();
				auto y = j * bbox.max().getY() + (1 - j) * bbox.min().getY();
				auto z = k * bbox.max().getZ() + (1 - k) * bbox.min().getZ();
			
				auto newx = cos_theta * x + sin_theta * z;
				auto newz = -sin_theta * x + cos_theta * z;

				Vec3f tester(newx, y, newz);

				for (int c = 0; c < 3; ++c) {
					min[c] = fmin(min[c], tester[c]);
					max[c] = fmax(max[c], tester[c]);
				}
			}
		}
	}
	bbox = AABB(min, max);
}

bool rotate_y::hit(const Ray& r, float t_min, float t_max, Object& rec) const {
	auto origin = r.getOrigin();
	auto direction = r.getDirection();

	origin[0] = cos_theta * r.getOrigin()[0] - sin_theta * r.getOrigin()[2];
	origin[2] = sin_theta * r.getOrigin()[0] + cos_theta * r.getOrigin()[2];

	direction[0] = cos_theta * r.getDirection()[0] - sin_theta * r.getDirection()[2];
	direction[2] = sin_theta * r.getDirection()[0] + cos_theta * r.getDirection()[2];

	Ray rotated_r(origin, direction, r.getTime());

	if (!ptr->hit(rotated_r, t_min, t_max, rec)) return false;

	auto p = rec.vertex.position;
	auto normal = rec.vertex.normal;

	p[0] = cos_theta * rec.vertex.getPosition()[0] + sin_theta * rec.vertex.getPosition()[2];
	p[2] = -sin_theta * rec.vertex.getPosition()[0] + cos_theta * rec.vertex.getPosition()[2];

	normal[0] = cos_theta * rec.vertex.getNormal()[0] + sin_theta * rec.vertex.getNormal()[2];
	normal[2] = -sin_theta * rec.vertex.getNormal()[0] + cos_theta * rec.vertex.getNormal()[2];
	
	rec.vertex.setPosition(p);
	rec.set_face_normal(rotated_r, normal);

	return true;
}

#endif // !HITTABLE_H