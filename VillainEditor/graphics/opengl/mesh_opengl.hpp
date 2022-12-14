#pragma once

#include "glad/glad.h"


#include "logging.hpp"

#include <glad/glad.h>
#include <string>
#include "mesh.hpp"
#include "asset_library/meshlibrary.hpp"


namespace villain {

class MeshOpengl : public Mesh
{
private:

 struct MeshMemoryRef 
 {
  GLuint vao = -1;
  std::vector<GLuint> buffer_object_ids;
  unsigned long long n_indices = 0;
 };

 std::shared_ptr<MeshMemoryRef> mesh_ref;
public:


 MeshOpengl(const std::string& name);
 void loadMesh() override;
 virtual bool isLoaded() override;
 virtual void unLoadMesh() override;
 void draw() override;
};
}