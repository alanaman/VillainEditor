#pragma once

#include "logging.hpp"
#include "scene.hpp"
#include "window/window.hpp"
#include "gui/gui_layer.hpp"

namespace villain {

class Editor
{
 WindowProperties window_properties;
 Window* window;
 GuiLayer* gui;
 Scene scene;

 static Editor* m_instance;
public:
 Editor();
 ~Editor();

 static Editor* getEditorInstance();
 void run();

 void dispatchEvent(Event& e);
 void onResizeEvent(int width, int height);
 void onSceneReload();

 //void startPlay();
 //void stopPlay();
};


}