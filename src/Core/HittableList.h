#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "../Math/Vec.h"
#include "../Math/Ray.h"
#include "Hittable.h"
#include "../Accelerator/AABB.h"

#include <memory>
#include <vector>

class Hittable_List : public Hittable {
public:
	Hittable_List() {}
	Hittable_List(std::shared_ptr<Hittable> object) { add(object); }

	void clear() { objects.clear(); }
	void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

	virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override;

	virtual float pdf_value(const Vec3f& o, const Vec3f& v) const override;

	virtual Vec3f random(const Vec3f& o) const override;

public:
	std::vector<std::shared_ptr<Hittable>> objects;
};

bool Hittable_List::hit(const Ray& r, float t_min, float t_max, Object& rec) const {
	Object temp_obj;
	bool hit_anything = false;
	float closest_so_far = t_max;

	for (const auto& object : objects) {
		if (object->hit(r, t_min, closest_so_far, temp_obj)) {
			hit_anything = true;
			closest_so_far = temp_obj.t;
			rec = temp_obj;
		}
	}
	return hit_anything;
}

bool Hittable_List::bounding_box(float time0, float time1, AABB& output_box) const {
	if (objects.empty()) return false;

	AABB temp_box;
	bool first_box = true;

	for (const auto& object : objects) {
		if (!object->bounding_box(time0, time1, temp_box)) return false;
		output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
		first_box = false;
	}

	return true;
}


float Hittable_List::pdf_value(const Point3f& o, const Vec3f& v) const {
	auto weight = 1.0 / objects.size();
	auto sum = 0.0;

	for (const auto& object : objects)
		sum += weight * object->pdf_value(o, v);

	return sum;
}


Vec3f Hittable_List::random(const Vec3f& o) const {
	auto int_size = static_cast<int>(objects.size());
	return objects[random_int(0, int_size - 1)]->random(o);
}

#endif // !HITTABLE_LIST_H