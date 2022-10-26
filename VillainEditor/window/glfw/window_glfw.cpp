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

 glfwSetWindowUserPointer(m_window, &m_scene);

 //TODO: glfwSetErrorCallback();
 glfwSetWindowCloseCallback(m_window, closeCallback);
 glfwSetWindowSizeCallback(m_window, sizeCallback);
 glfwSetKeyCallback(m_window, keyCallback);
 glfwSetCharCallback(m_window, charCallback);
 glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
 glfwSetCursorPosCallback(m_window, cursorPosCallback);
 glfwSetScrollCallback(m_window, scrollCallback);
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

void WindowGLFW::closeCallback(GLFWwindow* window)
{
 Scene* scene = *(Scene**)glfwGetWindowUserPointer(window);
 //TODO
 INFO("window closing");
}

void WindowGLFW::sizeCallback(GLFWwindow* window, int width, int height)
{
 Scene* scene = *(Scene**)glfwGetWindowUserPointer(window);
 //TODO
 INFO("window resize:- width: " << width << ", height:" << height);
}

void WindowGLFW::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
 Scene* scene = *(Scene**)glfwGetWindowUserPointer(window);
 INFO(
  "key input:- key: " << key
  << ", scancode:" << scancode
  << ", action:" << action
  << ", mods:" << mods);

 //TODO
}

void WindowGLFW::charCallback(GLFWwindow* window, unsigned int codepoint)
{
 Scene* scene = *(Scene**)glfwGetWindowUserPointer(window);
 //TODO
}

void WindowGLFW::mouseButtonCallback(GLFWwindow* window, int button, int action, int mod)
{
 Scene* scene = *(Scene**)glfwGetWindowUserPointer(window);
 //TODO
}

void WindowGLFW::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
 Scene* scene = *(Scene**)glfwGetWindowUserPointer(window);
 //TODO
}

void WindowGLFW::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
 Scene* scene = *(Scene**)glfwGetWindowUserPointer(window);
 //TODO
}


}



