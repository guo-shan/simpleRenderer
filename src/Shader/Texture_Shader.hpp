#ifndef TEXTURE_FRAGMENT_SHADER
#define TEXTURE_FRAGMENT_SHADER

#include "../Core/Shader.hpp"

class Texture_Fragment_Shader : public Fragment_Shader {
public:
	virtual Vec3f value(const Fragment_Shader_Payload& payload) const override;
};

Vec3f Texture_Fragment_Shader::value(const Fragment_Shader_Payload& payload) const {
	Vec3f return_color(0.f, 0.f, 0.f);
	if (payload.texture) {
		return_color = payload.texture->getColor(payload.tex_coords.getU(), payload.tex_coords.getV());
	}
	Vec3f texture_color(return_color.getX(), return_color.getY(), return_color.getZ());

	Vec3f ka = Vec3f(0.005f, 0.005f, 0.005f);
	Vec3f kd = texture_color / 255.0f;
	Vec3f ks = Vec3f(0.7937f, 0.7937f, 0.7937f);

	auto l1 = Light(Vec3f(20, 20, 20), Vec3f(500, 500, 500));
	auto l2 = Light(Vec3f(-20, 20, 0), Vec3f(500, 500, 500));

	std::vector<Light> lights = { l1, l2 };
	Vec3f amb_light_intensity(10, 10, 10);
	Vec3f eye_pos(0, 0, 10);

	float p = 150;

	Vec3f color = texture_color;
	Vec3f point = payload.view_pos;
	Vec3f normal = payload.normal;

	Vec3f result_color(0, 0, 0);

	for (auto& light : lights) {
		Vec3f LightDir = normalize(light.position - point);
		Vec3f ViewDir = normalize(eye_pos - point);
		Vec3f H = normalize(LightDir + ViewDir);
		Vec3f Diffuse = kd * (light.intensity / dot(light.position - point, light.position - point)) * max(0.0f, dot(normalize(normal), LightDir));
		Vec3f Specular = ks * (light.intensity / dot(light.position - point, light.position - point)) * pow(max(0.0f, dot(normalize(normal), H)), p);
		result_color += Diffuse + Specular;
	}
	Vec3f Ambient = ka * amb_light_intensity;
	result_color += Ambient;

	return result_color * 255.f;
}

#endif // !TEXTURE_FRAGMENT_SHADER
