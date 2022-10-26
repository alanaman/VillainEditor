#pragma once

#include <string>
#include <vector>
#include "model.hpp"
#include "camera.hpp"

namespace villain {
class Scene
{
private:
 std::string m_name;
 std::vector<std::shared_ptr<Model>> m_models;

 Camera m_view_cam;
public:
 Scene(std::string name, int aspectX, int aspectY);
 void render();
 void addModel(std::shared_ptr<Model> model) { m_models.push_back(model); };
};
}