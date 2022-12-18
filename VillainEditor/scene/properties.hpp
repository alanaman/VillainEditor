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

class PropDef
{
public:
 const std::string name;
 PropDef(std::string name) :name(name) {};
 virtual PropertyType getType() const = 0;
};

struct PropDefFloat :public PropDef
{
public:
 float def_val;
 PropDefFloat(std::string name, float default_val) : PropDef(name), def_val(default_val) {};
 virtual PropertyType getType() const override { return PropertyType::FLOAT; };

};

struct Property
{
protected:
 Property() {};//cereal
public:
 std::string name;
 Property(std::string name) :name(name) {};
 virtual PropertyType getType() const = 0;

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   CEREAL_NVP(name)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   name
  );
 };
 friend class cereal::access;
};

struct PropertyFloat :public Property
{
 PropertyFloat() {};//cereal
public:
 float val;
 PropertyFloat(std::string name, float val) : Property(name), val(val) {};
 virtual PropertyType getType() const override { return PropertyType::FLOAT; };

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   cereal::virtual_base_class<Property>(this),
   CEREAL_NVP(val)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   cereal::virtual_base_class<Property>(this),
   val
  );
 };
 friend class cereal::access;
};

class PropertyInt :public Property
{
public:
 PropertyInt() {};//cereal
 int val;
 PropertyInt(std::string name, int val) : Property(name), val(val) {};
 virtual PropertyType getType() const override { return PropertyType::INT; };

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   cereal::virtual_base_class<Property>(this),
   CEREAL_NVP(val)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   cereal::virtual_base_class<Property>(this),
   val
  );
 };
 friend class cereal::access;
};

class Properties
{
public:
 std::vector<std::shared_ptr<Property>> properties;
 void addProperty(std::shared_ptr<Property> property);
 std::shared_ptr<Property> getPropertyfromName(const std::string& name);
 float getFloatfromName(const std::string& name);
 void addPropertyFromDefault(PropDef* default_prop);
 void resolveProperties(const std::vector<std::shared_ptr<PropDef>>& default_properties);

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   CEREAL_NVP(properties)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   properties
  );
 };
 friend class cereal::access;
};

}

CEREAL_REGISTER_TYPE(villain::PropertyFloat);
CEREAL_REGISTER_TYPE(villain::PropertyInt);
