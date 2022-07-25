#ifndef CAMERA_H
#define CAMERA_H

#include "Math/Random.h"
#include "Math/Vec.h"
#include "Math/Ray.h"

class Camera {
public:
	Camera() : Camera(Point3f(0, 0, -1), Point3f(0, 0, 0), Vec3f(0, 1, 0), 40, 1, 0, 10) {}

	// vfov �Զ�Ϊ��λ�Ĵ�ֱ��Ұ aspect_ratio ���ݱ� aperture ��Ȧ focus_dist ����
	Camera(
		Point3f lookfrom,
		Point3f lookat,
		Vec3f viewup,
		float vfov,
		float aspect_ratio,
		float aperture,
		float focus_dist,
		float _time0 = 0,
		float _time1 = 0
	) {
		auto theta = degrees_to_radians(vfov);
		auto h = std::tan(theta / 2);
		auto viewport_height = 2.f * h;
		auto viewport_width = aspect_ratio * viewport_height;

		w = normalize(lookfrom - lookat);
		u = normalize(cross(viewup, w));
		v = cross(w, u);

		origin = lookfrom;
		horizontal = focus_dist * viewport_width * u;
		vertical = focus_dist * viewport_height * v;
		// �ӿ����½�����
		lower_left_corner = origin - horizontal / 2.f - vertical / 2.f - focus_dist * w;

		lens_radius = aperture / 2;

		time0 = _time0;
		time1 = _time1;
	}

	Ray get_ray(float s, float t) const {
		Vec3f rd = lens_radius * random_in_unit_disk(); // ��ͷ�뾶 * ��λԲƫ��
		Vec3f offset = u * rd.getX() + v * rd.getY(); // Դ��ƫ����
		// �����߼��������ʱ������
		return Ray(
			origin + offset, 
			lower_left_corner + s * horizontal + t * vertical - origin - offset, 
			random_float(time0, time1)); //���ʱ��
	}
private:
	Point3f origin;
	Point3f lower_left_corner;
	Vec3f horizontal;
	Vec3f vertical;
	Vec3f u, v, w;
	// �����ͷ�뾶
	float lens_radius;
	// ���ſ�/��ʱ��
	float time0, time1;
};

#endif