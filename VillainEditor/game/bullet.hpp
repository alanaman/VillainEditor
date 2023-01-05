#pragma once

#include "asset_library/actor_library.hpp"
#include "asset_library/meshlibrary.hpp"
#include "logging.hpp"
#include "scene/actor.hpp"
#include "graphics/mesh.hpp"

namespace villain {


class Bullet : public Actor
{
private:
 static std::shared_ptr<Mesh> bullet_mesh;

 float speed = 7.0f;
 glm::vec3 direction = glm::vec3(0, 1, 0);


 Bullet() {}; //for cereal
public:
 static std::shared_ptr<Actor> create();

 Bullet(std::string name);
 virtual void beginPlay() override;
 virtual void updateOnFrame(const float& deltatime) override;



 virtual void collectMeshes(std::vector<std::shared_ptr<Mesh>>& meshes) override;

 virtual void collectProperties(Properties& properties) override;
 
 void setSpeed(float speed);
 void setDirection(glm::vec3 direction);


 template<class Archive>
 void save(Archive& archive) const
 {
  archive(cereal::base_class<Actor>(this));
  archive(CEREAL_NVP(speed));
  archive(CEREAL_NVP(direction));

 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(cereal::base_class<Actor>(this));
  try { archive(CEREAL_NVP(speed)); }
  catch(const std::exception&){};
  try { archive(CEREAL_NVP(direction)); }
  catch(const std::exception&){};
 };
 friend class cereal::access;
};
}
CEREAL_REGISTER_TYPE(villain::Bullet);