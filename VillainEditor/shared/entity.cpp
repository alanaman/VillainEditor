#include "entity.hpp"

namespace villain {

int Entity::next_id = 0;

Entity::Entity() 
 : id(next_id) 
{
 next_id++;
 name = "Entity "+std::to_string(id);
}

Entity::Entity(std::string name)
 : id(next_id), name(name)
{
 next_id++;
}

Transform& Entity::getLocalTransformRef() 
{ 
 return m_transform; 
}

glm::mat4 Entity::getTransformMatrix() 
{
 if(auto temp_ptr=m_parent.lock())
  return temp_ptr->getTransformMatrix() * m_transform.getTransformMatrix();
 
 return m_transform.getTransformMatrix();

}

void Entity::setParent(std::weak_ptr<Entity> parent)
{
 m_parent = parent;
}

void Entity::collectProperties(Properties& properties)
{
 properties.addProperty(new Property<Transform>("Transform", m_transform));
}


}