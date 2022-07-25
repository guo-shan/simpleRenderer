#ifndef AREALIGHT_HPP
#define AREALIGHT_HPP

#include "../Math/Vec.h"
#include "../Math/Random.h"
#include "../Core/Light.hpp"

class AreaLight : public Light {
public:
    AreaLight(const Vec3f &p, const Vec3f &i) : Light(p, i) {
        normal = Vec3f(0.0, -1.0, 0.0);
        u = Vec3f(1.0, 0.0, 0.0);
        v = Vec3f(0.0, 0.0, 1.0);
        length = 100.0;
    }

    Vec3f SamplePoint() const {
        auto random_u = random_double();
        auto random_v = random_double();
        return position + random_u * u + random_v * v;
    }


public:
    Vec3f normal;
    Vec3f u;
    Vec3f v;
    double length;
};

#endif