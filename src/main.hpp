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

#define WINDOW_NAME "DefaultWindow" //Ϊ���ڱ��ⶨ��ĺ�

const int g_nManAlphaValue = 100; //Alphaֵ�����ֵ
int g_nAlphaValueSlider;//��������Ӧ�ı���
float g_dAlphaValue;
float g_dBetaValue;

enum State {
	Init,
	Rasterizer_Type,
	RayTracing_Type,
	PathTracing_Type
};

State state = Init;
//�����洢ͼ��ı���
const cv::Mat DefaultMat = cv::imread("C:/Users/guo/Downloads/learning/ray_tracing/SimpleRenderer/images/menu.jpg");
cv::Mat Image = cv::imread("C:/Users/guo/Downloads/learning/ray_tracing/SimpleRenderer/images/menu.jpg");
// ��ʼ�������
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

// �������
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
	//��ȡ�ı���С�ͻ��� 
	int baseline = 0;
	cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;
	// Ϊ��/�һ���/�µ���У������
	if (coord.y >= 0) {
		//ͼ�����Ͻǵ��ı������Ͻǵ����꣬��˰��������ƶ�
		coord.y += textSize.height;
	}
	else {
		//ͼ�����½ǵ��ı������½ǵ����꣬��˴ӵײ�����
		coord.y += img.rows - baseline + 1;
	}
	// ���ϣ������Ҳ����
	if (coord.x < 0) {
		coord.x += img.cols - textSize.width + 1;
	}

	// ��ȡ�ı��ı߽����
	cv::Rect boundingRect = cv::Rect(coord.x, coord.y - textSize.height, textSize.width, baseline + textSize.height);

	// ����ƽ�����ı�
	putText(img, text, coord, fontFace, fontScale, color, thickness, cv::LINE_AA);

	// �ı���С
	return boundingRect;
}

cv::Rect drawButton(cv::Mat& img, std::string text, cv::Point coord, int minWidth = 0) {
	int B = image_width * 0.02;
	cv::Point textCoord = cv::Point(coord.x + B, coord.y + B);
	// ��ȡ�ı��߽����
	cv::Rect rcText = drawString(img, text, textCoord, CV_RGB(0, 0, 0));
	// ���ı���Χ��һ�����ľ���
	cv::Rect rcButton = cv::Rect(rcText.x - B, rcText.y - B, rcText.width + 2 * B, rcText.height + 2 * B);
	// ���ð�ť����С���
	if (rcButton.width < minWidth)
		rcButton.width = minWidth;
	// ����һ����͸Ĥ�İ�ɫ����
	cv::Mat matButton = img(rcButton);
	matButton += CV_RGB(90, 90, 90);
	//��һ����͸���İ�ɫ�߽� 
	rectangle(img, rcButton, CV_RGB(200, 200, 200), 1, cv::LINE_AA);

	//ʹ�ÿ���ݣ���һ��ʵ��������ʾ���ı�
	drawString(img, text, textCoord, CV_RGB(10, 55, 20));

	return rcButton;
}

#endif // !MAIN_HPP
