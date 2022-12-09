# CMakeList.txt : CMake project for VillainEditor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (${PROJECT_NAME}
	"VillainEditor.cpp"
	"window/glfw/window_glfw.cpp"
	"window/nfd/nativefiledialog.cpp"
	"scene.cpp"
	"camera.cpp"
	"gui/gui_layer.cpp"
	"properties.cpp"
	"transform.cpp"
)

add_subdirectory(
	"graphics"
)

target_link_libraries(${PROJECT_NAME} glfw VillainGraphics ImGUI nfd)
# TODO: Add tests and install targets if needed.
