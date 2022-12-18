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
 std::weak_ptr<Entity> m_parent;
 Transform m_transform;

public:
 int id;
 std::string name;
 bool is_selected = false;

 Entity();
 Entity(std::string name);
 virtual ~Entity() = default;
 Transform& getLocalTransformRef();
 glm::mat4 getTransformMatrix();

 void setParent(std::weak_ptr<Entity> parent);

 virtual void collectProperties(std::vector<std::shared_ptr<Property>>& properties) { return; };

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   CEREAL_NVP(id),
   CEREAL_NVP(name),
   CEREAL_NVP(is_selected),
   CEREAL_NVP(m_transform)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(id, name, is_selected, m_transform);
 };
 friend class cereal::access;
};

}