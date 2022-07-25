#ifndef RASTERIZER_TRIANGLE_H
#define RASTERIZER_TRIANGLE_H

#include "Math/Vec.h"
#include "Core/Texture.h"

class Rasterizer_Triangle {
public:
    Rasterizer_Triangle() {
        v[0] = Vec4f(0, 0, 0, 1);
        v[1] = Vec4f(0, 0, 0, 1);
        v[2] = Vec4f(0, 0, 0, 1);

        color[0] = Vec3f(0.0, 0.0, 0.0);
        color[1] = Vec3f(0.0, 0.0, 0.0);
        color[2] = Vec3f(0.0, 0.0, 0.0);

        tex_coords[0] = Vec2f(0, 0);
        tex_coords[1] = Vec2f(0, 0);
        tex_coords[2] = Vec2f(0, 0);
    }

    Vec4f a() const { return v[0]; }
    Vec4f b() const { return v[1]; }
    Vec4f c() const { return v[2]; }

    void setVertex(int ind, Vec4f ver) { 
        v[ind] = ver; 
    }

    void setNormal(int ind, Vec3f n) { 
        normal[ind] = n; 
    }

    void setColor(int ind, float r, float g, float b) {
        if ((r < 0.0) || (r > 255.0) || (g < 0.0) || (g > 255.0) || (b < 0.0) || (b > 255.0)) {
            fprintf(stderr, "ERROR! Invalid color values");
            fflush(stderr);
            exit(-1);
        }
        color[ind] = Vec3f(r / 255.0, g / 255.0, b / 255.0);
    }

    void setNormals(const std::array<Vec3f, 3>& normals) {
        normal[0] = normals[0];
        normal[1] = normals[1];
        normal[2] = normals[2];
    }

    void setColors(const std::array<Vec3f, 3>& colors) {
        auto first_color = colors[0];
        setColor(0, colors[0][0], colors[0][1], colors[0][2]);
        setColor(1, colors[1][0], colors[1][1], colors[1][2]);
        setColor(2, colors[2][0], colors[2][1], colors[2][2]);
    }

    void setTexCoord(int ind, Vec2f uv) { 
        tex_coords[ind] = uv; 
    }

    std::array<Vec4f, 3> toVector4() const {
        std::array<Vec4f, 3> res;
        std::transform(std::begin(v), std::end(v), res.begin(), [](auto& vec) {
            return Vec4f(vec.getX(), vec.getY(), vec.getZ(), 1.0);
        });
        return res;
    }

public:
    Vec4f v[3];
    Vec3f color[3];
    Vec2f tex_coords[3];
    Vec3f normal[3];

    Texture* tex = nullptr;
};

#endif //RASTERIZER_TRIANGLE_H
