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
  bool shouldClose() const override;
  void update() const override;
  void terminate() const override;
  int getKeyStatus(int key) const override;
  void* getWindowPointer() const override;

  
  static void closeCallback(GLFWwindow* window);
  static void resizeCallback(GLFWwindow* window, int width, int height);
  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void charCallback(GLFWwindow* window, unsigned int codepoint);
  static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mod);
  static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
  static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

};
}