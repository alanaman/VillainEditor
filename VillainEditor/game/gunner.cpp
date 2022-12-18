#include "gunner.hpp"

namespace villain {

REGISTER_ACTOR(Gunner);

const std::vector<std::shared_ptr<PropDef>> Gunner::default_properties = {
 std::make_shared<PropDefFloat>(std::string("spin_speed"), 0.0f),
 //std::make_shared<PropDefFloat>(std::string("scale"), 1.5f)
};


//std::shared_ptr<Mesh> Gunner::gunner_mesh = NULL;


std::shared_ptr<Actor> Gunner::create()
{
 auto ptr = std::make_shared<Gunner>(std::string("gunner_inst"));
 std::vector<std::shared_ptr<Mesh>> meshes;
 ptr->collectMeshes(meshes);
 for (auto& mesh : meshes)
  mesh->setParent(ptr);
 return ptr;
}

Gunner::Gunner(std::string name)
 :Actor(name)
{
 auto x = std::string("gunner");
 gunner_mesh = Mesh::create(x);

 for (const auto& prop : default_properties)
 {
  props.addPropertyFromDefault(prop.get());
 }

}
void Gunner::beginPlay()
{
 //m_transform.setScale(glm::vec3(2, 2, 2));
}

void Gunner::updateOnFrame()
{
 m_transform.setRotation(m_transform.getRotation() + glm::vec3(props.getFloatfromName("spin_speed"), 0, 0));
}
void Gunner::collectMeshes(std::vector<std::shared_ptr<Mesh>>& meshes)
{
 this->Actor::collectMeshes(meshes);
 meshes.push_back(gunner_mesh);
 return;
}

void Gunner::collectProperties(std::vector<std::shared_ptr<Property>>& properties)
{
 this->Actor::collectProperties(properties);
 for (auto& prop : props.properties)
 {
  properties.push_back(prop);
 }
 return;
}
}