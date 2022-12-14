#pragma once
#include <string>
#include "scene.hpp"
#include "input.hpp"
#include "context.hpp"

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

 struct WindowData
 {
  Cursor cursor;
  GraphicsContext* context = NULL;
 };

 WindowData m_data;

public:
  static Window* create(const WindowProperties& props);
  virtual int getKeyStatus(int key) const = 0;
  virtual void* getWindowPointer() const = 0;
  virtual bool shouldClose() const = 0;
  virtual void update() const = 0;
  virtual void terminate() const = 0;
  void attachScene(Scene &scene) {};

  //virtual void setVSync(bool enabled);

};
}
