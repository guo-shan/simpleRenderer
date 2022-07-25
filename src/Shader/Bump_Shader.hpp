#ifndef BUMP_FRAGMENT_HPP
#define BUMP_FRAGMENT_HPP

#include "../Core/Shader.hpp"

class Bump_Fragment_Shader : public Fragment_Shader {
public:
	virtual Vec3f value(const Fragment_Shader_Payload& payload) const override;
};

Vec3f Bump_Fragment_Shader::value(const Fragment_Shader_Payload& payload) const {
	Vec3f ka = Vec3f(0.005, 0.005, 0.005);
	Vec3f kd = payload.color;
	Vec3f ks = Vec3f(0.7937, 0.7937, 0.7937);

	auto l1 = Light(Vec3f(20, 20, 20), Vec3f(500, 500, 500));
	auto l2 = Light(Vec3f(-20, 20, 0), Vec3f(500, 500, 500));

	std::vector<Light> lights = { l1, l2 };
	Vec3f amb_light_intensity(10, 10, 10);
	Vec3f eye_pos(0, 0, 10);

	float p = 150;

	Vec3f color = payload.color;
	Vec3f point = payload.view_pos;
	Vec3f normal = payload.normal;

	float kh = 0.2, kn = 0.1;

	float x = normal.getX();
	float y = normal.getY();
	float z = normal.getZ();
	Vec3f n = normal;
	Vec3f t(x * y / sqrt(x * x + z * z), sqrt(x * x + z * z), z * y / sqrt(x * x + z * z));
	Vec3f b = cross(n, t);
	Mat3f TBN(t, b, n);
	float u = payload.tex_coords.getU();
	float v = payload.tex_coords.getV();
	float w = payload.texture->width;
	float h = payload.texture->height;
	float dU = kh * kn * (payload.texture->getColor(u + 1 / w, v).length() - payload.texture->getColor(u, v).length());
	float dV = kh * kn * (payload.texture->getColor(u, v + 1 / h).length() - payload.texture->getColor(u, v).length());
	Vec3f ln(-dU, -dV, 1);
	Vec3f result_color = normalize(TBN * ln);

	return result_color * 255.f;
}

#endif // !BUMP_FRAGMENT_HPP