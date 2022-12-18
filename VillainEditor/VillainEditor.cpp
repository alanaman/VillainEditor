// VillainEditor.cpp : Defines the entry point for the application.
#include "VillainEditor.hpp"


namespace villain {

Editor* Editor::m_instance = NULL;

Editor::Editor()
 :
 window_properties("Editor", 1080, 720),
 window(Window::create(window_properties)),
 scene("Scene", 1080, 720)
{

 m_instance = this;
 
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

Editor* Editor::getEditorInstance()
{
 return m_instance;
}

void Editor::dispatchEvent(Event& e)
{
 switch (e.getEventType())
 {
 case EventType::KeyPress:
 {
  e.is_handled = true;
  KeyPressEvent* ke = (KeyPressEvent*)&e;
  int key = ke->key;
  if (key == KEY::A && (e.mods & MOD::SHIFT))
   MeshLibrary::createMeshFromFile();
  break;
 }
 default:
  e.is_handled = false;
  break;
 }
 scene.eventHandler(e);
}

void Editor::onResizeEvent(int width, int height)
{
 scene.onResizeEvent(width, height);
}

void Editor::onSceneReload()
{
 gui->onSceneReload();
}

Editor::~Editor()
{
	window->terminate();
}


}
