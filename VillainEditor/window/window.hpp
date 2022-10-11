#pragma once
#include <string>

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

public:
  static Window* create(const WindowProperties& props);
  virtual bool shouldClose() const = 0;
  virtual void update() const = 0;
  virtual void terminate() const = 0;
  //virtual void setVSync(bool enabled);
};
}
