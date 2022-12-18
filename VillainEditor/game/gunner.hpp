#pragma once

#include "actor_library.hpp"
#include "meshlibrary.hpp"
#include "logging.hpp"
#include "actor.hpp"
#include "mesh.hpp"

namespace villain {


class Gunner : public Actor
{
private:
 std::shared_ptr<Mesh> gunner_mesh;
 Properties props;

 static const std::vector<std::shared_ptr<PropDef>> default_properties;

 Gunner() {}; //for cereal
public:
 static std::shared_ptr<Actor> create();

 Gunner(std::string name);
 virtual void beginPlay() override;
 virtual void updateOnFrame() override;



 virtual void collectMeshes(std::vector<std::shared_ptr<Mesh>>& meshes) override;

 virtual void collectProperties(std::vector<std::shared_ptr<Property>>& properties) override;

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   cereal::base_class<Actor>(this),
   CEREAL_NVP(gunner_mesh),
   CEREAL_NVP(props)
   );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   cereal::base_class<Actor>(this),
   gunner_mesh,
   props
  );
  props.resolveProperties(default_properties);
 };
 friend class cereal::access;
};
}
CEREAL_REGISTER_TYPE(villain::Gunner);