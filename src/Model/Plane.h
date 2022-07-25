//#ifndef PLANE_H
//#define PLANE_H
//
//#include "../Math/Vec.h"
//#include "../Math/Ray.h"
//#include "../Math/Defs.h"
//#include "../Math/Random.h"
//#include "../Core/onb.h"
//#include "../Core/Hittable.h"
//#include "../Accelerator/AABB.h"
//
//class Plane : public Hittable {
//public:
//	Plane() {}
//	Plane(Point3f& p, Vec3f& n) : position(p), normal(normalize(n)) {}
//	Plane(Point3f& c, Vec3f& n, std::shared_ptr<Material> m) : position(p), normal(normalize(n)), material_ptr(m) {}
//	virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override;
//
//private:
//	Point3f position;
//	Vec3f normal;
//	std::shared_ptr<Material> material_ptr;
//};
//
//bool Plane::hit(const Ray& r, float t_min, float t_max, Object& rec) const {
//	float a = dot(normal_, ray.direction());
//	if (a > 0) return false;
//
//	float b = -dot(ray.origin() - position_, normal_);
//
//	float dis = b / a;
//
//	if (dis > 0 && dis < isect.distance()) {
//		Point3f hitPos(ray.origin() + ray.direction() * dis);
//		isect.update(dis, this, hitPos, normal_, Point2f(), material_);
//		return true;
//	}
//	return false; 
//}
//
//#endif