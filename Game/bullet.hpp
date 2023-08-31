#pragma once

#include "logging.hpp"
#include "actor.hpp"

namespace villain {


class Bullet : public Actor
{
private:
 MeshComponent bullet_mesh = MeshComponent("bullet");

 float speed = 7.0f;
 glm::vec3 direction = glm::vec3(0, 1, 0);


 Bullet() {}; //for cereal
public:
 static Actor* create();
 //TODO const ref
 Bullet(std::string name);
 virtual void beginPlay() override;
 virtual void updateOnFrame(const float& deltatime) override;



 virtual void collectMeshes(std::vector<MeshComponent*>& meshes) override;

 virtual void collectProperties(Properties& properties) override;

 void setSpeed(float speed);
 void setDirection(glm::vec3 direction);


 template<class Archive>
 void save(Archive& archive) const
 {
  archive(cereal::base_class<Actor>(this));
  archive(CEREAL_NVP(speed));
  archive(CEREAL_NVP(direction));
  //archive(CEREAL_NVP(bullet_mesh));

 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(cereal::base_class<Actor>(this));
  try { archive(CEREAL_NVP(speed)); }
  catch (const std::exception&) {};
  try { archive(CEREAL_NVP(direction)); }
  catch (const std::exception&) {};
  //try { archive(CEREAL_NVP(bullet_mesh)); }
  //catch(const std::exception&){};
 };
 friend class cereal::access;
};
}
