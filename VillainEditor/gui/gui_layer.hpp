#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

#include "outliner.hpp"
#include "assetlib.hpp"
#include "control_bar.hpp"

namespace villain {

class GuiLayer
{
private:
 bool show_demo_window = true;
 bool show_another_window = false;
 bool show_properties_window = true;

 Scene* m_scene = NULL;

 Outliner m_outliner;
 AssetLibrary m_assetlib;
 ControlBar m_controlbar;

 ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

public:
 GuiLayer(void* window);
 ~GuiLayer();
 void attachScene(Scene *scene);
 void render();
 void onSceneReload();
 float getDeltaTime();

};
}