#include "actor.hpp"

namespace villain {
Actor::Actor()
{
}

Actor::Actor(std::string name)
 :Entity(name)
{
}
void Actor::collectProperties(Properties& properties)
{
 this->Entity::collectProperties(properties);
 return;
}

}