#include "gunner.hpp"

namespace villain {
Gunner::Gunner(std::string name, std::shared_ptr<Model> model)
 :Actor(name), model(model)
{
}
void Gunner::beginPlay()
{
 m_transform.setScale(glm::vec3(2, 2, 2));
}

void Gunner::updateOnFrame()
{
 m_transform.setRotation(m_transform.getRotation() + glm::vec3(.1, 0, 0));
}
std::shared_ptr<Model> Gunner::getModel()
{
 return model;
}
}