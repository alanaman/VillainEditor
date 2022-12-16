#pragma once

#include "logging.hpp"
#include "properties.hpp"
#include "transform.hpp"
#include "mesh.hpp"

namespace villain {

class Actor : public Entity
{
public:
 Actor();
 Actor(std::string name);
 virtual void beginPlay(){};
 virtual void actorBeginOverlap(Actor& otherActor){};
 virtual void updateOnFrame(){};
 virtual void getMesh(std::vector<std::shared_ptr<Mesh>>& meshes) { return; };
};

}