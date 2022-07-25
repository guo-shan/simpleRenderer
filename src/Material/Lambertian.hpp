#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "Core/PDF.h"
#include "Math/Defs.h"
#include "Math/Vec.h"
#include "Core/Material.h"
#include "Core/Texture.h"

class Lambertian : public Material {
public:
    Lambertian(const Color& a) : albedo(std::make_shared<Solid_Color>(a)) {}
    Lambertian(std::shared_ptr<Texture> a) : albedo(a) {}
    virtual bool scatter(const Ray& r_in, const Object& obj, Color& attenuation, Ray& scattered) const override {
        Vec3f scatter_direction = obj.vertex.getNormal() + random_unit_vector();
        if (scatter_direction.near_zero()) scatter_direction = obj.vertex.getNormal();
        scattered = Ray(obj.vertex.getPosition(), scatter_direction, r_in.getTime());
        attenuation = albedo->value(obj.vertex.getU(), obj.vertex.getV(), obj.vertex.getPosition());
        return true;
    }
    virtual bool scatter(const Ray& r_in, const Object& obj, Scatter_Object& sobj) const override {
        sobj.is_specular = false;
        sobj.attenuation = albedo->value(obj.vertex.getU(), obj.vertex.getV(), obj.vertex.getPosition());
        sobj.pdf_ptr = std::make_shared<cosine_hemisphere_pdf>(obj.vertex.getNormal());
        return true;
    }
    virtual float scattering_pdf(const Ray& r_in, const Object& obj, const Ray& scattered) const override {
        auto cosine = dot(obj.vertex.getNormal(), normalize(scattered.getDirection()));
        return cosine < 0 ? 0 : cosine / PI;
    }

public:
    std::shared_ptr<Texture> albedo;
};

#endif // !LAMBERTIAN_HPP


