#pragma once

#include "logging.hpp"
#include "properties.hpp"
#include "transform.hpp"
#include "mesh.hpp"

namespace villain {

class Actor
{
protected:
 std::string name;
 Transform m_transform;
 Properties m_properties;
public:
 Actor();
 Actor(std::string name);
 virtual void beginPlay(){};
 virtual void actorBeginOverlap(Actor& otherActor){};
 virtual void updateOnFrame(){};
 virtual std::shared_ptr<Mesh> getMesh() { return NULL; };
 glm::mat4 getTransformMatrix() { return m_transform.getTransformMatrix(); };
 Transform& getTransformRef() { return m_transform; };
};

}