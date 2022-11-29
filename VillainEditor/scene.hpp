#pragma once

#include <string>
#include <vector>
#include <memory>
#include "model.hpp"
#include "camera.hpp"
#include "events.hpp"

namespace villain {
class Scene
{
private:
 std::string m_name;
 std::vector<std::shared_ptr<Model>> m_models;

 std::shared_ptr<Camera> m_view_cam;
public:
 Scene(std::string name, int aspectX, int aspectY);
 void render();
 void addModel(std::shared_ptr<Model> model) { m_models.push_back(model); };

 void dispatchEvent(Event& e);
};
}