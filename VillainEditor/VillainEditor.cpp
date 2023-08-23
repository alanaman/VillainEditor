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
 MaterialLibrary::init();
 gui = new GuiLayer(window->getWindowPointer());

	//window->attachScene(scene);
	gui->attachScene(&scene);

}

 //scene.loadScene();
void Editor::run()
{
 window->setResizeable(true);
	while (!window->shouldClose())
	{
		scene.updateOnFrame(gui->getDeltaTime());
  gui->render();
		window->update();
	}
}


void Editor::runProjectSelector()
{
 window->setResizeable(false);
 while (!window->shouldClose())
 {
  gui->renderSelector();
  window->update();
  if (mProjectName != "")
   break;
 }
 gui->setProjectDirectory(mProjectFolder);
 run();

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
  else if (key == KEY::S && (e.mods & MOD::CONTROL))
   onSave();
  else if (key == KEY::L && (e.mods & MOD::CONTROL))
   onLoad();
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

void Editor::onSave()
{
 scene.saveScene();
 MaterialLibrary::onSave();

}

void Editor::onLoad()
{
 MaterialLibrary::onLoad();
 scene.loadScene();
}

void Editor::selectProject()
{
 auto file = FileBrowser::selectFile();
 if (file == "")
  return;
 std::filesystem::path filepath(file);

 if (filepath.extension().string() != ".vproject")
 {
  WARNING("Project file should have extionsion .vproject")
  return;
 }

 mProjectFolder = filepath.parent_path().string();
 mProjectName = filepath.stem().string();

}

void Editor::createNewProject(std::string projectName)
{
 if (projectName == "")
  return;
 auto folder = FileBrowser::selectDirectory();
 if (folder == "")
  return;
 std::filesystem::path filepath(folder);

 if (!std::filesystem::exists(folder))
 {
  if (!std::filesystem::create_directories(folder))
   ERROR("Failed to create directory: " << folder);
 }

 for (const auto& entry : std::filesystem::directory_iterator(folder))
 {
  WARNING("Non-empty project directory selected");
  break;
 }

 auto projFile = std::filesystem::path(folder) / std::filesystem::path(projectName + ".vproject");
 for (const auto& entry : std::filesystem::directory_iterator(folder))
 {
  if (entry.path() == projFile)
  {
   WARNING("Project with same name already exists");
   return;
  }
 }

 mProjectFolder = filepath.string();
 mProjectName = projectName;

 std::ofstream outFile;
 outFile.open(projFile, std::ios::out);
}

Editor::~Editor()
{
	window->terminate();
}


}
