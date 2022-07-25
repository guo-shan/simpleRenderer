#ifndef VERTEX_H
#define VERTEX_H

#include "Vec.h"


class Vertex {
public:
	Vertex() {}

	Vertex(const Point3f &pos, const Vec3f &n, const Vec2f &uv_coor) : position(pos), normal(n), uv(uv_coor) {}

	const Point3f& getPosition() const { return position; }
	const Vec3f& getNormal() const { return normal; }
	const float& getU() const { return uv.getU(); }
	const float& getV() const { return uv.getV(); }

	void setPosition(const Point3f& pos) { position = pos; }
	void setNormal(const Vec3f& n) { normal = n; }

public:
	Point3f position;
	Vec3f normal;
	Vec2f uv;
};


#endif