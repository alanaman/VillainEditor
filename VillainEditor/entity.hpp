#pragma once

#include "logging.hpp"
#include "transform.hpp"
#include "properties.hpp"

namespace villain {

class Entity
{
protected:
 Transform m_tranform;
 Properties m_properties;


public:

 Properties& getPropertiesRef() { return m_properties; };
 Transform& getTransformRef() { return m_tranform; };

};
}