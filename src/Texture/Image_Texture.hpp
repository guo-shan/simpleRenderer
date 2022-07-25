#ifndef IMAGE_TEXTURE_HPP
#define IMAGE_TEXTURE_HPP

#include "Core/stb_image.h"
#include "Core/Texture.h"

class Image_Texture : public Texture {
public:
	const static int bytes_per_pixel = 3;
	Image_Texture() : data(nullptr), width(0), height(0), bytes_per_scanline(0) {}

	Image_Texture(const char* filename) {
		auto components_per_pixel = bytes_per_pixel;

		data = stbi_load(filename, &width, &height, &components_per_pixel, components_per_pixel);

		if (!data) {
			std::cerr << "ERROR : Could not load texture image file '" << filename << "'" << std::endl;
			width = height = 0;
		}

		bytes_per_scanline = bytes_per_pixel * width;
	}

	~Image_Texture() {
		delete data;
	}

	virtual Color value(float u, float v, const Vec3f& p) const override {
		// 如果没有纹理数据，则返回纯青色
		if (data == nullptr) return Color(0, 1, 1);

		// 将输入纹理坐标约束为 [0,1] x [1,0]
		u = clamp_to_num(u, 0.0f, 1.0f);
		v = 1.0 - clamp_to_num(v, 0.0f, 1.0f);
		
		auto i = static_cast<int>(u * width);
		auto j = static_cast<int>(v * height);

		// 实际坐标应该小于 1.0
		if (i >= width) i = width - 1;
		if (j >= height) j = height - 1;

		const auto color_scale = 1.0 / 255.0;
		auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;

		return Color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
	}

public:
	int width, height;
private:
	unsigned char* data;
	int bytes_per_scanline;
};

#endif // !IMAGE_TEXTURE_HPP
