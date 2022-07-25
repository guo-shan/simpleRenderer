#include <algorithm>
#include <opencv2/opencv.hpp>
#include <math.h>

#include "Rasterization.hpp"

pos_buf_id Rasterization::load_positions(const std::vector<Vec3f>& positions) {
    auto id = get_next_id();
    pos_buf.emplace(id, positions);

    return { id };
}

ind_buf_id Rasterization::load_indices(const std::vector<Vec3i>& indices) {
    auto id = get_next_id();
    ind_buf.emplace(id, indices);

    return { id };
}

col_buf_id Rasterization::load_colors(const std::vector<Vec3f>& cols) {
    auto id = get_next_id();
    col_buf.emplace(id, cols);

    return { id };
}

col_buf_id Rasterization::load_normals(const std::vector<Vec3f>& normals) {
    auto id = get_next_id();
    nor_buf.emplace(id, normals);

    normal_id = id;

    return { id };
}

static bool insideTriangle(int x, int y, const Vec4f* _v) {
    Vec3f v[3];
    for (int i = 0; i < 3; i++)
        v[i] = { _v[i].getX(),_v[i].getY(), 1.0 };
    Vec3f f0, f1, f2;
    f0 = cross(v[1], v[0]);
    f1 = cross(v[2], v[1]);
    f2 = cross(v[0], v[2]);
    Vec3f p(x, y, 1.);
    if ((dot(p, f0) * dot(f0, v[2]) > 0) && (dot(p, f1) * dot(f1, v[0]) > 0) && (dot(p, f2) * dot(f2, v[1]) > 0))
        return true;
    return false;
}

// 重心坐标
static std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Vec4f* v) {
    float c1 = (x * (v[1].getY() - v[2].getY()) + (v[2].getX() - v[1].getX()) * y + v[1].getX() * v[2].getY() - v[2].getX() * v[1].getY()) / (v[0].getX() * (v[1].getY() - v[2].getY()) + (v[2].getX() - v[1].getX()) * v[0].getY() + v[1].getX() * v[2].getY() - v[2].getX() * v[1].getY());
    float c2 = (x * (v[2].getY() - v[0].getY()) + (v[0].getX() - v[2].getX()) * y + v[2].getX() * v[0].getY() - v[0].getX() * v[2].getY()) / (v[1].getX() * (v[2].getY() - v[0].getY()) + (v[0].getX() - v[2].getX()) * v[1].getY() + v[2].getX() * v[0].getY() - v[0].getX() * v[2].getY());
    float c3 = (x * (v[0].getY() - v[1].getY()) + (v[1].getX() - v[0].getX()) * y + v[0].getX() * v[1].getY() - v[1].getX() * v[0].getY()) / (v[2].getX() * (v[0].getY() - v[1].getY()) + (v[1].getX() - v[0].getX()) * v[2].getY() + v[0].getX() * v[1].getY() - v[1].getX() * v[0].getY());
    return { c1,c2,c3 };
}

