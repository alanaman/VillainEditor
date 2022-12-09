#pragma once

#include "properties.hpp"

namespace villain{
Property::Property(std::string& name)
 :name(name)
{
}
PropertyVec3::PropertyVec3(std::string& name, glm::vec3 value)
 :Property(name), value(value)
{
}
void Properties::addProperty(std::string& name, glm::vec3& val)
{
 m_properties.push_back(PropertyVec3(name, val));
}

}