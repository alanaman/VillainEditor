#pragma once

#include "logging.hpp"
#include "transform.hpp"
#include "glm.hpp"

namespace villain {

enum class PropertyType
{
 NONE,
 INT, FLOAT, VEC2, VEC3
};


struct Property
{
 const std::string name;
 void* value_ptr;
 const PropertyType type;

 Property(std::string name, int& value);
 Property(std::string name, float& value);
 Property(std::string name, glm::vec3& value);
 PropertyType getType() const;
};

}