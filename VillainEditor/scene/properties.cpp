#pragma once

#include "properties.hpp"



namespace villain{

void Properties::addProperty(std::shared_ptr<Property> property)
{
 properties.push_back(property);
}

std::shared_ptr<Property> Properties::getPropertyfromName(const std::string& name)
{
 for (auto& prop : properties)
 {
  if (prop->name == name)
   return prop;
 }
 return NULL;
}

float Properties::getFloatfromName(const std::string& name)
{
 return std::dynamic_pointer_cast<PropertyFloat>(getPropertyfromName(name))->val;
}

void Properties::addPropertyFromDefault(PropDef* default_prop)
{
 switch (default_prop->getType())
 {
 case PropertyType::FLOAT:
 {
  properties.push_back(std::make_shared<PropertyFloat>(
   default_prop->name,
   ((PropDefFloat*)default_prop)->def_val)
  );
  break;
 }
 default:
  break;
 }
}

void Properties::resolveProperties(const std::vector<std::shared_ptr<PropDef>>& default_properties)
{
 Properties new_props;

 for (auto& default_prop : default_properties)
 {
  if (auto prop = getPropertyfromName(default_prop->name))
   new_props.addProperty(prop);
  else
   new_props.addPropertyFromDefault(default_prop.get());
 }
 properties = new_props.properties;
}


}