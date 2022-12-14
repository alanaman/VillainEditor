// VillainEditor.cpp : Defines the entry point for the application.
#include "VillainEditor.hpp"


namespace villain {

Editor::Editor()
 :
 window_properties("Editor", 1080, 720),
 window(Window::create(window_properties)),
 scene("Scene", 1080, 720)
{
 MeshLibrary::init();
 gui = new GuiLayer(window->getWindowPointer());

	window->attachScene(scene);
	gui->attachScene(&scene);

}

 //scene.loadScene();
void Editor::run()
{
	while (!window->shouldClose())
	{
		scene.updateOnFrame();
  gui->render();
		window->update();
	}
}

Editor::~Editor()
{
	window->terminate();
}


}
