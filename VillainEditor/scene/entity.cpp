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
;

}