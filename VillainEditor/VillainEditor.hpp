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

 static Editor* m_instance;
public:
 Editor();
 ~Editor();

 static Editor* getEditorInstance();
 void run();

 void dispatchEvent(Event& e);
 void onResizeEvent(int width, int height);
 void onSceneReload();

 Scene* getScene() { return &scene; };
 //void startPlay();
 //void stopPlay();
};


}