#ifndef RAY_H
#define RAY_H

#include "Vec.h"

// π‚œﬂ¿‡
class Ray {
public:
	Ray() {}
	Ray(const Point3f& origin, const Vec3f& direction, float time = 0.0f) : orig(origin), dir(direction), tm(time) {}
	
	Point3f getOrigin() const { return orig; }
	Vec3f getDirection() const { return dir; }
	float getTime() const { return tm; }

	void setOrigin(const Point3f& origin) { orig = origin; }
	void setDirection(const Vec3f& direction) { dir = direction; }
	void setTime(const float& time) { tm = time; }

	Vec3f at(const float& t) const {
		return orig + t * dir;
	}

private:
	Point3f orig;
	Vec3f dir;
	float tm;
};

#endif