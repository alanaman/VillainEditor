#pragma once

#include "glad/glad.h"


#include "logging.hpp"

#include <string>
#include "graphics/mesh.hpp"
#include "asset_library/meshlibrary.hpp"
#include "asset_library/material_library.hpp"


namespace villain {

class MeshOpengl : public Mesh
{
private:

 struct MeshMemoryRef 
 {
  GLuint vao = -1;
  std::vector<GLuint> buffer_object_ids;
  unsigned long long n_indices = 0;
  MeshMemoryRef();
 };

 std::shared_ptr<std::vector<MeshMemoryRef>> mesh_ref = NULL;
 //for cereal
 MeshOpengl() {};
public:


 MeshOpengl(MeshId mesh_id);
 void loadMesh() override;
 virtual bool isLoaded() override;
 virtual void unLoadMesh() override;
 void draw(std::shared_ptr<Entity> parent) override;


 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   cereal::base_class<Mesh>(this)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   cereal::base_class<Mesh>(this)
  );
 };
 friend class cereal::access;
};
}
CEREAL_REGISTER_TYPE(villain::MeshOpengl);
