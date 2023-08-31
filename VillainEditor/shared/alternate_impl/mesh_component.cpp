#include "mesh_component.hpp"
#include "asset_library/meshlibrary.hpp"

//ccorresponding dll implementation in mesh_component_dll.cpp

villain::MeshComponent::MeshComponent(std::string path)
{
 MeshLibrary::getId(path);
}

//villain::MeshComponent::MeshComponent(int meshId)
//{
// mesh_id = meshId;
//}
