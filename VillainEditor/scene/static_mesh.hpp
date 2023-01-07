#pragma once

#include "entity.hpp"
#include "graphics/mesh.hpp"


namespace villain {

class StaticMesh : public Entity
{
 std::shared_ptr<Mesh> m_mesh=NULL;
 
 StaticMesh()=default;
public:
 //do not call these constructors directly!! use create
 // TODO: fix access : https://stackoverflow.com/questions/8147027/how-do-i-call-stdmake-shared-on-a-class-with-only-protected-or-private-const
 StaticMesh(std::shared_ptr<Mesh>& mesh);
 StaticMesh(std::string& name, std::shared_ptr<Mesh>& mesh);

 StaticMesh(const StaticMesh&) = delete;
 const StaticMesh& operator=(const StaticMesh&) = delete;
 
 static std::shared_ptr<StaticMesh> create(std::shared_ptr<Mesh>& mesh);
 static std::shared_ptr<StaticMesh> create(std::string name, std::shared_ptr<Mesh>& mesh);

 std::shared_ptr<Mesh> getMesh();
 virtual void collectProperties(Properties& properties) override;

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   cereal::base_class<Entity>(this),
   CEREAL_NVP(m_mesh)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   cereal::base_class<Entity>(this),
   m_mesh
  );
 };
 friend class cereal::access;
};

}

CEREAL_REGISTER_TYPE(villain::StaticMesh);
//CEREAL_REGISTER_POLYMORPHIC_RELATION(villain::Entity, villain::StaticMesh);

