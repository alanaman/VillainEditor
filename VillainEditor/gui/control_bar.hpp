#include <imgui.h>

#include "scene.hpp"

namespace villain {

class ControlBar
{
 Scene*& m_scene;


public:
 ControlBar(Scene*& scene);

 void render();
};

}