#include "logging.hpp"
#include "transform.hpp"
#include "glm.hpp"

namespace villain {

class Property
{
 std::string name;
public:
 Property(std::string& name);
};

class PropertyVec3 :public Property
{
 glm::vec3& value;
public:
 PropertyVec3(std::string& name, glm::vec3 value);

};

class Properties
{
 std::vector<std::shared_ptr<Property>> m_properties;

public:
 void addProperty(std::string& name, glm::vec3& val);
 void addProperty(Transform& trans);

};







}