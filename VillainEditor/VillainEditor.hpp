#pragma once

#include "logging.hpp"
#include "scene/scene.hpp"
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

 std::string mProjectName;
 std::string mProjectFolder;

 static Editor* m_instance;

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