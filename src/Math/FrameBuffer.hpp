#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

struct fragment_shader_payload {
    fragment_shader_payload() {
        texture = nullptr;
    }

    fragment_shader_payload(const Vec3f& col, const Vec3f& nor, const Vec2f& tc, Texture* tex) :
        color(col), normal(nor), tex_coords(tc), texture(tex) {}


    Vec3f view_pos;
    Vec3f color;
    Vec3f normal;
    Vec2f tex_coords;
    Texture* texture;
};

#endif // !FRAMEBUFFER_HPP
