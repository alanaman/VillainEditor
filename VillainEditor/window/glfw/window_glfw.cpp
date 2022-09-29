#pragma once
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
  {
    ERROR("glfw initialization failed (might be reinitialization)");
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    ERROR("failed to create window");
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    //glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
}
}



