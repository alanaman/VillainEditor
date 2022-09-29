# CMakeList.txt : CMake project for VillainEditor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "VillainEditor.cpp" "VillainEditor.hpp" "window.hpp"  "window/glfw/window_glfw.hpp" "window/glfw/window_glfw.cpp")

target_include_directories(${PROJECT_NAME}
	PUBLIC .)


target_link_libraries(${PROJECT_NAME} glfw)
# TODO: Add tests and install targets if needed.
