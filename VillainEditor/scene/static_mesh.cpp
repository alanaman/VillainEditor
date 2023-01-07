#include "static_mesh.hpp"


namespace villain {
StaticMesh::StaticMesh(std::shared_ptr<Mesh>& mesh)
 :m_mesh(mesh)
{
}
StaticMesh::StaticMesh(std::string& name, std::shared_ptr<Mesh>& mesh)
 :m_mesh(mesh), Entity(name)
{
}
std::shared_ptr<StaticMesh> StaticMesh::create(std::shared_ptr<Mesh>& mesh)
{
 auto ptr = std::make_shared<StaticMesh>(mesh);
 ptr->m_mesh->setParent(ptr);
 return ptr;
}
std::shared_ptr<StaticMesh> StaticMesh::create(std::string name, std::shared_ptr<Mesh>& mesh)
{
 auto ptr = std::make_shared<StaticMesh>(name, mesh);
 ptr->m_mesh->setParent(ptr);
 return ptr;
}
std::shared_ptr<Mesh> StaticMesh::getMesh()
{
 return m_mesh;
}
void StaticMesh::collectProperties(Properties& properties)
{
 this->Entity::collectProperties(properties);

}
}