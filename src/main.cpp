#include "main.hpp"

void create_triangleist(std::vector<Rasterizer_Triangle*>& TriangleList, const std::string& obj_name) {
	objl::Loader Loader;

	bool loadout = Loader.LoadFile(obj_name);
	if (!loadout) std::cout << "读取obj失败" << std::endl;

	for (auto mesh : Loader.LoadedMeshes) {
		for (int i = 0; i < mesh.Vertices.size(); i += 3) {
			Rasterizer_Triangle* t = new Rasterizer_Triangle();
			for (int j = 0; j < 3; ++j) {
				t->setVertex(j, Vec4f(mesh.Vertices[i + j].Position.X, mesh.Vertices[i + j].Position.Y, mesh.Vertices[i + j].Position.Z, 1.0));
				t->setNormal(j, Vec3f(mesh.Vertices[i + j].Normal.X, mesh.Vertices[i + j].Normal.Y, mesh.Vertices[i + j].Normal.Z));
				t->setTexCoord(j, Vec2f(mesh.Vertices[i + j].TextureCoordinate.X, mesh.Vertices[i + j].TextureCoordinate.Y));
			}
			TriangleList.push_back(t);
		}
	}
}

void on_mouse(int event, int x, int y, int flags, void* userdata) {
	switch (event) {
	case cv::EVENT_FLAG_LBUTTON:
		if (state == 0) {
			if (x > btn01.x && x < btn01.x + btn01.width && y > btn01.y && y < btn01.y + btn01.height) {
				Image = DefaultMat.clone();
				btn01 = drawButton(Image, btn_name4, cv::Point(b, b), 0);
				btn02 = drawButton(Image, btn_name5, cv::Point(btn01.x, btn01.height + b), btn01.width);
				btn03 = drawButton(Image, btn_name6, cv::Point(btn01.x, btn02.height + btn02.y), btn01.width);
				btn04 = drawButton(Image, btn_name7, cv::Point(btn01.x, btn03.height + btn03.y), btn01.width);
				btn05 = drawButton(Image, btn_name8, cv::Point(btn01.x, btn04.height + btn04.y), btn01.width);
				imshow(WINDOW_NAME, Image);
				state = Rasterizer_Type;
			}

			if (x > btn02.x && x < btn02.x + btn02.width && y > btn02.y && y < btn02.y + btn02.height) {
				//drawString(g_srcImage2, str, Point(20, -20), Scalar(123, 21, 211), 0.55f, 1, 3);
				auto world = final_scene();
				Color background(0.7f, 0.8f, 1.0f);
				RayTracing r;
				auto start = std::chrono::system_clock::now();
				r.Render(background, world, cam);
				auto stop = std::chrono::system_clock::now();
				std::cout << "Ray Tracing complete: \n";
				std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
				std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
				std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";
			}

			if (x > btn03.x && x < btn03.x + btn03.width && y > btn03.y && y < btn03.y + btn03.height) {
				auto world = random_scene();
				Color background(0, 0, 0);
				PathTracing r;
				auto start = std::chrono::system_clock::now();
				r.Render(Image, background, world, cam);
				auto stop = std::chrono::system_clock::now();
				std::cout << "Path Tracing complete: \n";
				std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
				std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
				std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";
			}
		}
		else if (state == 1) {
			std::vector<Rasterizer_Triangle*> TriangleList;
			std::string obj_name = "C:/Users/guo/Downloads/learning/ray_tracing/SimpleRenderer/models/spot/spot_triangulated_good.obj";
			create_triangleist(TriangleList, obj_name);
		
			std::function<Vec3f(Vertex_Shader_Payload)> vertex_shader;			
			std::function<Vec3f(Fragment_Shader_Payload)> active_shader;
			
			if (x > btn01.x && x < btn01.x + btn01.width && y > btn01.y && y < btn01.y + btn01.height) {
				Vertex_Shader v;
				vertex_shader = std::bind(&Vertex_Shader::value, &v, std::placeholders::_1);
				Blinn_Phong_Fragment_Shader f;
				active_shader = std::bind(&Fragment_Shader::value, &f, std::placeholders::_1);
			}
			if (x > btn02.x && x < btn02.x + btn02.width && y > btn02.y && y < btn02.y + btn02.height) {
				Vertex_Shader v;
				vertex_shader = std::bind(&Vertex_Shader::value, &v, std::placeholders::_1);
				Normal_Fragment_Shader f;
				active_shader = std::bind(&Fragment_Shader::value, &f, std::placeholders::_1);
			}
			if (x > btn03.x && x < btn03.x + btn03.width && y > btn03.y && y < btn03.y + btn03.height) {
				Vertex_Shader v;
				vertex_shader = std::bind(&Vertex_Shader::value, &v, std::placeholders::_1);
				Texture_Fragment_Shader f;
				active_shader = std::bind(&Fragment_Shader::value, &f, std::placeholders::_1);
			}
			if (x > btn04.x && x < btn04.x + btn04.width && y > btn04.y && y < btn04.y + btn04.height) {
				Vertex_Shader v;
				vertex_shader = std::bind(&Vertex_Shader::value, &v, std::placeholders::_1);
				Bump_Fragment_Shader f;
				active_shader = std::bind(&Fragment_Shader::value, &f, std::placeholders::_1);
			}
			if (x > btn05.x && x < btn05.x + btn05.width && y > btn05.y && y < btn05.y + btn05.height) {
				Vertex_Shader v;
				vertex_shader = std::bind(&Vertex_Shader::value, &v, std::placeholders::_1);
				Displacement_Fragment_Shader f;
				active_shader = std::bind(&Fragment_Shader::value, &f, std::placeholders::_1);
			}
			Rasterization r(700, 700, vertex_shader, active_shader);
			r.Render(TriangleList);
		}

		break;

	case cv::EVENT_FLAG_RBUTTON:
		if (state == 1 || state == 2 || state == 3) {
			Image = DefaultMat.clone();
			btn01 = drawButton(Image, btn_name1, cv::Point(b, b), 0);
			btn02 = drawButton(Image, btn_name2, cv::Point(btn01.x, btn01.height + b), btn01.width);
			btn03 = drawButton(Image, btn_name3, cv::Point(btn01.x, btn02.height + btn02.y), btn01.width);
			imshow(WINDOW_NAME, Image);
			cv::destroyWindow("image"); 
			state = Init;
		}

	default:
		break;
	}
}


int main(int argc, char** argv) {
	////设置滑动条初始值为70
	//g_nAlphaValueSlider = 70;

	//创建窗体
	cv::namedWindow(WINDOW_NAME, cv::WINDOW_NORMAL);
	btn01 = drawButton(Image, btn_name1, cv::Point(b, b), 0);
	btn02 = drawButton(Image, btn_name2, cv::Point(btn01.x, btn01.height + b), btn01.width);
	btn03 = drawButton(Image, btn_name3, cv::Point(btn01.x, btn02.height + btn02.y), btn01.width);
	imshow(WINDOW_NAME, Image);

	int key = 0;
	while (key != 27) {
		cv::setMouseCallback(WINDOW_NAME, on_mouse);
		key = cv::waitKey(5);
	}
	return 0;
}