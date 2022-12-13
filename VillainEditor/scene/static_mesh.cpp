#include "static_mesh.hpp"

namespace villain {
StaticMesh::StaticMesh(std::shared_ptr<Mesh>& mesh)
 :mesh(mesh)
{
}
std::shared_ptr<Mesh> StaticMesh::getModel()
{
 return mesh;
}
}