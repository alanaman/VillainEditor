#include "alternate_impl/mesh_component.hpp"
#include "editor_rep.hpp"

villain::MeshComponent::MeshComponent(std::string path)
{
 mesh_id = EditorRep::getMeshId(path);
}