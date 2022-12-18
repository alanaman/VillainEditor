#pragma once

#include "properties.hpp"

namespace villain{

PropertyType Property::getType() const
{
 return type;
}

Property::Property(std::string name, glm::vec3& value)
 :name(name), value_ptr(&value), type(PropertyType::VEC3)
{
}

Property::Property(std::string name, int& value)
 :name(name), value_ptr(&value), type(PropertyType::INT)
{
}

Property::Property(std::string name, float& value)
 :name(name), value_ptr(&value), type(PropertyType::FLOAT)
{
}

}