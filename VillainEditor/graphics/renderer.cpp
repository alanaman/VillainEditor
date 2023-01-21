#include <glad/glad.h>
#include "renderer.hpp"
#include "renderer.hpp"
namespace villain {
Renderer::Renderer()
{
}

void Renderer::submitMesh(std::shared_ptr<Mesh>* mesh, std::shared_ptr<Entity> parent)
{
 if (mesh == NULL || parent == NULL)
  ERROR("invalid mesh / parent submitted");
 mMeshes.push_back(mesh);
 mParents.push_back(parent);
}

void Renderer::submitMeshes(std::vector<std::shared_ptr<Mesh>*>& meshes, std::shared_ptr<Entity> parent)
{
 for (auto& mesh : meshes)
  submitMesh(mesh, parent);
}

void Renderer::submitCamera(std::shared_ptr<Camera> cam)
{
 mView_cam = cam;
}

void Renderer::clearAll()
{
 for (auto mesh : mMeshes)
  (*mesh)->unLoadMesh();
 mMeshes.clear();
 mParents.clear();
 mView_cam = NULL;
}

void Renderer::renderFrame()
{
 //TODO clean this up
 glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 ShaderLibrary::setCameraMatrix(mView_cam->getProjectionViewMatrix());
 for (int i=0;i<mMeshes.size();i++)
 {
  (*mMeshes[i])->loadMesh();
  (*mMeshes[i])->draw(mParents[i]);
 }
}
}