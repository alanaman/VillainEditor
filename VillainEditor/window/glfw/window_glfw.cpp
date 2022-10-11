#pragma once
#include <GLFW/glfw3.h>
#include "window_glfw.hpp"
#include "logging.hpp"
#include "opengl/context_opengl.hpp"


namespace villain {

Window* Window::create(const WindowProperties& props)
{
  return new WindowGLFW(props);
}

WindowGLFW::WindowGLFW(const WindowProperties& props)
{
 m_name = props.name;
 m_width = props.width;
 m_height = props.height;

 if (!glfwInit())
   ERROR("glfw initialization failed (might be reinitialization)");
 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

 m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);
 if (!m_window)
 {
   glfwTerminate();
   ERROR("failed to create m_window");
 }

 glfwMakeContextCurrent(m_window);
  
 m_context = new ContextOpengl();//TODO: fix this when adding other APIs
 m_context->initiate();
}

void WindowGLFW::update() const
{
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}

bool WindowGLFW::shouldClose() const
{
 return glfwWindowShouldClose(m_window);
}

void WindowGLFW::terminate() const
{
 glfwTerminate();
}

}



