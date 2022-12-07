#include <glad/glad.h>
#include "scene.hpp"
#include "input.hpp"
#include "window/filedialog.hpp"

namespace villain {
Scene::Scene(std::string name, int aspectX, int aspectY):
 m_name(name)
{
 m_view_cam = std::make_shared<Camera>(aspectX, aspectY);
}

void Scene::render()
{
//TODO clean this up
 glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 m_view_cam->updateOnFrame();
 for (auto& model : m_models)
  model->draw(m_view_cam->getProjectionViewMatrix());
}

void Scene::addModelFromFile()
{
 std::string filename = FileBrowser::selectFile();
 if (filename == "")
  return;
 auto model = Model::create("cube", filename);
 model->setShader(Shader::create(
  "resources/shaders/basic_vertex2.glsl",
  "resources/shaders/basic_fragment2.glsl"));
 model->loadMeshes();

 addModel(model);
}

void Scene::dispatchEvent(Event& e)
{
 switch (e.getEventType())
 {
 case EventType::KeyPress:
 {
  KeyPressEvent* ke = (KeyPressEvent*)&e;
  int key = ke->key;
  if (key == KEY::A && (e.mods & MOD::SHIFT))
  {
   addModelFromFile();
   return;
  }
  break;
 }
 default:
  break;
 }
 m_view_cam->eventHandler(e);
}


}