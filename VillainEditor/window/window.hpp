#pragma once
#include <string>
#include "scene.hpp"

namespace villain {

struct WindowProperties
{
  std::string name;
  int width, height;

  WindowProperties(std::string name, int width, int height):
    name(name), width(width), height(height){}
};


class Window
{
protected:
 std::string m_name;
 int m_width, m_height;
 Scene* m_scene;
public:
  static Window* create(const WindowProperties& props);
  virtual int getKeyStatus(int key) const = 0;
  virtual bool shouldClose() const = 0;
  virtual void update() const = 0;
  virtual void terminate() const = 0;
  void attachScene(Scene &scene) { m_scene = &scene; };
  //virtual void setVSync(bool enabled);

};
}
