#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "../Math/Vec.h"

class Light {
public:
    Light(const Vec3f &p, const Vec3f &i) : position(p), intensity(i) {}
    Vec3f position;
    Vec3f intensity;
};

#endif