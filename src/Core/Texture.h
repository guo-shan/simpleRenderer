#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "Math/Vec.h"

class Texture {
public:
	virtual Color value(float u, float v, const Vec3f& p) const = 0;
};

#endif