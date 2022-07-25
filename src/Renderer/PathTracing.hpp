#ifndef PATHTRACING_HPP
#define PATHTRACING_HPP

#include "Core/Material.h"
#include "Core/Color.hpp"
#include "Accelerator/AARECT.h"
#include "Core/HittableList.h"

Color ray_color(const Ray& r, const Color& background, const Hittable& world, std::shared_ptr<Hittable> lights, int depth) {
    Object rec;

    if (depth <= 0)
        return Color(0, 0, 0);

    if (!world.hit(r, 0.001, Infinity, rec))
        return background;

    Scatter_Object srec;
    Color emitted = rec.material_ptr->emitted(r, rec, rec.vertex.getU(), rec.vertex.getV(), rec.vertex.getPosition());

    if (!rec.material_ptr->scatter(r, rec, srec))
        return emitted;

    if (srec.is_specular) {
        return srec.attenuation
            * ray_color(srec.specular_ray, background, world, lights, depth - 1);
    }

    auto light_ptr = std::make_shared<hittable_pdf>(lights, rec.vertex.getPosition());
    mixture_pdf p(light_ptr, srec.pdf_ptr);
    Ray scattered = Ray(rec.vertex.getPosition(), p.generate(), r.getTime());
    auto pdf_val = p.value(scattered.getDirection());

    return emitted + srec.attenuation * rec.material_ptr->scattering_pdf(r, rec, scattered) 
		 * ray_color(scattered, background, world, lights, depth - 1) / pdf_val;
}


class PathTracing {
public:
	void Render(cv::Mat& M, const Color& background, const Hittable& world, const Camera& cam) {
		std::cout << "路径追踪：正在渲染中，请稍后" << std::endl;
		auto lights = std::make_shared<Hittable_List>();
		lights->add(std::make_shared<xz_rect>(213, 343, 227, 332, 554, std::shared_ptr<Material>()));
		lights->add(std::make_shared<Sphere>(Point3f(190, 90, 190), 90, std::shared_ptr<Material>()));
		for (int j = 0; j < image_height; ++j) {
			for (int i = 0; i < image_width; ++i) {
				Color pixel_color(0, 0, 0);
				for (int s = 0; s < samples_per_pixel; ++s) {
					auto u = (i + random_float()) / (image_width - 1);
					auto v = (j + random_float()) / (image_height - 1);
					Ray r = cam.get_ray(u, v);
					pixel_color += ray_color(r, background, world, lights, max_depth);
				}
				pixel_color = write_color(std::cout, pixel_color, samples_per_pixel);

				M.at<cv::Vec3b>(i, j)[0] = static_cast<char>((int)pixel_color[2]);
				M.at<cv::Vec3b>(i, j)[1] = static_cast<char>((int)pixel_color[1]);
				M.at<cv::Vec3b>(i, j)[2] = static_cast<char>((int)pixel_color[0]);

				UpdateProgress(j / image_height);
			}
			UpdateProgress(1.0);
		}
		std::cout << "渲染完成" << std::endl;
	}
};

#endif // !PATHTRACING_HPP
