#ifndef NORMAL_FRAGMENT_SHADER
#define NORMAL_FRAGMENT_SHADER

#include "../Core/Shader.hpp"

class Normal_Fragment_Shader : public Fragment_Shader {
public:
	virtual Vec3f value(const Fragment_Shader_Payload& payload) const override;
};

Vec3f Normal_Fragment_Shader::value(const Fragment_Shader_Payload& payload) const {
	Vec3f return_color = (normalize(payload.normal) + Vec3f(1.0f, 1.0f, 1.0f)) / 2.f;
	Vec3f result(return_color.getX() * 255.f, return_color.getY() * 255.f, return_color.getZ() * 255.f);
	return result;
}

#endif // !NORMAL_FRAGMENT_SHADER