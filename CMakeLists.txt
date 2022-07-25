cmake_minimum_required (VERSION 3.8)

project ("simpleRenderer")

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

FILE(GLOB simpleRenderer_SOURCE_FILES
	"src/main.cpp"
	"src/Core/stb_image.cpp"
	"src/Math/Matrix.cpp"
	"src/Renderer/Rasterization.cpp"
)

add_executable(simpleRenderer ${simpleRenderer_SOURCE_FILES} )
target_include_directories(simpleRenderer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(simpleRenderer PRIVATE ${OpenCV_LIBRARIES})        