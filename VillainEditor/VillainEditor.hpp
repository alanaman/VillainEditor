#include "logging.hpp"
#include "window/window.hpp"
#include "gui/gui_layer.hpp"

namespace villain {

class Editor
{
 WindowProperties window_properties;
 Window* window;
 GuiLayer* gui;
 Scene scene;
public:
 Editor();
 ~Editor();

 void run();
};


}