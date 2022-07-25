#ifndef PDF_H
#define PDF_H

#include "Model/sphere.h"
#include "Math/Random.h"
#include "Math/Vec.h"
#include "onb.h"

class PDF {
public:

	virtual float value(const Vec3f& direction) const = 0;
	virtual Vec3f generate() const = 0;
};

class cosine_hemisphere_pdf : public PDF {
public:
	cosine_hemisphere_pdf(const Vec3f& n) { uvw.build_from_normal(n); }

	virtual float value(const Vec3f& direction) const override {
		auto cosine = dot(normalize(direction), uvw.getW());
		return (cosine <= 0) ? 0 : cosine / PI;
	}

	virtual Vec3f generate() const override {
		return uvw.local(random_cosine_hemisphere_direction());
	}

private:
	onb uvw;
};

class cosine_sphere_pdf : public PDF {
public:
	cosine_sphere_pdf(const Vec3f& n) { uvw.build_from_normal(n); }

	//virtual float value(const Vec3f& direction) const override {
	//	auto cosine = dot(normalize(direction), uvw.w());
	//	return (cosine <= 0) ? 0 : cosine / pi;
	//}

	virtual Vec3f generate() const override {
		return uvw.local(random_cosine_hemisphere_direction());
	}

private:
	onb uvw;
};

class hittable_pdf : public PDF {
public:
    hittable_pdf(std::shared_ptr<Hittable> p, const Point3f& origin) : ptr(p), o(origin) {}

    virtual float value(const Vec3f& direction) const override {
        return ptr->pdf_value(o, direction);
    }

    virtual Vec3f generate() const override {
        return ptr->random(o);
    }

public:
    Point3f o;
    std::shared_ptr<Hittable> ptr;
};


class mixture_pdf : public PDF {
public:
    mixture_pdf(std::shared_ptr<PDF> p0, std::shared_ptr<PDF> p1) {
        p[0] = p0;
        p[1] = p1;
    }

    virtual float value(const Vec3f& direction) const override {
        return 0.5 * p[0]->value(direction) + 0.5 * p[1]->value(direction);
    }

    virtual Vec3f generate() const override {
        if (random_float() < 0.5)
            return p[0]->generate();
        else
            return p[1]->generate();
    }

public:
    std::shared_ptr<PDF> p[2];
};

#endif // !PDF_H
