#pragma once
#include "window/window.hpp"
#include "context.hpp"

namespace villain {
class WindowGLFW : public Window
{
private:
  GLFWwindow* m_window;
  GraphicsContext* m_context;




public:
  WindowGLFW(const WindowProperties& props);
  bool shouldClose() const;
  void update() const;
  void terminate() const;
};
}