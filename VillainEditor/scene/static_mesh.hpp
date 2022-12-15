
#include "entity.hpp"
#include "mesh.hpp"


namespace villain {

class StaticMesh : public Entity
{
 std::shared_ptr<Mesh> mesh=NULL;
 
 StaticMesh()=default;
public:
 StaticMesh(std::shared_ptr<Mesh>& mesh);
 StaticMesh(std::string name, std::shared_ptr<Mesh>& mesh);
 std::shared_ptr<Mesh> getMesh();


 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   cereal::base_class<Entity>(this),
   CEREAL_NVP(mesh)
   );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   cereal::base_class<Entity>(this),
   mesh
  );
 };
 friend class cereal::access;
};

}

CEREAL_REGISTER_TYPE(villain::StaticMesh);
//CEREAL_REGISTER_POLYMORPHIC_RELATION(villain::Entity, villain::StaticMesh);

