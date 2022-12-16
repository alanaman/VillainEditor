#include "gunner.hpp"

namespace villain {

REGISTER_ACTOR(Gunner);


//std::shared_ptr<Mesh> Gunner::gunner_mesh = NULL;


std::shared_ptr<Actor> Gunner::create()
{
 auto ptr = std::make_shared<Gunner>(std::string("gunner_inst"));
 std::vector<std::shared_ptr<Mesh>> meshes;
 ptr->getMesh(meshes);
 for (auto& mesh : meshes)
  mesh->setParent(ptr);
 return ptr;
}

Gunner::Gunner(std::string name)
 :Actor(name)
{
 auto x = std::string("gunner");
 gunner_mesh = Mesh::create(x);
}
void Gunner::beginPlay()
{
 m_transform.setScale(glm::vec3(2, 2, 2));
}

void Gunner::updateOnFrame()
{
 m_transform.setRotation(m_transform.getRotation() + glm::vec3(.1, 0, 0));
}
void Gunner::getMesh(std::vector<std::shared_ptr<Mesh>>& meshes)
{
 this->Actor::getMesh(meshes);
 meshes.push_back(gunner_mesh);
 return;
}
}