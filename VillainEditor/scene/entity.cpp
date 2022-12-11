#include "entity.hpp"

namespace villain {

int Entity::next_id = 0;

Entity::Entity() 
 : id(next_id) 
{
 next_id++;
};

}