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
	"scene/entity.cpp"
	"scene/collection.cpp"
	"scene/actor.cpp"
	"game/gunner.cpp"
 "scene/static_mesh.cpp")

add_subdirectory(
	"graphics"
)

target_include_directories(
	${PROJECT_NAME}
	PUBLIC "./scene"
	PUBLIC "./game"
	#PUBLIC "."
	PUBLIC "../external/glfw/include"
	PUBLIC "../external/nativefiledialog-extended/src/include"
	PUBLIC "../external/assimp/include"
	PUBLIC "../external/glm"
	PUBLIC "../external/imgui"
	PUBLIC "../external"
	PUBLIC "../shared"
)

target_link_libraries(${PROJECT_NAME} glfw VillainGraphics ImGUI nfd)
# TODO: Add tests and install targets if needed.
