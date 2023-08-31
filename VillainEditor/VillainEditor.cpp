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



 //auto bullet_inst = my_imp.createActor("bullet");
 //Properties p;
 //bullet_inst->collectProperties(p);

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

#define VILLAIN_AUTO_LOAD_FILE
#ifndef VILLAIN_AUTO_LOAD_FILE
 while (!window->shouldClose())
 {
  gui->renderSelector();
  window->update();
  if (m_projectName != "")
   break;
 }
#else
 std::ifstream infile;
 infile.open("most_recent_project.txt", std::ios::in);
 std::string projectFile;
 if (infile.is_open()) {
  std::getline(infile, projectFile);
  infile.close();
 }
 std::filesystem::path filepath(projectFile); 
 if (std::filesystem::directory_entry(filepath).exists())
 {
  m_projectFolder = filepath.parent_path().string();
  m_projectName = filepath.stem().string();
 }
 else
 {
  while (!window->shouldClose())
  {
   gui->renderSelector();
   window->update();
   if (m_projectName != "")
    break;
  }
 }
#endif
 gui->setProjectDirectory(m_projectFolder);
 //TODO create dll before loading
 ASSERT(m_dllImporter.load(m_projectFolder));
 setDllFunctionPointers();
 run();
}

void Editor::setDllFunctionPointers()
{
 FunctionHandoverInterface funcHander(m_dllImporter.getEditorRep());

 funcHander.set_getMeshIdFP(MeshLibrary::getId);
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

 m_projectFolder = filepath.parent_path().string();
 m_projectName = filepath.stem().string();

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
   VLLN_ERR("Failed to create directory: " << folder);
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

 m_projectFolder = filepath.string();
 m_projectName = projectName;

 std::ofstream outFile;
 outFile.open(projFile, std::ios::out);
}

Editor::~Editor()
{
	window->terminate();
}


}
