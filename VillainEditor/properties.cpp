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
 m_properties.push_back(std::make_shared<PropertyVec3>(name, val));
}
void Properties::addProperty(Transform& trans)
{
 addProperty(std::string("Position"), trans.getPosition());
 addProperty(std::string("Scale"), trans.getScale());
 addProperty(std::string("Rotation"), trans.getRotation());
}
}