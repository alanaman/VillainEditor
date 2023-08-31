#pragma once

#include "logging.hpp"
#include "scene/scene.hpp"

// INFO: if <glfw3.h>(in gui_layer.hpp) is included before
// <Windows.h>(in dll_importer.hpp), APIENTRY redefinition 
// warning will appear
#include "game/dll_importer.hpp"
#include "window/window.hpp"


#include "gui/gui_layer.hpp"

#include "asset_library/material_library.hpp"


namespace villain {

class Editor
{
 WindowProperties window_properties;
 Window* window;
 GuiLayer* gui;
 Scene scene;

 std::string m_projectName;
 std::string m_projectFolder;
 
 DllImporter m_dllImporter;

 static Editor* m_instance;

 void setDllFunctionPointers();

public:
 Editor();
 ~Editor();

 static Editor* getEditorInstance();
 void run();
 void runProjectSelector();

 void dispatchEvent(Event& e);
 void onResizeEvent(int width, int height);
 void onSceneReload();
 void onSave();
 void onLoad();

 void selectProject();
 void createNewProject(std::string projectName);


 Scene* getScene() { return &scene; };
 //void startPlay();
 //void stopPlay();
};


}