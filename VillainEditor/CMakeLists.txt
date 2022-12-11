# CMakeList.txt : CMake project for VillainEditor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (${PROJECT_NAME}
	"VillainEditor.cpp"
	"window/glfw/window_glfw.cpp"
	"window/nfd/nativefiledialog.cpp"
	"scene/scene.cpp"
	"scene/camera.cpp"
	"gui/gui_layer.cpp"
	"gui/outliner.cpp"
	"scene/properties.cpp"
	"scene/transform.cpp"
 "scene/entity.cpp")

add_subdirectory(
	"graphics"
)

target_include_directories(
	${PROJECT_NAME}
	PUBLIC "./scene"
)

target_link_libraries(${PROJECT_NAME} glfw VillainGraphics ImGUI nfd)
# TODO: Add tests and install targets if needed.
