#ifndef NOISE_TEXTURE_HPP
#define NOISE_TEXTURE_HPP

#include "Core/Texture.h"
#include "Perlin.h"

class Noise_Texture : public Texture {
public:
	Noise_Texture() {}
	Noise_Texture(float sc) : scale(sc) {}

	virtual Color value(float u, float v, const Vec3f& p) const override {
		// return color(1, 1, 1) * noise.noise(p);
		// return color(1,1,1) * noise.noise(scale * p);
		// return color(1, 1, 1) * 0.5 * (1.0 + noise.noise(scale * p));
		// return color(1, 1, 1) * noise.turb(scale * p);
		return Color(1, 1, 1) * 0.5f * (1 + sin(scale * p.getZ() + 10 * noise.turb(p)));
	}

public:
	perlin noise;
	float scale;
};

#endif // !NOISE_TEXTURE_HPP
