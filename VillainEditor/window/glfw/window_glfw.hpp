#pragma once
#include "window.hpp"

namespace villain {
class WindowGLFW : public Window
{
private:
  GLFWwindow* window;

  std::string m_name;
  int m_width, m_height;
public:
  WindowGLFW(const WindowProperties& props);

};
}