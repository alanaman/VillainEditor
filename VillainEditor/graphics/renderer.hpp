#pragma once

#include "logging.hpp"
#include "mesh.hpp"
#include "actor.hpp"
#include "scene/camera.hpp"
#include "shader.hpp"

#include "asset_library/material_library.hpp"

namespace villain{

class Renderer
{

 std::vector<std::shared_ptr<Mesh>> mMeshes;
 std::vector<std::shared_ptr<Entity>> mParents;

 std::shared_ptr<Camera> mView_cam;
 
public:
 Renderer();

 void submitMesh(MeshComponent& meshComp, std::shared_ptr<Entity> parent);
 
 //TODO:this is only for submitting mesh from StaticMesh 
 //maybe change Static mesh to use MeshComponent
 void submitMesh(std::shared_ptr<Mesh> mesh, std::shared_ptr<Entity> parent);
 
 
 //void submitMeshes(std::vector<MeshComponent>& meshes, std::shared_ptr<Entity> parent);
 void submitCamera(std::shared_ptr<Camera> cam);
 void clearAll();
 //void addShaderFromFile(const std::string& vertexpath, const std::string& fragmentpath);


 void renderFrame();




};

}