# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("VillainEditor")

# Include sub-projects.
add_subdirectory("external/glfw")
add_subdirectory("external/assimp")
add_subdirectory ("VillainEditor")

target_include_directories(${PROJECT_NAME}
	PUBLIC "."
	PUBLIC "external/glfw/include"
	PUBLIC "external/assimp/include"
	PUBLIC "external/glm/glm"
	PUBLIC "shared"
	)
