#include "actor.hpp"

namespace villain {
Actor::Actor()
{
}

Actor::Actor(std::string name)
 :Entity(name)
{
}
void Actor::collectProperties(std::vector<std::shared_ptr<Property>>& properties)
{
 return;
}

}