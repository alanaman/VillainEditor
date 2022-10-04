// VillainEditor.cpp : Defines the entry point for the application.
//

#include "VillainEditor.hpp"
#include "window/window.hpp"
#include "graphics/shader.hpp"
#include <memory>

using namespace villain;
int main()
{
	WindowProperties props("Editor", 1080, 720);
	Window* window = Window::create(props);

	auto shader = Shader::create(
		"resources/shaders/basic_vertex.glsl",
		"resources/shaders/basic_fragment.glsl");

	return 0;
}
