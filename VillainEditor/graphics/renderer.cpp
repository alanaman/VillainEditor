#include <glad/glad.h>
#include "renderer.hpp"
#include "renderer.hpp"
namespace villain {
Renderer::Renderer()
{
}

void Renderer::submitMesh(std::shared_ptr<Mesh> mesh)
{
 mMeshes.push_back(mesh);
 if(!mesh->isLoaded())
  mesh->loadMesh();
}

void Renderer::submitMeshes(std::vector<std::shared_ptr<Mesh>>& meshes)
{
 for (auto& mesh : meshes)
 {
  mMeshes.push_back(mesh);
  if(!mesh->isLoaded())
   mesh->loadMesh();
 }
}

void Renderer::submitCamera(std::shared_ptr<Camera> cam)
{
 mView_cam = cam;
}

void Renderer::clearAll()
{
 for (auto mesh : mMeshes)
  mesh->unLoadMesh();
 mMeshes.clear();
}

void Renderer::renderFrame()
{
 //TODO clean this up
 glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 ShaderLibrary::setCameraMatrix(mView_cam->getProjectionViewMatrix());
 for (int i=0;i<mMeshes.size();i++)
 {
  mMeshes[i]->draw();
 }
}
}