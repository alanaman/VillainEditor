#include <glad/glad.h>
#include "scene.hpp"

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

void Scene::dispatchEvent(Event& e)
{
 m_view_cam->eventHandler(e);
}


}