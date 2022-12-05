cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (ImGUI
	"imgui.cpp"
	"imgui_demo.cpp"
	"imgui_draw.cpp"
	"imgui_tables.cpp"
	"imgui_widgets.cpp"
	"imgui_impl_glfw.cpp"
	"imgui_impl_opengl3.cpp"
	)

target_include_directories(ImGUI
	PUBLIC "../glfw/include"
	)

# target_link_libraries(VillainGraphics glad assimp)

# TODO: Add tests and install targets if needed.