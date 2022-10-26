// VillainEditor.cpp : Defines the entry point for the application.
//

#include "VillainEditor.hpp"
#include "window/window.hpp"
#include "graphics/shader.hpp"
#include "graphics/model.hpp"
#include "scene.hpp"
#include <memory>

using namespace villain;
int main()
{
	WindowProperties props("Editor", 1080, 720);
	Window* window = Window::create(props);

	Scene scene("Scene", 1080, 720);

	auto model = Model::create("cube", "resources/models/cube.fbx");
	model->setShader(Shader::create(
		"resources/shaders/basic_vertex2.glsl",
		"resources/shaders/basic_fragment2.glsl"));
	model->loadMeshes();

	scene.addModel(model);

	while (!window->shouldClose())
	{
		scene.render();
		window->update();
	}
	window->terminate();

	return 0;
}
