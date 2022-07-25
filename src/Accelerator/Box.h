#ifndef Box_H
#define Box_H

#include "Math/Vec.h"
#include "AARECT.h"
#include "Core/HittableList.h"

class Box : public Hittable {
public:
    Box() {}
    Box(const Point3f& p0, const Point3f& p1, std::shared_ptr<Material> ptr);

    virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override;

    virtual bool bounding_box(float time0, float time1, AABB& output_box) const override {
        output_box = AABB(minSide, maxSide);
        return true;
    }

public:
    Point3f minSide, maxSide;
    Hittable_List sides;
};

Box::Box(const Point3f& p0, const Point3f& p1, std::shared_ptr<Material> ptr) {
    minSide = p0;
    maxSide = p1;

    sides.add(std::make_shared<xy_rect>(p0.getX(), p1.getX(), p0.getY(), p1.getY(), p0.getZ(), ptr));
    sides.add(std::make_shared<xy_rect>(p0.getX(), p1.getX(), p0.getY(), p1.getY(), p1.getZ(), ptr));

    sides.add(std::make_shared<xz_rect>(p0.getX(), p1.getX(), p0.getZ(), p1.getZ(), p0.getY(), ptr));
    sides.add(std::make_shared<xz_rect>(p0.getX(), p1.getX(), p0.getZ(), p1.getZ(), p1.getY(), ptr));

    sides.add(std::make_shared<yz_rect>(p0.getY(), p1.getY(), p0.getZ(), p1.getZ(), p0.getX(), ptr));
    sides.add(std::make_shared<yz_rect>(p0.getY(), p1.getY(), p0.getZ(), p1.getZ(), p1.getX(), ptr));
}

bool Box::hit(const Ray& r, float t_min, float t_max, Object& rec) const {
    return sides.hit(r, t_min, t_max, rec);
}

#endif