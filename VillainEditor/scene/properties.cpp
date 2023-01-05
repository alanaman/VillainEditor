#pragma once

#include "properties.hpp"



namespace villain{

PropertyType Property<int>::getType() const { return PropertyType::INT; }
PropertyType Property<float>::getType() const { return PropertyType::FLOAT; }
PropertyType Property<glm::vec2>::getType() const { return PropertyType::VEC2; }
PropertyType Property<glm::vec3>::getType() const { return PropertyType::VEC3; }
PropertyType Property<Transform>::getType() const { return PropertyType::TRANSFORM; }



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
// case PropertyType::FLOAT:
// {
//  properties.push_back(
//   std::make_shared<PropertyFloat>(
//    default_prop->name,
//    std::dynamic_pointer_cast<PropDefFloat>(default_prop)->def_val
//    )
//  );
//  break;
// }
// case PropertyType::VEC3:
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


}