#ifndef AABB_H
#define AABB_H

#include "../Math/Vec.h"

class AABB {
public:
	AABB() {}
	AABB(const Point3f& a, const Point3f& b) { 
		minimum = Vec3f(fmin(a.getX(), b.getX()), fmin(a.getY(), b.getY()), fmin(a.getZ(), b.getZ()));
		maximum = Vec3f(fmax(a.getX(), b.getX()), fmax(a.getY(), b.getY()), fmax(a.getZ(), b.getZ()));
	}

	Point3f min() const { return minimum; }
	Point3f max() const { return maximum; }

	bool hit(const Ray& r, float t_min, float t_max) const;

	float area() const {
		auto a = maximum.getX() - minimum.getX();
		auto b = maximum.getY() - minimum.getY();
		auto c = maximum.getZ() - minimum.getZ();
		return 2 * (a * b + b * c + c * a);
	}

	int longest_axis() const {
		auto a = maximum.getX() - minimum.getX();
		auto b = maximum.getY() - minimum.getY();
		auto c = maximum.getZ() - minimum.getZ();
		if (a > b && a > c)
			return 0;
		else if (b > c)
			return 1;
		else
			return 2;
	}

public:
	Point3f minimum, maximum;
};

inline bool AABB::hit(const Ray& r, float t_min, float t_max) const {
	for (int i = 0; i < 3; ++i) {
		auto invD = 1.0f / r.getDirection()[i];
		auto t0 = (min()[i] - r.getOrigin()[i]) * invD;
		auto t1 = (max()[i] - r.getOrigin()[i]) * invD;
		if (invD < 0.0f) std::swap(t0, t1);
		t_min = t0 > t_min ? t0 : t_min;
		t_max = t1 < t_max ? t1 : t_max;
		if (t_max <= t_min) return false;
	}
	return true;
}

AABB surrounding_box(AABB box0, AABB box1) {
	Point3f small(fmin(box0.min().getX(), box1.min().getX()),
				  fmin(box0.min().getY(), box1.min().getY()),
				  fmin(box0.min().getZ(), box1.min().getZ()));
	Point3f big(fmax(box0.max().getX(), box1.max().getX()),
			    fmax(box0.max().getY(), box1.max().getY()),
		        fmax(box0.max().getZ(), box1.max().getZ()));
	return AABB(small, big);
}

AABB surrounding_box(AABB box, Vec3f u) {
	Point3f small(fmin(box.min().getX(), u.getX()),
				  fmin(box.min().getY(), u.getY()),
				  fmin(box.min().getZ(), u.getZ()));
	Point3f big(fmax(box.max().getX(), u.getX()),
				fmax(box.max().getY(), u.getY()),
				fmax(box.max().getZ(), u.getZ()));
	return AABB(small, big);
}
#endif