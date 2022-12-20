#pragma once

#include <imgui/imgui.h>

#include "scene/scene.hpp"

namespace villain {

class ControlBar
{
 Scene*& m_scene;


public:
 ControlBar(Scene*& scene);

 void render();
};

}