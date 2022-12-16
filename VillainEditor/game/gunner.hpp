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

 Gunner() {}; //for cereal
public:
 static std::shared_ptr<Actor> create();

 Gunner(std::string name);
 virtual void beginPlay() override;
 virtual void updateOnFrame() override;



 virtual void getMesh(std::vector<std::shared_ptr<Mesh>>& meshes) override;

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   cereal::base_class<Actor>(this),
   CEREAL_NVP(gunner_mesh)
   );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   cereal::base_class<Actor>(this),
   gunner_mesh
   );
 };
 friend class cereal::access;
};
}
CEREAL_REGISTER_TYPE(villain::Gunner);