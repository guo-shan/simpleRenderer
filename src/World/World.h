#ifndef WORLD_H
#define WORLD_H

#include <iostream>

#include "Math/Vec.h"

#include "Core/HittableList.h"
#include "Core/Camera.h"
#include "Core/Material.h"

#include "Model/Sphere.h"
#include "Model/MovingSphere.h"
#include "Model/Constant_Medium.h"

#include "Accelerator/BVH.h"
#include "Accelerator/AARECT.h"
#include "Accelerator/Box.h"

#include "Material/Dielectric.hpp"
#include "Material/Diffuse.hpp"
#include "Material/Isotropic.hpp"
#include "Material/Lambertian.hpp"
#include "Material/Metal.hpp"

#include "Texture/Checker_Texture.hpp"
#include "Texture/Image_Texture.hpp"
#include "Texture/Noise_Texture.hpp"
#include "Texture/Solid_Color.hpp"

using std::make_shared;

Hittable_List random_scene() {
	Hittable_List world;

	auto checker = make_shared<Checker_Texture>(Color(0.2f, 0.3f, 0.1f), Color(0.9f, 0.9f, 0.9f));
	world.add(make_shared<Sphere>(Point3f(0, -1000, 0), 1000, make_shared<Lambertian>(checker)));

	for (int i = -11; i < 11; ++i) {
		for (int j = -11; j < 11; ++j) {
			auto choose_mat = random_float();
			Point3f center(i + 0.9 * random_float(), 0.2, j + 0.9 * random_float());

			if ((center - Point3f(4, 0.2, 0)).length() > 0.9) {
				std::shared_ptr<Material> sphere_material;
	;
				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = random_vec3() * random_vec3();
					sphere_material = make_shared<Lambertian>(albedo);
					auto center2 = center + Vec3f(0, random_float(0, 0.5), 0);
					world.add(make_shared<Moving_Sphere>(center, center2, 0.0, 1.0, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = random_vec3(0.5, 1);
					auto fuzzy = random_float(0, 0.5);
					sphere_material = make_shared<Metal>(albedo, fuzzy);
					world.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<Dielectric>(1.5);
					world.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<Dielectric>(1.5f);
	world.add(make_shared<Sphere>(Point3f(0.f, 1.f, 0.f), 1.f, material1));

	auto material2 = make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
	world.add(make_shared<Sphere>(Point3f(-4.f, 1.f, 0.f), 1.f, material2));

	auto material3 = make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.f);
	world.add(make_shared<Sphere>(Point3f(4.f, 1.f, 0.f), 1.f, material3));

	return Hittable_List(make_shared<BVH_Node>(world, 0.f, 1.f));
}

//Hittable_List two_Spheres() {
//	Hittable_List objects;
//
//	auto checker = make_shared<Checker_Texture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
//
//	objects.add(make_shared<Sphere>(Point3f(0, -10, 0), 10, make_shared<Lambertian>(checker)));
//	objects.add(make_shared<Sphere>(Point3f(0, 10, 0), 10, make_shared<Lambertian>(checker)));
//
//	return objects;
//
//}
//
//Hittable_List two_perlin_Spheres() {
//	Hittable_List objects;
//
//	auto pertext = make_shared<noise_texture>(4);
//
//	objects.add(make_shared<Sphere>(Point3f(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
//	objects.add(make_shared<Sphere>(Point3f(0, 2, 0), 2, make_shared<lambertian>(pertext)));
//
//	return objects;
//
//}
//
//Hittable_List earth() {
//	auto earth_texture = make_shared<image_texture>("..\\..\\..\\images\\earthmap.jpg");
//	auto earth_surface = make_shared<lambertian>(earth_texture);
//	auto globe = make_shared<Sphere>(Point3f(0, 0, 0), 2, earth_surface);
//
//	return Hittable_List(globe);
//}
//
//Hittable_List simple_light() {
//	Hittable_List objects;
//
//	auto pertext = make_shared<noise_texture>(4);
//	objects.add(make_shared<Sphere>(Point3f(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
//	objects.add(make_shared<Sphere>(Point3f(0, 2, 0), 2, make_shared<lambertian>(pertext)));
//
//	auto difflight = make_shared<Diffuse>(Color(4, 4, 4));
//	objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));
//
//	return objects;
//}

//Hittable_List cornell_box() {
//	Hittable_List objects;
//
//	auto red = make_shared<Lambertian>(Color(0.65, 0.05, 0.05));
//	auto white = make_shared<Lambertian>(Color(0.73, 0.73, 0.73));
//	auto green = make_shared<Lambertian>(Color(0.12, 0.45, 0.15));
//	auto light = make_shared<Diffuse>(Color(15, 15, 15));
//
//	objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
//	objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
//	objects.add(make_shared<flip_face>(make_shared<xz_rect>(213, 343, 227, 332, 554, light)));
//	objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
//	objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
//	objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));
//
//	//objects.add(make_shared<box>(Point3f(130, 0, 65), Point3f(295, 165, 230), white));
//	//objects.add(make_shared<box>(Point3f(265, 0, 295), Point3f(430, 330, 460), white));
//
//	//std::shared_ptr<Hittable> box1 = make_shared<Box>(Point3f(0, 0, 0), Point3f(165, 330, 165), white);
//	//box1 = make_shared<rotate_y>(box1, 15);
//	//box1 = make_shared<Translate>(box1, Vec3f(265, 0, 295));
//	//objects.add(box1);
//
//	//std::shared_ptr<Hittable> box2 = make_shared<Box>(Point3f(0, 0, 0), Point3f(165, 165, 165), white);
//	//box2 = make_shared<rotate_y>(box2, -18);
//	//box2 = make_shared<Translate>(box2, Vec3f(130, 0, 65));
//	//objects.add(box2);
//
//	std::shared_ptr<Material> aluminum = make_shared<Metal>(Color(0.8, 0.85, 0.88), 0.0);
//	std::shared_ptr<Hittable> box1 = make_shared<Box>(Point3f(0, 0, 0), Point3f(165, 330, 165), aluminum);
//	box1 = make_shared<rotate_y>(box1, 15);
//	box1 = make_shared<Translate>(box1, Vec3f(265, 0, 295));
//	objects.add(box1);
//
//	auto glass = make_shared<Dielectric>(1.5);
//	objects.add(make_shared<Sphere>(Point3f(190, 90, 190), 90, glass));
//
//	return objects;
//}

//
//Hittable_List cornell_smoke() {
//	Hittable_List objects;
//
//	auto red = make_shared<lambertian>(Color(0.65, 0.05, 0.05));
//	auto white = make_shared<lambertian>(Color(0.73, 0.73, 0.73));
//	auto green = make_shared<lambertian>(Color(0.12, 0.45, 0.15));
//	auto light = make_shared<Diffuse>(Color(7, 7, 7));
//
//	objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
//	objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
//	objects.add(make_shared<xz_rect>(113, 443, 127, 432, 554, light));
//	objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
//	objects.add(make_shared<xz_rect>(0, 555, 0, 555,   0, white));
//	objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));
//
//	shared_ptr<Hittable> box1 = make_shared<Box>(Point3f(0, 0, 0), Point3f(165, 330, 165), white);
//	box1 = make_shared<rotate_y>(box1, 15);
//	box1 = make_shared<Translate>(box1, Vec3f(265, 0, 295));
//
//	shared_ptr<Hittable> box2 = make_shared<Box>(Point3f(0, 0, 0), Point3f(165, 165, 165), white);
//	box2 = make_shared<rotate_y>(box2, -18);
//	box2 = make_shared<Translate>(box2, Vec3f(130, 0, 65));
//
//	objects.add(make_shared<constant_medium>(box1, 0.01, Color(0, 0, 0)));
//	objects.add(make_shared<constant_medium>(box2, 0.01, Color(1, 1, 1)));
//
//	return objects;
//}

Hittable_List final_scene() {
	Hittable_List boxes1;
	auto ground = make_shared<Lambertian>(Color(0.48, 0.83, 0.53));
	
	const int boxes_per_side = 20;
	for (int i = 0; i < boxes_per_side; ++i) {
		for (int j = 0; j < boxes_per_side; ++j) {
			auto w = 100.0;
			auto x0 = -1000.0 + i * w;
			auto z0 = -1000.0 + j * w;
			auto y0 = 0.0;
			auto x1 = x0 + w;
			auto y1 = random_float(1, 101);
			auto z1 = z0 + w;

			boxes1.add(make_shared<Box>(Point3f(x0, y0, z0), Point3f(x1, y1, z1), ground));
		}
	}

	Hittable_List objects;

	objects.add(make_shared<BVH_Node>(boxes1, 0, 1));

	auto light = make_shared<Diffuse>(Color(7, 7, 7));
	objects.add(make_shared<xz_rect>(123, 423, 147, 412, 554, light));

	auto center1 = Point3f(400, 400, 200);
	auto center2 = center1 + Vec3f(30, 0, 0);
	auto moving_sphere_material = make_shared<Lambertian>(Color(0.7, 0.3, 0.1));
	objects.add(make_shared<Moving_Sphere>(center1, center2, 0, 1, 50, moving_sphere_material));

	objects.add(make_shared<Sphere>(Point3f(260, 150, 45), 50, make_shared<Dielectric>(1.5)));
	objects.add(make_shared<Sphere>(Point3f(0, 150, 145), 50, make_shared<Metal>(Color(0.8, 0.8, 0.9), 1.0)));

	auto boundary = make_shared<Sphere>(Point3f(360, 150, 145), 70, make_shared<Dielectric>(1.5));
	objects.add(boundary);
	objects.add(make_shared<Constant_Medium>(boundary, 0.2, Color(0.2, 0.4, 0.9)));
	boundary = make_shared<Sphere>(Point3f(0, 0, 0), 5000, make_shared<Dielectric>(1.5));
	objects.add(make_shared<Constant_Medium>(boundary, 0.0001, Color(1, 1, 1)));

	auto emat = make_shared<Lambertian>(make_shared<Image_Texture>("C:/Users/guo/Downloads/learning/ray_tracing/SimpleRenderer/images/earthmap.jpg"));
	objects.add(make_shared<Sphere>(Point3f(400, 200, 400), 100, emat));
	auto pertext = make_shared<Noise_Texture>(0.1);
	objects.add(make_shared<Sphere>(Point3f(220, 280, 300), 80, make_shared<Lambertian>(pertext)));

	Hittable_List boxes2;
	auto white = make_shared<Lambertian>(Color(0.73, 0.73, 0.73));
	int ns = 1000;
	for (int i = 0; i < ns; ++i) {
		boxes2.add(make_shared<Sphere>(random_vec3(0, 165), 10, white));
	}

	 objects.add(make_shared<Translate>(make_shared<rotate_y>(make_shared<BVH_Node>(boxes2, 0.0, 1.0), 15), Vec3f(-100, 270, 395)));

	return objects;
}	

#endif

