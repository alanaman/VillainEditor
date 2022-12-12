#include <glad/glad.h>
#include "renderer.hpp"
namespace villain {
Renderer::Renderer(
 std::vector<std::shared_ptr<Model>>& models, 
 std::vector<std::shared_ptr<Actor>>& actors, 
 std::vector<std::shared_ptr<Shader>>& shaders
):
 m_models(models), m_actors(actors), m_shaders(shaders)
{
}
void Renderer::submitModel(Model& model)
{
 model.loadMesh();
}
void Renderer::submitCamera(std::shared_ptr<Camera> cam)
{
 m_view_cam = cam;
}
void Renderer::renderFrame()
{
 //TODO clean this up
 glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 for (auto& model : m_models)
 {
  auto shader = m_shaders[model->getShader()];
  shader->bind();
  shader->setUniformMat4("uTransform", model->getTransformMatrix());
  shader->setUniformMat4("uProjViewModelMat", m_view_cam->getProjectionViewMatrix());
  
  model->draw();
 }
 for (auto& actor : m_actors)
 {
  auto model = actor->getModel();
  auto shader = m_shaders[model->getShader()];
  shader->bind();
  shader->setUniformMat4("uTransform", actor->getTransformMatrix());
  shader->setUniformMat4("uProjViewModelMat", m_view_cam->getProjectionViewMatrix());
  
  model->draw();
 }
}
}