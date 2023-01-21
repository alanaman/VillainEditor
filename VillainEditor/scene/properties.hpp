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

class MeshId;
class Mesh;
class Shader;
class Material;

enum class DataType
{
 NONE,
 INT, FLOAT, VEC2, VEC3, STRING,
 MESH, TRANSFORM, SHADER, MATERIAL
};

//class PropDefault
//{
//public:
// const std::string name;
// PropDefault(std::string name) :name(name) {};
// virtual DataType getType() const = 0;
//};
//
//#define DEFINE_PROPERTY_DEFAULT(name_tag, type, type_enum) \
//struct PropDef##name_tag:public PropDefault \
//{ \
//public:\
// type def_val;\
// PropDef##name_tag(std::string name, type default_val) : PropDefault(name), def_val(default_val) {};\
// virtual DataType getType() const override { return type_enum; };\
//};\
//
//DEFINE_PROPERTY_DEFAULT(Float, float, DataType::FLOAT)
//DEFINE_PROPERTY_DEFAULT(Vec3, glm::vec3, DataType::VEC3)
//DEFINE_PROPERTY_DEFAULT(Vec2, glm::vec2, DataType::VEC2)
//DEFINE_PROPERTY_DEFAULT(Int, int, DataType::INT)

class PropertyBase
{
public:
 std::string name;
 PropertyBase(std::string name) :name(name) {};
 virtual DataType getType() const = 0;
};

template<typename T>
class Property: public PropertyBase
{
public:
 T& val;
 Property(std::string name, T& val) :PropertyBase(name), val(val) {};
 virtual DataType getType() const override;
};


class Properties
{
 std::vector<PropertyBase*> properties;
public:
 ~Properties();

 void clear();
 std::vector<PropertyBase*>& getPropertiesVector() { return properties; };

 void addProperty(PropertyBase* property);
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

//class PropertyFloat :public Property
//{
//public:
// float &val;
// PropertyFloat(std::string name, float &val) : Property(name), val(val) {};
// virtual DataType getType() const override { return DataType::FLOAT; };
//};
//
//class PropertyTransform :public Property
//{
//public:
// Transform &val;
// PropertyTransform(std::string name, Transform &val) : Property(name), val(val) {};
// virtual DataType getType() const override { return DataType::TRANSFORM; };
//};
//
//class PropertyVec3 :public Property
//{
//public:
// glm::vec3 &val;
// PropertyVec3(std::string name, glm::vec3 &val) : Property(name), val(val) {};
// virtual DataType getType() const override { return DataType::VEC3; };
//};
//
//class PropertyInt :public Property
//{
//public:
// int &val;
// PropertyInt(std::string name, int &val) : Property(name), val(val) {};
// virtual DataType getType() const override { return DataType::INT; };
//};
//
//class PropertyMesh : public Property
//{
//public:
// std::shared_ptr<Mesh> &val;
// PropertyMesh(std::string name, std::shared_ptr<Mesh> &val) : Property(name), val(val) {};
// virtual DataType getType() const override { return DataType::MESH; };
//};


class ParameterBase
{
public:
 std::string name;
 ParameterBase(std::string name) :name(name) {};
 virtual DataType getType() const = 0;

 virtual PropertyBase* getProperty()=0;

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(CEREAL_NVP(name));
 };
 template<class Archive>
 void load(Archive& archive)
 {
  try { archive(CEREAL_NVP(name)); }
  catch (const std::exception&) {};
 };
 friend class cereal::access;
};

template<typename T>
class Parameter : public ParameterBase
{
private:
 Parameter();//for cereal
public:
 T val;
 Parameter(std::string name, T val) :ParameterBase(name), val(val) {};
 virtual DataType getType() const override;
 virtual PropertyBase* getProperty() override { return new Property<T>(name, val); };

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(cereal::base_class<ParameterBase>(this));
  archive(CEREAL_NVP(val));
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(cereal::base_class<ParameterBase>(this));
  try { archive(CEREAL_NVP(val)); }
  catch (const std::exception&) {};
 };
 friend class cereal::access;
};

class Parameters
{
 std::vector<ParameterBase*> parameters;
public:
 ~Parameters();

 void clear();
 std::vector<ParameterBase*>& getParameterVector() { return parameters; };

 void addParameter(ParameterBase* parameter);

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(CEREAL_NVP(parameters));
 };
 template<class Archive>
 void load(Archive& archive)
 {
  try { archive(CEREAL_NVP(parameters)); }
  catch (const std::exception&) {};
 };
 friend class cereal::access;
};
}

//CEREAL_REGISTER_TYPE(villain::Parameter<int>);
//CEREAL_REGISTER_TYPE(villain::Parameter<float>);
//CEREAL_REGISTER_TYPE(villain::Parameter<glm::vec2>);
//CEREAL_REGISTER_TYPE(villain::Parameter<glm::vec3>);
//CEREAL_REGISTER_TYPE(villain::Parameter<std::string>);
//CEREAL_REGISTER_TYPE(villain::Parameter<villain::Transform>);
//CEREAL_REGISTER_TYPE(villain::Parameter<std::shared_ptr<villain::Mesh>>);
//CEREAL_REGISTER_TYPE(villain::Parameter<std::shared_ptr<villain::Shader>>);
//CEREAL_REGISTER_TYPE(villain::Parameter<std::shared_ptr<villain::Material>>);

//TODO add this to macro
//CEREAL_REGISTER_TYPE(villain::PropertyFloat);
//CEREAL_REGISTER_TYPE(villain::PropertyInt);
//CEREAL_REGISTER_TYPE(villain::PropertyVec3);
//CEREAL_REGISTER_TYPE(villain::PropertyMesh);