void Rasterization::draw(std::vector<Rasterizer_Triangle*>& TriangleList) {
    // zFar和zNear之间的距离的一半
    float f1 = (50 - 0.1) / 2.0;
    // zFar与zNear的中心z坐标
    float f2 = (50 + 0.1) / 2.0;

    Mat4f mvp = projection * view * model;
    for (const auto& t : TriangleList) {
        Rasterizer_Triangle newtri = *t;

        std::array<Vec4f, 3> mm{
            (view * model * t->v[0]),
            (view * model * t->v[1]),
            (view * model * t->v[2])
        };

        std::array<Vec3f, 3> viewspace_pos;

        std::transform(mm.begin(), mm.end(), viewspace_pos.begin(), [](auto& v) {
            return Vec3f(v.getX(), v.getY(), v.getZ());
        });

        Vec4f v[] = {
            mvp * t->v[0],
            mvp * t->v[1],
            mvp * t->v[2]
        };
        // 未处理w维，因为w坐标记录了原本的z值
        for (auto& vec : v) {
            vec.x /= vec.getW();
            vec.y /= vec.getW();
            vec.z /= vec.getW();
        }

        Mat4f inv_trans = transpose4(inverse4(view * model));
        Vec4f n[] = {
                inv_trans * Vec4f(t->normal[0], 0.0),
                inv_trans * Vec4f(t->normal[1], 0.0),
                inv_trans * Vec4f(t->normal[2], 0.0)
        };

        // 视图变换
        for (auto& vert : v) {
            vert.x = 0.5 * width * (vert.getX() + 1.0);
            vert.y = 0.5 * height * (vert.getY() + 1.0);
            vert.z = vert.getZ() * f1 + f2;
        }

        for (int i = 0; i < 3; ++i) {
            newtri.setVertex(i, v[i]);
        }

        for (int i = 0; i < 3; ++i) {
            newtri.setNormal(i, vec4_to_vec3(n[i]));
        }

        newtri.setColor(0, 148, 121.0, 92.0);
        newtri.setColor(1, 148, 121.0, 92.0);
        newtri.setColor(2, 148, 121.0, 92.0);

        rasterize_triangle(newtri, viewspace_pos);
    }
}

static Vec3f interpolate(float alpha, float beta, float gamma, const Vec3f& vert1, const Vec3f& vert2, const Vec3f& vert3, float weight) {
    return (alpha * vert1 + beta * vert2 + gamma * vert3) / weight;
}

static Vec2f interpolate(float alpha, float beta, float gamma, const Vec2f& vert1, const Vec2f& vert2, const Vec2f& vert3, float weight) {
    auto u = (alpha * vert1[0] + beta * vert2[0] + gamma * vert3[0]);
    auto v = (alpha * vert1[1] + beta * vert2[1] + gamma * vert3[1]);

    u /= weight;
    v /= weight;

    return Vec2f(u, v);
}

void Rasterization::rasterize_triangle(const Rasterizer_Triangle& t, const std::array<Vec3f, 3>& view_pos) {
    int min_x = static_cast<int>(floor(min(t.v[0][0], min(t.v[1][0], t.v[2][0]))));
    int min_y = static_cast<int>(floor(min(t.v[0][1], min(t.v[1][1], t.v[2][1]))));
    int max_x = static_cast<int>(ceil(max(t.v[0][0], max(t.v[1][0], t.v[2][0]))));
    int max_y = static_cast<int>(ceil(max(t.v[0][1], max(t.v[1][1], t.v[2][1]))));

    int MSAA = 4;
    std::vector<Vec2f> bias{
        {0.25,0.25},                //左下
        {0.75,0.25},                //右下
        {0.25,0.75},                //左上
        {0.75,0.75}                 //右上
    };

    for (int i = min_x; i <= max_x; ++i) {
        for (int j = min_y; j <= max_y; ++j) {
            int count = 0;
            for (int k = 0; k < MSAA; ++k) {
                if (insideTriangle(static_cast<float>(i + bias[k][0]), static_cast<float>(j + bias[k][1]), t.v)) ++count;
            }

            if (count) {
                auto [alpha, beta, gamma] = computeBarycentric2D(i + 0.5, j + 0.5, t.v);
                float Z = 1.0 / (alpha / t.v[0].getW() + beta / t.v[1].getW() + gamma / t.v[2].getW());
                float zp = alpha * t.v[0].getW() / t.v[0].getW() + beta * t.v[1].getW() / t.v[1].getW() + gamma * t.v[2].getW() / t.v[2].getW();
                zp *= Z;
                //std::cout << alpha << " " << beta << " " << gamma <<  " " << Z << " " << zp << std::endl;
                if (zp < depth_buf[get_index(i, j)]) {
                    depth_buf[get_index(i, j)] = zp;
                    //std::cout << alpha << " * " << beta << " * " << gamma << " * " << t.color[0] << " " << t.color[1] << " " << t.color[2] << std::endl;
                    auto interpolated_color = interpolate(alpha, beta, gamma, t.color[0], t.color[1], t.color[2], 1.0f);
                    auto interpolated_normal = interpolate(alpha, beta, gamma, t.normal[0], t.normal[1], t.normal[2], 1.0f);
                    auto interpolated_texcoords = interpolate(alpha, beta, gamma, t.tex_coords[0], t.tex_coords[1], t.tex_coords[2], 1.0f);
                    auto interpolated_shadingcoords = interpolate(alpha, beta, gamma, view_pos[0], view_pos[1], view_pos[2], 1.0f);
                    //std::cout << interpolated_normal << std::endl;
                    Fragment_Shader_Payload payload(interpolated_color, normalize(interpolated_normal), interpolated_texcoords, texture ? &*texture : nullptr);
                    payload.view_pos = interpolated_shadingcoords;
                    //std::cout << "^^^" << std::endl;
                    auto pixel_color = fragment_shader(payload);
                    //std::cout << i << " " << j << " " << pixel_color << std::endl;
                    set_pixel(Vec2i(i, j), pixel_color * (count / 4.f));
                }
            }
        }
    }
}


