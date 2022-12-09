#pragma once

#include "logging.hpp"
#include "transform.hpp"
#include "properties.hpp"

namespace villain {

class Entity
{
protected:
 Transform m_transform;
 Properties m_properties;


public:

 Properties& getPropertiesRef() { return m_properties; };
 Transform& getTransformRef() { return m_transform; };
 glm::mat4 getTransformMatrix() { return m_transform.getTransformMatrix(); };

};
}