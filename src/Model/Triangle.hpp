//#ifndef TRIANGLE_HPP
//#define TRIANGLE_HPP
//
//#include "Core/Hittable.h"
//#include "Math/Vec.h"
//#include "Math/Ray.h"
//
//class Triangle : public Hittable {
//public:
//    Triangle(Point3d _A, Point3d _B, Point3d _C, std::shared_ptr<Material> _m = nullptr) : A(_A), B(_B), C(_C), m(_m) {
//        AB = B - A;
//        AC = C - A;
//        normal = normalize(cross(AB, AC));
//        area = cross(AB, AC).length() * 0.5;
//    }
//
//    virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override;
//
//    virtual bool bounding_box(float time0, float time1, AABB& output_box) const override;
//
//    virtual float pdf_value(const Point3f& o, const Vec3f& v) const override;
//
//    virtual Vec3f random(const Point3f& o) const override;
//private:
//    Vec3f A, B, C; // 顶点 A, B, C
//    Vec3f AB, AC;  // 边 AB, AC
//    Vec3f normal;
//    float area;
//	std::shared_ptr<Material> material_ptr;
//};
//
//bool Triangle::hit(const Ray& r, float t_min, float t_max, Object& rec) const {
//    Object obj;
//
//    //if (dot(ray.direction, normal) > 0)
//    //    return inter;
//    //float u, v, t_tmp = 0;
//    //Vec3f pvec = cross(ray.direction, e2);
//    //float det = dot(e1, pvec); // 分母特别小，则t会特别大，人眼看不见
//    //if (fabs(det) < EPSILON)
//    //    return inter;
//
//    //float det_inv = 1. / det;
//    //Vec3f tvec = ray.origin - v0;
//    //u = dot(tvec, pvec) * det_inv;
//    //if (u < 0 || u > 1)
//    //    return inter;
//    //Vec3f qvec = cross(tvec, e1);
//    //v = dot(ray.direction, qvec) * det_inv;
//    //if (v < 0 || u + v > 1)
//    //    return inter;
//    //t_tmp = dot(e2, qvec) * det_inv;
//    //if (t_tmp < 0) return inter;
//
//    //inter.coords = ray.origin + t_tmp * ray.direction;
//    //inter.distance = t_tmp;
//    //inter.happened = true;
//    //inter.m = m;
//    //inter.normal = normal;
//    //inter.obj = this;
//    //return inter;
//}
//
//bool Triangle::bounding_box(float time0, float time1, AABB& output_box) const {
//    //return surrounding_box(AABB(A, B), C);
//}
//
//float Triangle::pdf_value(const Point3d& o, const Vec3f& v) const {
//
//}
//
//Vec3f Triangle::random(const Point3d& o) const {
//
//}
//
//#endif // TRIANGLE_HPP 