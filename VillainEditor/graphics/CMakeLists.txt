cmake_minimum_required (VERSION 3.10)

# Add source to this project's executable.
add_library (VillainGraphics
	"opengl/shader_opengl.cpp"
	"opengl/context_opengl.cpp"
	"opengl/mesh_opengl.cpp"
	"renderer.cpp"	
)

add_subdirectory("opengl/libraries/GLAD")

target_include_directories(VillainGraphics PUBLIC
	"."
	"opengl/libraries/GLAD/include"
	"../../external/glm/glm"
	"../../external/assimp/include"
	"../../shared"
	"../."
	"../scene"
	)

target_link_libraries(VillainGraphics glad assimp)

# TODO: Add tests and install targets if needed.
