#include "bullet.hpp"

namespace villain {

REGISTER_ACTOR(Bullet);

const std::vector<std::shared_ptr<PropDef>> Bullet::default_properties = {
 std::make_shared<PropDefFloat>(std::string("speed"), 7.0f),
 std::make_shared<PropDefVec3>(std::string("direction"), glm::vec3(0,1,0))
 //std::make_shared<PropDefFloat>(std::string("scale"), 1.5f)
};


//std::shared_ptr<Mesh> Gunner::gunner_mesh = NULL;


std::shared_ptr<Actor> Bullet::create()
{
 auto ptr = std::make_shared<Bullet>(std::string("bullet_inst"));
 std::vector<std::shared_ptr<Mesh>> meshes;
 ptr->collectMeshes(meshes);
 for (auto& mesh : meshes)
  mesh->setParent(ptr);
 return ptr;
}

Bullet::Bullet(std::string name)
 :Actor(name)
{
 auto x = std::string("bullet");
 bullet_mesh = Mesh::create(x);

 for (const auto& prop : default_properties)
 {
  props.addPropertyFromDefault(prop.get());
 }

}
void Bullet::beginPlay()
{
 //m_transform.setScale(glm::vec3(2, 2, 2));
}

void Bullet::updateOnFrame(const float& deltatime)
{
 auto dir = props.getVec3FromName("direction");
 auto speed = props.getFloatFromName("speed");
 m_transform.setPosition(m_transform.getPosition() + deltatime*speed*dir);
}
void Bullet::collectMeshes(std::vector<std::shared_ptr<Mesh>>& meshes)
{
 this->Actor::collectMeshes(meshes);
 meshes.push_back(bullet_mesh);
 return;
}

void Bullet::collectProperties(std::vector<std::shared_ptr<Property>>& properties)
{
 this->Actor::collectProperties(properties);
 for (auto& prop : props.properties)
 {
  properties.push_back(prop);
 }
 return;
}
void Bullet::setProperty(std::string name, glm::vec3 val)
{
 auto property = props.getPropertyfromName(name);
 std::dynamic_pointer_cast<PropertyVec3>(property)->val=val;

}
}