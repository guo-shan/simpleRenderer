#ifndef RASTERIZATION_HPP
#define RASTERIZATION_HPP

#include <optional>
#include <algorithm>

#include "Math/Matrix.h"
#include "Math/Matrix.cpp"
#include "Math/Vec.h"
#include "Core/Shader.hpp"
#include "Core/Rasterizer_Triangle.hpp"
#include "Core/Rasterizer_Texture.hpp"

enum class Buffers {
    Color = 1,
    Depth = 2
};

inline Buffers operator|(Buffers a, Buffers b) {
    return Buffers((int)a | (int)b);
}

inline Buffers operator&(Buffers a, Buffers b) {
    return Buffers((int)a & (int)b);
}

enum class Primitive {
    Line,
    Triangle
};

struct pos_buf_id {
    int pos_id = 0;
};

struct ind_buf_id {
    int ind_id = 0;
};

struct col_buf_id {
    int col_id = 0;
};


class Rasterization {
public:
    Rasterization(const int& w, const int& h, 
                  std::function<Vec3f(Vertex_Shader_Payload)>& vert_shader, 
                  std::function<Vec3f(Fragment_Shader_Payload)>& frag_shader);
    pos_buf_id load_positions(const std::vector<Vec3f>& positions);
    ind_buf_id load_indices(const std::vector<Vec3i>& indices);
    col_buf_id load_colors(const std::vector<Vec3f>& colors);
    col_buf_id load_normals(const std::vector<Vec3f>& normals);

    void set_model(const Mat4f& m);
    void set_view(const Mat4f& v);
    void set_projection(const Mat4f& p);
    void set_texture(Rasterizer_Texture tex) { texture = tex; }

    void set_vertex_shader(std::function<Vec3f(Vertex_Shader_Payload)> vert_shader);
    void set_fragment_shader(std::function < Vec3f(Fragment_Shader_Payload)> frag_shader);

    void set_pixel(const Vec2i& point, const Vec3f& color);

    void clear(Buffers buff);

    void draw(std::vector<Rasterizer_Triangle*>& TriangleList);

    std::vector<Vec3f>& frame_buffer() { return frame_buf; }

    void Render(std::vector<Rasterizer_Triangle*>& TriangleList);

private:

    void rasterize_triangle(const Rasterizer_Triangle& t, const std::array<Vec3f, 3>& world_pos);

private:
    Mat4f model;
    Mat4f view;
    Mat4f projection;

    int normal_id = -1;

    std::map<int, std::vector<Vec3f>> pos_buf;
    std::map<int, std::vector<Vec3i>> ind_buf;
    std::map<int, std::vector<Vec3f>> col_buf;
    std::map<int, std::vector<Vec3f>> nor_buf;

    std::optional<Rasterizer_Texture> texture;

    std::function<Vec3f(Fragment_Shader_Payload)> fragment_shader;
    std::function<Vec3f(Vertex_Shader_Payload)> vertex_shader;

    std::vector<Vec3f> frame_buf;
    std::vector<double> depth_buf;
    int get_index(int x, int y);

    int width, height;

    int next_id = 0;
    int get_next_id() { return next_id++; }
};


#endif // !RASTERIZATION_HPP
