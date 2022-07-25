#ifndef RAY_TRACING_HPP
#define RAY_TRACING_HPP

#include "Core/Material.h"
#include "Core/Color.hpp"

const int samples_per_pixel = 20;
const int max_depth = 50;

Color ray_color(const Ray& r, const Color& background, const Hittable& world, int depth) {
	Object obj;

	if (depth <= 0)
		return Color(0, 0, 0);

	if (!world.hit(r, 0.001, Infinity, obj))
		return background;

	Ray scattered;
	Color attenuation;
	Color emitted = obj.material_ptr->emitted(obj.vertex.getU(), obj.vertex.getV(), obj.vertex.getPosition());

	if (!obj.material_ptr->scatter(r, obj, attenuation, scattered))
		return emitted;

	return emitted + attenuation * ray_color(scattered, background, world, depth - 1);
}

void set_pixel(const Vec2i& point, const Vec3f& color) {

}

class RayTracing {
public:
	void Render(const Color& background, const Hittable& world, const Camera& cam) {
		std::vector<Vec3f> frame_buf(image_width * image_height);
		std::cout << "光线追踪：正在渲染中，请稍后" << std::endl;

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		cv::Mat image(image_height, image_width, CV_8UC3);

		FILE* fp = fopen("binary.ppm", "wb");
		(void)fprintf(fp, "P6\n%d %d\n255\n", image_width, image_height);

		for (int j = image_height - 1; j >= 0; --j) {
			for (int i = 0; i < image_width; ++i) {
				Color pixel_color(0, 0, 0);
				static unsigned char color[3];
				for (int s = 0; s < samples_per_pixel; ++s) {
					auto u = (i + random_float()) / (image_width - 1);
					auto v = (j + random_float()) / (image_height - 1);
					Ray r = cam.get_ray(u, v);
					pixel_color += ray_color(r, background, world, max_depth);
				}
				pixel_color = write_color(std::cout, pixel_color, samples_per_pixel);
				color[0] = (unsigned char)(pixel_color[0]);
				color[1] = (unsigned char)(pixel_color[1]);
				color[2] = (unsigned char)(pixel_color[2]);
				fwrite(color, 1, 3, fp);

				//int ind = (image_height - j - 1) * image_width + i;
				//frame_buf[ind] = pixel_color;

				image.at<cv::Vec3b>(image_height - 1 - j, i)[0] = static_cast<unsigned char>(pixel_color[2]);
				image.at<cv::Vec3b>(image_height - 1 - j, i)[1] = static_cast<unsigned char>(pixel_color[1]);
				image.at<cv::Vec3b>(image_height - 1 - j, i)[2] = static_cast<unsigned char>(pixel_color[0]);
				UpdateProgress((float) j / image_height);
			}
			UpdateProgress(1.0);
		}

		//cv::Mat image(image_height, image_width, CV_32FC3, frame_buf.data());
		//image.convertTo(image, CV_8UC3, 1.f);
		//cv::cvtColor(image, image, cv::COLOR_RGB2BGR);

		cv::imshow("image", image);
	}
};

#endif // !RAY_TRACING_HPP
