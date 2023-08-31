#pragma once
#include "logging.hpp"

namespace villain {

class MeshComponent
{
 int mesh_id;
 std::vector<int> material_ids;
public:

 MeshComponent(std::string path);
//#ifdef VILLAIN_EDITOR
// MeshComponent(int meshId);
//#else
//#endif // VILLAIN_EDITOR

 //TODO add cereal serialization

 friend class Mesh;
 friend class MeshOpengl;
 friend class MeshLibrary;
 friend class Renderer;
};
}