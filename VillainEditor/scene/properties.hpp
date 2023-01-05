#pragma once

#include "logging.hpp"
#include "transform.hpp"
#include "glm/glm.hpp"


//namespace glm
//{
//template<class Archive>
//void serialize(Archive& archive,
// vec3& m)
//{
// archive(m.x, m.y, m.z);
//}
//template<class Archive>
//void serialize(Archive& archive,
// vec2& m)
//{
// archive(m.x, m.y);
//}
//}

namespace villain {

class Mesh;

enum class PropertyType
{
 NONE,
 INT, FLOAT, VEC2, VEC3,
 MESH, TRANSFORM
};

//class PropDefault
//{
//public:
// const std::string name;
// PropDefault(std::string name) :name(name) {};
// virtual PropertyType getType() const = 0;
//};
//
//#define DEFINE_PROPERTY_DEFAULT(name_tag, type, type_enum) \
//struct PropDef##name_tag:public PropDefault \
//{ \
//public:\
// type def_val;\
// PropDef##name_tag(std::string name, type default_val) : PropDefault(name), def_val(default_val) {};\
// virtual PropertyType getType() const override { return type_enum; };\
//};\
//
//DEFINE_PROPERTY_DEFAULT(Float, float, PropertyType::FLOAT)
//DEFINE_PROPERTY_DEFAULT(Vec3, glm::vec3, PropertyType::VEC3)
//DEFINE_PROPERTY_DEFAULT(Vec2, glm::vec2, PropertyType::VEC2)
//DEFINE_PROPERTY_DEFAULT(Int, int, PropertyType::INT)

class PropertyBase
{
public:
 std::string name;
 PropertyBase(std::string name) :name(name) {};
 virtual PropertyType getType() const = 0;
};

//#define SERIALIZE_PROPERTY(classname)\
//template<class Archive>\
//void save(Archive& archive, const classname& prop)\
//{\
// archive(\
//  cereal::virtual_base_class<Property>(&prop),\
//  CEREAL_NVP(prop.val)\
// );\
//};\
//template<class Archive>\
//void load(Archive& archive, classname& prop)\
//{\
// archive(\
//  cereal::virtual_base_class<Property>(&prop),\
//  CEREAL_NVP(prop.val)\
// );\
//};\

template<typename T>
class Property: public PropertyBase
{
public:
 T& val;
 Property(std::string name, T& val) :PropertyBase(name), val(val) {};
 virtual PropertyType getType() const override;
};


//class PropertyFloat :public Property
//{
//public:
// float &val;
// PropertyFloat(std::string name, float &val) : Property(name), val(val) {};
// virtual PropertyType getType() const override { return PropertyType::FLOAT; };
//};
//
//class PropertyTransform :public Property
//{
//public:
// Transform &val;
// PropertyTransform(std::string name, Transform &val) : Property(name), val(val) {};
// virtual PropertyType getType() const override { return PropertyType::TRANSFORM; };
//};
//
//class PropertyVec3 :public Property
//{
//public:
// glm::vec3 &val;
// PropertyVec3(std::string name, glm::vec3 &val) : Property(name), val(val) {};
// virtual PropertyType getType() const override { return PropertyType::VEC3; };
//};
//
//class PropertyInt :public Property
//{
//public:
// int &val;
// PropertyInt(std::string name, int &val) : Property(name), val(val) {};
// virtual PropertyType getType() const override { return PropertyType::INT; };
//};
//
//class PropertyMesh : public Property
//{
//public:
// std::shared_ptr<Mesh> &val;
// PropertyMesh(std::string name, std::shared_ptr<Mesh> &val) : Property(name), val(val) {};
// virtual PropertyType getType() const override { return PropertyType::MESH; };
//};

class Properties
{
 std::vector<PropertyBase*> properties;
public:
 ~Properties();

 void clear();
 std::vector<PropertyBase*>& getPropertiesVector() { return properties; };

 void addProperty(PropertyBase* property);
};

}

//TODO add this to macro
//CEREAL_REGISTER_TYPE(villain::PropertyFloat);
//CEREAL_REGISTER_TYPE(villain::PropertyInt);
//CEREAL_REGISTER_TYPE(villain::PropertyVec3);
//CEREAL_REGISTER_TYPE(villain::PropertyMesh);
