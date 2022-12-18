#pragma once

#include "logging.hpp"
#include "properties.hpp"
#include "transform.hpp"
#include "entity.hpp"
#include "mesh.hpp"

namespace villain {

class Actor : public Entity
{
public:
 Actor();
 Actor(std::string name);
 virtual void beginPlay(){};
 virtual void actorBeginOverlap(Actor& otherActor){};
 virtual void updateOnFrame(const float& deltatime){};
 virtual void collectMeshes(std::vector<std::shared_ptr<Mesh>>& meshes) { return; };

 virtual void collectProperties(std::vector<std::shared_ptr<Property>>& properties) override;
 virtual void setProperty(std::string name, glm::vec3 val) {};


 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   cereal::base_class<Entity>(this)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   cereal::base_class<Entity>(this)
  );
 };
 friend class cereal::access;
};

}
CEREAL_REGISTER_TYPE(villain::Actor);