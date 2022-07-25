#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

#include "Math/Vec.h"
#include "Core/Camera.h"
#include "Renderer/Rasterization.hpp"
#include "Renderer/RayTracing.hpp"
#include "Renderer/PathTracing.hpp"
#include "World/World.h"
#include "Shader/Blinn_Shader.hpp"
#include "Shader/Bump_Shader.hpp"
#include "Shader/Displacement_Shader.hpp"
#include "Shader/Normal_Shader.hpp"
#include "Shader/Texture_Shader.hpp"
#include "Core/OBJ_Loader.hpp"

#define WINDOW_NAME "DefaultWindow" //为窗口标题定义的宏

const int g_nManAlphaValue = 100; //Alpha值的最大值
int g_nAlphaValueSlider;//滑动条对应的变量
float g_dAlphaValue;
float g_dBetaValue;

enum State {
	Init,
	Rasterizer_Type,
	RayTracing_Type,
	PathTracing_Type
};

State state = Init;
//声明存储图像的变量
const cv::Mat DefaultMat = cv::imread("C:/Users/guo/Downloads/learning/ray_tracing/SimpleRenderer/images/menu.jpg");
cv::Mat Image = cv::imread("C:/Users/guo/Downloads/learning/ray_tracing/SimpleRenderer/images/menu.jpg");
// 初始界面参数
const int b = image_width * 0.02;
std::string str1 = "rasterization";
std::string str2 = "ray tracing";
std::string str3 = "path tracing";
std::string btn_name1 = "rasterization";
std::string btn_name2 = "ray tracing";
std::string btn_name3 = "path tracing";
std::string btn_name4 = "Blinn Phong Shader";
std::string btn_name5 = "Normal Map";
std::string btn_name6 = "Texture Map";
std::string btn_name7 = "Bump Map";
std::string btn_name8 = "Displacement Map";
cv::Rect btn01;
cv::Rect btn02;
cv::Rect btn03;
cv::Rect btn04;
cv::Rect btn05;

// 相机参数
//Point3f lookfrom(478, 278, -600);
//Point3f lookat(278, 278, 0);
//float vfov = 40.f;
//Vec3f vup(0.f, 1.f, 0.f);
//float dist_to_focus = 10.f;
//float aperture = 0.0f;

Point3f lookfrom = Point3f(13, 2, 3);
Point3f lookat = Point3f(0, 0, 0);
float vfov = 20.0;
float aperture = 0.1;
Vec3f vup(0, 1, 0);
float dist_to_focus = 10.f;

Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.f, 1.f);

cv::Rect drawString(cv::Mat& img, std::string text, cv::Point coord, cv::Scalar color, float fontScale = 1.0f, int thickness = 1, int fontFace = cv::FONT_HERSHEY_COMPLEX) {
	//获取文本大小和基线 
	int baseline = 0;
	cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;
	// 为左/右或上/下调整校正坐标
	if (coord.y >= 0) {
		//图像左上角的文本的左上角的坐标，因此按行向下移动
		coord.y += textSize.height;
	}
	else {
		//图像左下角的文本的左下角的坐标，因此从底部上来
		coord.y += img.rows - baseline + 1;
	}
	// 如果希望变成右侧调整
	if (coord.x < 0) {
		coord.x += img.cols - textSize.width + 1;
	}

	// 获取文本的边界矩形
	cv::Rect boundingRect = cv::Rect(coord.x, coord.y - textSize.height, textSize.width, baseline + textSize.height);

	// 画出平滑的文本
	putText(img, text, coord, fontFace, fontScale, color, thickness, cv::LINE_AA);

	// 文本大小
	return boundingRect;
}

cv::Rect drawButton(cv::Mat& img, std::string text, cv::Point coord, int minWidth = 0) {
	int B = image_width * 0.02;
	cv::Point textCoord = cv::Point(coord.x + B, coord.y + B);
	// 获取文本边界矩形
	cv::Rect rcText = drawString(img, text, textCoord, CV_RGB(0, 0, 0));
	// 在文本周围画一个填充的矩形
	cv::Rect rcButton = cv::Rect(rcText.x - B, rcText.y - B, rcText.width + 2 * B, rcText.height + 2 * B);
	// 设置按钮的最小宽度
	if (rcButton.width < minWidth)
		rcButton.width = minWidth;
	// 创建一个半透膜的白色矩形
	cv::Mat matButton = img(rcButton);
	matButton += CV_RGB(90, 90, 90);
	//画一个非透明的白色边界 
	rectangle(img, rcButton, CV_RGB(200, 200, 200), 1, cv::LINE_AA);

	//使用抗锯齿，画一个实际用来显示的文本
	drawString(img, text, textCoord, CV_RGB(10, 55, 20));

	return rcButton;
}

#endif // !MAIN_HPP
