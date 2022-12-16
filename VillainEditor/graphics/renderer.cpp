#include "renderer.hpp"
#include "renderer.hpp"
#include <glad/glad.h>
#include "renderer.hpp"
namespace villain {
Renderer::Renderer()
{
 mShaders.push_back(Shader::create(
  "resources/shaders/basic_vertex.glsl",
  "resources/shaders/basic_fragment.glsl"));
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
 for (int i = 1; i < mShaders.size(); i++)
 {
  //TODO: remove shader from memory
 }
 auto default_shader = mShaders[0];
 mShaders = std::vector<std::shared_ptr<Shader>>();
 mShaders.push_back(default_shader);

 mMeshes.clear();
}

void Renderer::renderFrame()
{
 //TODO clean this up
 glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 for (int i=0;i<mMeshes.size();i++)
 {
  auto& shader = mShaders[mMeshes[i]->getShader()];
  shader->bind();
  shader->setUniformMat4("uTransform", mMeshes[i]->getTransformMatrix());
  shader->setUniformMat4("uProjViewModelMat", mView_cam->getProjectionViewMatrix());
  
  mMeshes[i]->draw();
 }
 //for (auto& actor : mActors)
 //{
 // auto model = actor->getModel();
 // auto shader = mShaders[model->getShader()];
 // shader->bind();
 // shader->setUniformMat4("uTransform", actor->getTransformMatrix());
 // shader->setUniformMat4("uProjViewModelMat", m_view_cam->getProjectionViewMatrix());
 // 
 // model->draw();
 //}
}
}