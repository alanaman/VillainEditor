#pragma once

#include "logging.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "events.hpp"

namespace villain {
class Scene
{
private:
 std::string m_name;
 std::vector<std::shared_ptr<Model>> m_models;
 std::vector<std::shared_ptr<Shader>> m_shaders;

 Renderer m_renderer;
 std::shared_ptr<Camera> m_view_cam;
public:
 Scene(std::string name, int aspectX, int aspectY);
 void updateOnFrame();
 void addModelFromFile();
 void addModel(std::shared_ptr<Model> model);

 void dispatchEvent(Event& e);

 //TODO
 void saveScene();
 void loadScene();
};
}