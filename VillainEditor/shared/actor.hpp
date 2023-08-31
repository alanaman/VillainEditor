#pragma once

#include "logging.hpp"
#include "properties.hpp"
#include "transform.hpp"
#include "entity.hpp"
#include "alternate_impl/mesh_component.hpp"

namespace villain {



class Actor : public Entity
{

public:
 Actor();
 Actor(std::string name);
 virtual void beginPlay(){};
 virtual void actorBeginOverlap(Actor& otherActor){};
 virtual void updateOnFrame(const float& deltatime){};
 virtual void collectMeshes(std::vector<MeshComponent*>& meshes) { return; };

 virtual void collectProperties(Properties& properties) override;


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