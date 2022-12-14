# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

project (VillainEditor)

# Include sub-projects.
add_subdirectory("external/glfw")
add_subdirectory("external/assimp")
add_subdirectory("external/imgui")
add_subdirectory("external/nativefiledialog-extended")

#include_directories("out/build/x64-Debug/external/assimp/include")

add_subdirectory ("VillainEditor")


add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${PROJECT_BINARY_DIR}/VillainEditor/resources
        COMMENT "Copying resources into binary directory")

add_dependencies(VillainEditor copy_resources)