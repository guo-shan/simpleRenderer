#ifndef ONB_H
#define ONB_H

#include "Math/Vec.h"

class onb {
public:
	onb() {}
	inline Vec3f operator[](int i) const { return axis[i]; }

	Vec3f getU() const{ return axis[0]; }
	Vec3f getV() const{ return axis[1]; }
	Vec3f getW() const{ return axis[2]; }

	Vec3f local(float a, float b, float c) const {
		return a * getU() + b * getV() + c * getW();
	}

	Vec3f local(const Vec3f& a) const {
		return a.getX() * getU() + a.getY() * getV() + a.getZ() * getW();
	}

	void build_from_normal(const Vec3f&);

public:
	Vec3f axis[3];
};

void onb::build_from_normal(const Vec3f& n) {
	axis[2] = normalize(n);
	Vec3f a = (std::fabs(getW().getX()) > 0.9) ? Vec3f(0, 1, 0) : Vec3f(1, 0, 0);
	axis[1] = normalize(cross(getW(), a));
	axis[0] = cross(getW(), getV());
}
#endif // !ONB_H
