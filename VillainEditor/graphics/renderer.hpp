#pragma once

#include "logging.hpp"
#include "mesh.hpp"
#include "scene/actor.hpp"
#include "scene/camera.hpp"
#include "shader.hpp"

#include "asset_library/material_library.hpp"

namespace villain{

class Renderer
{

 std::vector<std::shared_ptr<Mesh>> mMeshes;

 std::shared_ptr<Camera> mView_cam;
 
public:
 Renderer();

 void submitMesh(std::shared_ptr<Mesh> mesh);
 void submitMeshes(std::vector<std::shared_ptr<Mesh>>& meshes);
 void submitCamera(std::shared_ptr<Camera> cam);
 void clearAll();
 //void addShaderFromFile(const std::string& vertexpath, const std::string& fragmentpath);


 void renderFrame();




};

}