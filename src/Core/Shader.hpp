#ifndef SHADER_HPP
#define SHADER_HPP

#include "Math/Vec.h"
#include "Core/Light.hpp"
#include "Core/Rasterizer_Texture.hpp"
#include <vector>

struct Vertex_Shader_Payload {
    Vec3f position;
};

struct Fragment_Shader_Payload {
    Fragment_Shader_Payload() : texture(nullptr) {}

    Fragment_Shader_Payload(const Vec3f& col, const Vec3f& nor, const Vec2f& tc, Rasterizer_Texture* tex) :
        color(col), normal(nor), tex_coords(tc), texture(tex) {}

    Vec3f view_pos;
    Vec3f color;
    Vec3f normal;
    Vec2f tex_coords;
    Rasterizer_Texture* texture;
};

class Vertex_Shader {
public:
    Vec3f value(const Vertex_Shader_Payload& payload) {
        return payload.position;
    }
};

class Fragment_Shader {
public:
    virtual Vec3f value(const Fragment_Shader_Payload& payload) const {
        return Vec3f(0, 0, 0);
    }

};

#endif // !SHADER_HPP
