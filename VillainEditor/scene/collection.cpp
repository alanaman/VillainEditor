#include "collection.hpp"

namespace villain {

int Collection::next_id = 0;

Collection::Collection()
 :id(next_id)
{
 name = "Collection " + std::to_string(id);
 next_id++;
}

Collection::Collection(std::string name)
 :name(name), id(next_id)
{
 next_id++;
}

void Collection::addCollection(std::shared_ptr<Collection> coll)
{
 child_collections.push_back(coll);
}

void Collection::addEntity(std::shared_ptr<Entity> entt)
{
 child_entities.push_back(entt);
}

bool Collection::isParentOf(std::shared_ptr<Collection> coll)
{
 for (auto& child : child_collections)
 {
  if (child == coll)
   return true;
  if (child->isParentOf(coll))
   return true;
 }
 return false;
}

void Collection::resetIdCount()
{
 next_id = 0;
}

}