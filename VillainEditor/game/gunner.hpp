#pragma once

#include "asset_library/actor_library.hpp"
#include "asset_library/meshlibrary.hpp"
#include "logging.hpp"
#include "scene/actor.hpp"
#include "graphics/mesh.hpp"

namespace villain {


class Gunner : public Actor
{
private:
 std::shared_ptr<Mesh> gunner_mesh;
 Properties props;

 static const std::vector<std::shared_ptr<PropDef>> default_properties;

 Gunner() {}; //for cereal

 float bullet_timer = 0;
public:
 static std::shared_ptr<Actor> create();

 Gunner(std::string name);
 virtual void beginPlay() override;
 virtual void updateOnFrame(const float& deltatime) override;



 virtual void collectMeshes(std::vector<std::shared_ptr<Mesh>>& meshes) override;

 virtual void collectProperties(std::vector<std::shared_ptr<Property>>& properties) override;

 void spawnBullet();
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