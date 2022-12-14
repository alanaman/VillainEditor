#include "window_glfw.hpp"


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
  
 m_data.context = new ContextOpengl();//TODO: fix this when adding other APIs
 m_data.context->initiate();

 glfwSetWindowUserPointer(m_window, &m_data);

 Cursor& cursor = m_data.cursor;
 glfwGetCursorPos(m_window, &cursor.prev_xpos, &cursor.prev_ypos);

 //TODO: glfwSetErrorCallback();
 glfwSetWindowCloseCallback(m_window, closeCallback);
 glfwSetWindowSizeCallback(m_window, resizeCallback);
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

int WindowGLFW::getKeyStatus(int key) const
{
 return glfwGetKey(m_window, key);
}

void* WindowGLFW::getWindowPointer() const
{
 return m_window;
}

void WindowGLFW::closeCallback(GLFWwindow* window)
{
 Scene* scene = *(Scene**)glfwGetWindowUserPointer(window);
 //TODO
 INFO("window closing");
}

void WindowGLFW::resizeCallback(GLFWwindow* window, int width, int height)
{
 WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
 data->context->resizeViewport(width, height);
 Editor::getEditorInstance()->onResizeEvent(width, height);
 //TODO
}

void WindowGLFW::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
 WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);


 if (action == GLFW_PRESS)
 {
  KeyPressEvent e(key, mods);
  Editor::getEditorInstance()->dispatchEvent(e);

 }
 else if (action == GLFW_RELEASE)
 {
  KeyReleaseEvent e(key);
  Editor::getEditorInstance()->dispatchEvent(e);

 }
 //TODO

}

void WindowGLFW::charCallback(GLFWwindow* window, unsigned int codepoint)
{
 WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

 //TODO
}

void WindowGLFW::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
 WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
 if (action == GLFW_PRESS)
 {
  MouseButtonPressEvent e(button, mods);
  Editor::getEditorInstance()->dispatchEvent(e);

 }
 else if (action == GLFW_RELEASE)
 {
  MouseButtonReleaseEvent e(button);
  Editor::getEditorInstance()->dispatchEvent(e);

 }
 //TODO
}

void WindowGLFW::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
 WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

 //TODO
}

void WindowGLFW::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
 WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

 Cursor& cursor = data->cursor;

 cursor.delta_xpos = xpos - cursor.prev_xpos;
 cursor.delta_ypos = ypos - cursor.prev_ypos;

 cursor.prev_xpos = xpos;
 cursor.prev_ypos = ypos;

 CursorMoveEvent e(cursor.delta_xpos, cursor.delta_ypos);

 
 Editor::getEditorInstance()->dispatchEvent(e);
 //TODO
}


}



