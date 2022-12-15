#pragma once

#include "logging.hpp"
#include "mesh.hpp"
#include "actor.hpp"
#include "camera.hpp"
#include "shader.hpp"

namespace villain{

class Renderer
{

 std::vector<std::shared_ptr<Mesh>> mMeshes;
 std::vector<Transform*> mTransforms;
 std::vector<std::shared_ptr<Shader>> mShaders;

 std::shared_ptr<Camera> mView_cam;
 
public:
 Renderer();

 void submitMesh(std::shared_ptr<Mesh> mesh, Transform* transform);
 void submitCamera(std::shared_ptr<Camera> cam);
 void clearAll();
 //void addShaderFromFile(const std::string& vertexpath, const std::string& fragmentpath);


 void renderFrame();




};

}