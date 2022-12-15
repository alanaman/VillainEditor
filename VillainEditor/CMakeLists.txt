# CMakeList.txt : CMake project for VillainEditor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Add source to this project's executable.
add_executable (${PROJECT_NAME}
	"main.cpp"
	
	"VillainEditor.cpp"
	
	"window/glfw/window_glfw.cpp"
	"window/nfd/nativefiledialog.cpp"
	
	"scene/scene.cpp"
	"scene/camera.cpp"
	"scene/static_mesh.cpp" 
	
	"gui/gui_layer.cpp"
	"gui/outliner.cpp"
	"gui/assetlib.cpp" 
	"gui/control_bar.cpp" 
	
	"scene/properties.cpp"
	"scene/transform.cpp"
	"scene/entity.cpp"
	"scene/collection.cpp"
	"scene/actor.cpp"
	
	"game/gunner.cpp"
	
	"asset_library/meshlibrary.cpp"
)

 set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
 set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)


add_subdirectory(
	"graphics"
)

target_include_directories(
	${PROJECT_NAME}
	PUBLIC "./scene"
	PUBLIC "./game"
	PUBLIC "./asset_library"
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
