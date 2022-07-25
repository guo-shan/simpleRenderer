#ifndef RASTERIZER_TEXTURE_HPP
#define RASTERIZER_TEXTURE_HPP

#include "Math/Vec.h"
#include <opencv2/opencv.hpp>

class Rasterizer_Texture {
private:
    cv::Mat image_data;

public:
    Rasterizer_Texture(const std::string& name) {
        image_data = cv::imread(name);
        cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
        width = image_data.cols;
        height = image_data.rows;
    }

    int width, height;

    Vec3f getColor(float u, float v) {
        u = fmin(1, fmax(u, 0));
        v = fmin(1, fmax(v, 0));
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Vec3f(color[0], color[1], color[2]);
    }

};
#endif // !RASTERIZER_TEXTURE_HPP
