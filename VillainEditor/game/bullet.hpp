#pragma once

#include "actor_library.hpp"
#include "meshlibrary.hpp"
#include "logging.hpp"
#include "actor.hpp"
#include "mesh.hpp"

namespace villain {


class Bullet : public Actor
{
private:
 std::shared_ptr<Mesh> bullet_mesh;
 Properties props;

 static const std::vector<std::shared_ptr<PropDef>> default_properties;

 Bullet() {}; //for cereal
public:
 static std::shared_ptr<Actor> create();

 Bullet(std::string name);
 virtual void beginPlay() override;
 virtual void updateOnFrame(const float& deltatime) override;



 virtual void collectMeshes(std::vector<std::shared_ptr<Mesh>>& meshes) override;

 virtual void collectProperties(std::vector<std::shared_ptr<Property>>& properties) override;
 virtual void setProperty(std::string name, glm::vec3 val) override;


 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   cereal::base_class<Actor>(this),
   CEREAL_NVP(bullet_mesh),
   CEREAL_NVP(props)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   cereal::base_class<Actor>(this),
   bullet_mesh,
   props
  );
  props.resolveProperties(default_properties);
 };
 friend class cereal::access;
};
}
CEREAL_REGISTER_TYPE(villain::Bullet);