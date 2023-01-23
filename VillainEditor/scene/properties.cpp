#pragma once

#include "properties.hpp"



namespace villain{

DataType Property<int>::getType() const { return DataType::INT; }
DataType Property<float>::getType() const { return DataType::FLOAT; }
DataType Property<glm::vec2>::getType() const { return DataType::VEC2; }
DataType Property<glm::vec3>::getType() const { return DataType::VEC3; }
DataType Property<std::string>::getType() const { return DataType::STRING; }
DataType Property<Transform>::getType() const { return DataType::TRANSFORM; }
DataType Property<std::shared_ptr<Mesh>>::getType() const { return DataType::MESH; }
DataType Property<std::shared_ptr<Shader>>::getType() const { return DataType::SHADER; }
DataType Property<std::shared_ptr<Material>>::getType() const { return DataType::MATERIAL; }


DataType Parameter<int>::getType() const { return DataType::INT; }
DataType Parameter<float>::getType() const { return DataType::FLOAT; }
DataType Parameter<glm::vec2>::getType() const { return DataType::VEC2; }
DataType Parameter<glm::vec3>::getType() const { return DataType::VEC3; }
DataType Parameter<std::string>::getType() const { return DataType::STRING; }
DataType Parameter<Transform>::getType() const { return DataType::TRANSFORM; }
DataType Parameter<std::shared_ptr<Mesh>>::getType() const { return DataType::MESH; }
DataType Parameter<std::shared_ptr<Shader>>::getType() const { return DataType::SHADER; }
DataType Parameter<std::shared_ptr<Material>>::getType() const { return DataType::MATERIAL; }

//template<typename T>
//PropertyBase* Parameter<T>::getProperty()
//{
// return nullptr;
// //return new Property<T>(name, val);
//}




Properties::~Properties()
{
 for (auto prop : properties)
  delete prop;
}
void Properties::clear()
{
 for (auto prop : properties)
  delete prop;
 properties.clear();
}
void Properties::addProperty(PropertyBase* property)
{
 properties.push_back(property);
}

//std::shared_ptr<Property> Properties::getPropertyfromName(const std::string& name)
//{
// for (auto& prop : properties)
// {
//  if (prop->name == name)
//   return prop;
// }
// return NULL;
//}
//
//float Properties::getFloatFromName(const std::string& name)
//{
// return std::dynamic_pointer_cast<PropertyFloat>(getPropertyfromName(name))->val;
//}
//
//glm::vec3 Properties::getVec3FromName(const std::string& name)
//{
// return std::dynamic_pointer_cast<PropertyVec3>(getPropertyfromName(name))->val;
//}
//
//void Properties::addPropertyFromDefault(const std::shared_ptr<PropDefault>& default_prop)
//{
// switch (default_prop->getType())
// {
// case DataType::FLOAT:
// {
//  properties.push_back(
//   std::make_shared<PropertyFloat>(
//    default_prop->name,
//    std::dynamic_pointer_cast<PropDefFloat>(default_prop)->def_val
//    )
//  );
//  break;
// }
// case DataType::VEC3:
// {
//  properties.push_back(
//   std::make_shared<PropertyVec3>(
//    default_prop->name,
//    std::dynamic_pointer_cast<PropDefVec3>(default_prop)->def_val
//    )
//  );
//  break;
// }
// default:
//  ERROR("unknown type");
// }
//};
//
//void Properties::resolveProperties(const std::vector<std::shared_ptr<PropDefault>>& default_properties)
//{
// Properties new_props;
//
// for (auto& default_prop : default_properties)
// {
//  if (auto prop = getPropertyfromName(default_prop->name))
//   new_props.addProperty(prop);
//  else
//   new_props.addPropertyFromDefault(default_prop);
// }
// properties = new_props.properties;
//}


Parameters::~Parameters()
{
 //TODO add warning if still being used;
}

void Parameters::clear()
{
 parameters.clear();
}

void Parameters::addParameter(std::shared_ptr<ParameterBase> parameter)
{
 parameters.push_back(parameter);
}

std::shared_ptr<ParameterBase> Parameters::getParameter(std::string& parameter_name)
{
 for (auto& param : parameters)
 {
  if (parameter_name == param->name)
   return param;
 }
 return NULL;
}

}