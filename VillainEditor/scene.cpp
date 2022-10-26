#include "scene.hpp"

namespace villain {
Scene::Scene(std::string name, int aspectX, int aspectY):
 m_name(name), m_view_cam(aspectX, aspectY)
{}

void Scene::render()
{
 for (auto model : m_models)
  model->draw(m_view_cam.getProjectionViewMatrix());
}
}