﻿// VillainEditor.cpp : Defines the entry point for the application.
#include "window/window.hpp"
#include "gui/gui_layer.hpp"

using namespace villain;
int main()
{
	WindowProperties props("Editor", 1080, 720);
	Window* window = Window::create(props);
 GuiLayer gui(window->getWindowPointer());

	Scene scene("Scene", 1080, 720);
	window->attachScene(scene);
	auto model = Model::create("cube", "resources/models/cube.fbx");
	model->setShader(Shader::create(
		"resources/shaders/basic_vertex2.glsl",
		"resources/shaders/basic_fragment2.glsl"));
	model->loadMeshes();

	scene.addModel(model);

	while (!window->shouldClose())
	{
		scene.render();
  gui.render();
		window->update();
	}
	window->terminate();

	return 0;
}
