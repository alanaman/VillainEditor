#include "scene.hpp"
#include "input.hpp"
#include "window/filedialog.hpp"

namespace villain {
Scene::Scene(std::string name, int aspectX, int aspectY):
 m_name(name), m_renderer(m_models, m_shaders)
{
 m_view_cam = std::make_shared<Camera>(aspectX, aspectY);
 m_renderer.submitCamera(m_view_cam);
}
void Scene::updateOnFrame()
{

 m_view_cam->updateOnFrame();
 m_renderer.renderFrame();

}

void Scene::addModelFromFile()
{
 std::string filename = FileBrowser::selectFile();
 if (filename == "")
  return;
 auto model = Model::create(filename);
 model->setShader(Shader::create(
  "resources/shaders/basic_vertex2.glsl",
  "resources/shaders/basic_fragment2.glsl"));
 model->loadMesh();

 addModel(model);
}

void Scene::addModel(std::shared_ptr<Model> model)
{
 m_models.push_back(model);
 m_renderer.submitModel(*model);
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