void Rasterization::set_model(const Mat4f& m) {
    model = m;
}

void Rasterization::set_view(const Mat4f& v) {
    view = v;
}

void Rasterization::set_projection(const Mat4f& p) {
    projection = p;
}

void Rasterization::clear(Buffers buff) {
    if ((buff & Buffers::Color) == Buffers::Color) {
        std::fill(frame_buf.begin(), frame_buf.end(), Vec3f(0, 0, 0));
    }
    if ((buff & Buffers::Depth) == Buffers::Depth) {
        std::fill(depth_buf.begin(), depth_buf.end(), Infinity);
    }
}

Rasterization::Rasterization(const int& w, const int& h,
                             std::function<Vec3f(Vertex_Shader_Payload)>& vert_shader, 
                             std::function<Vec3f(Fragment_Shader_Payload)>& frag_shader)
    : width(w), height(h), vertex_shader(vert_shader), fragment_shader(frag_shader) {
    
    frame_buf.resize(w * h);
    depth_buf.resize(w * h);

    texture = std::nullopt;
}

int Rasterization::get_index(int x, int y) {
    return (height - y) * width + x;
}

void Rasterization::set_pixel(const Vec2i& point, const Vec3f& color) {
    int ind = (height - point.getV()) * width + point.getU();
    frame_buf[ind] = color;
}

void Rasterization::set_vertex_shader(std::function<Vec3f(Vertex_Shader_Payload)> vert_shader) {
    vertex_shader = vert_shader;
}

void Rasterization::set_fragment_shader(std::function<Vec3f(Fragment_Shader_Payload)> frag_shader) {
    fragment_shader = frag_shader;
}
void Rasterization::Render(std::vector<Rasterizer_Triangle*>& TriangleList) {
    std::string filename = "output.png";
    std::string obj_path = "C:/Users/guo/Downloads/learning/ray_tracing/SimpleRenderer/models/spot/";

    std::string texture_path = "hmap.jpg";
    set_texture(Rasterizer_Texture(obj_path + texture_path));

    Vec3f eye_pos(0, 0, 10);

    clear(Buffers::Color | Buffers::Depth);

    set_model(rotate4Y(140.0f) * scale4(2.5f, 2.5f, 2.5f));
    set_view(translate4(-eye_pos));
    set_projection(perspective(degrees_to_radians(45.0f), 1.0f, 0.1f, 50.0f));

    auto start = std::chrono::system_clock::now();
    draw(TriangleList);
    auto stop = std::chrono::system_clock::now();

    cv::Mat image(700, 700, CV_32FC3, frame_buffer().data());
    image.convertTo(image, CV_8UC3, 1.f);
    cv::cvtColor(image, image, cv::COLOR_RGB2BGR);

    cv::imshow("image", image);

    std::cout << "Rasterization complete: \n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";
}