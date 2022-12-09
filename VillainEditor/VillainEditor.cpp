// VillainEditor.cpp : Defines the entry point for the application.
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
	gui.attachScene(&scene);
 scene.loadScene();

	while (!window->shouldClose())
	{
		scene.updateOnFrame();
  gui.render();
		window->update();
	}
	window->terminate();

	return 0;
}
