#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "window_glfw.hpp"
#include "logging.hpp"


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

  window = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    ERROR("failed to create window");
  }

  glfwMakeContextCurrent(window);
  int version = gladLoadGL();
  if (!version)
  {
   ERROR("Could not initialize GLAD");
   exit(1);
  }

  while (!glfwWindowShouldClose(window))
  {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
}
}



