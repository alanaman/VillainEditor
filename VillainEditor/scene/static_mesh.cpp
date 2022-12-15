#include "static_mesh.hpp"


namespace villain {
StaticMesh::StaticMesh(std::shared_ptr<Mesh>& mesh)
 :mesh(mesh)
{
}
StaticMesh::StaticMesh(std::string name, std::shared_ptr<Mesh>& mesh)
 :mesh(mesh), Entity(name)
{
}
std::shared_ptr<Mesh> StaticMesh::getMesh()
{
 return mesh;
}
}