#pragma once

#include "logging.hpp"
#include "transform.hpp"
#include "properties.hpp"

namespace villain {

class Entity
{
private:
 static int next_id;

protected:
 Transform m_transform;
 Properties m_properties;

public:
 int id;
 std::string name;
 bool is_selected = false;

 Entity();
 Entity(std::string name);
 Properties& getPropertiesRef() { return m_properties; };
 Transform& getTransformRef() { return m_transform; };
 glm::mat4 getTransformMatrix() { return m_transform.getTransformMatrix(); };

};

}