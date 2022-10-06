#pragma once
#include "window/window.hpp"
#include "context.hpp"

namespace villain {
class WindowGLFW : public Window
{
private:
  GLFWwindow* m_window;
  GraphicsContext* m_context;

  std::string m_name;
  int m_width, m_height;


public:
  WindowGLFW(const WindowProperties& props);

};
}