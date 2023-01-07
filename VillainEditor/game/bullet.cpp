#include "bullet.hpp"

namespace villain {

REGISTER_ACTOR(Bullet);

std::shared_ptr<Actor> Bullet::create()
{
 auto ptr = std::make_shared<Bullet>(std::string("bullet_inst"));
 return ptr;
}

Bullet::Bullet(std::string name)
 :Actor(name)
{
}
void Bullet::beginPlay()
{
}

void Bullet::updateOnFrame(const float& deltatime)
{
 m_transform.setPosition(m_transform.getPosition() + deltatime*speed*direction);
}
void Bullet::collectMeshes(std::vector<std::shared_ptr<Mesh>>& meshes)
{
 this->Actor::collectMeshes(meshes);
 meshes.push_back(bullet_mesh);
 return;
}

void Bullet::collectProperties(Properties& properties)
{
 this->Actor::collectProperties(properties);
 properties.addProperty(new Property<float>("speed", speed));
 properties.addProperty(new Property<glm::vec3>("direction", direction));
 return;
}

void Bullet::setSpeed(float speed)
{
 this->speed = speed;
}

void Bullet::setDirection(glm::vec3 direction)
{
 this->direction = direction;
}

}