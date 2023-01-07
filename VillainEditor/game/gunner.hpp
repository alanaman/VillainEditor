#pragma once

#include "asset_library/actor_library.hpp"
#include "asset_library/meshlibrary.hpp"
#include "logging.hpp"
#include "scene/actor.hpp"
#include "graphics/mesh.hpp"

#include "bullet.hpp"
namespace villain {


class Gunner : public Actor
{
 //make properties member vars
 //property classes shud have references to these member vars
private:

 //shared vars

 //per instance editable vars
 float spin_speed = 1.0f;
 float fire_interval = 1.0f;

 //unexposed vars
 const std::shared_ptr<Mesh> gunner_mesh = Mesh::create("gunner");
 
 float bullet_timer = 0;

 Gunner() {}; //for cereal
public:
 static std::shared_ptr<Actor> create();

 Gunner(std::string name);
 virtual void beginPlay() override;
 virtual void updateOnFrame(const float& deltatime) override;



 virtual void collectMeshes(std::vector<std::shared_ptr<Mesh>>& meshes) override;

 virtual void collectProperties(Properties& properties) override;

 void spawnBullet();
 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   cereal::base_class<Actor>(this),
   CEREAL_NVP(spin_speed),
   CEREAL_NVP(fire_interval)
   //CEREAL_NVP(gunner_mesh)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(cereal::base_class<Actor>(this));
  try { archive(CEREAL_NVP(spin_speed)); }
  catch(const std::exception&){};
  try { archive(CEREAL_NVP(fire_interval)); }
  catch(const std::exception&){};
  //try { archive(CEREAL_NVP(gunner_mesh)); }
  //catch(const std::exception&){};
 };
 friend class cereal::access;
};
}
CEREAL_REGISTER_TYPE(villain::Gunner);