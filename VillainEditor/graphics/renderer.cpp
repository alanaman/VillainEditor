#include <glad/glad.h>
#include "renderer.hpp"
namespace villain {
Renderer::Renderer(
 std::vector<std::shared_ptr<Model>>& m_models, 
 std::vector<std::shared_ptr<Shader>>& m_shaders
):
 m_models(m_models), m_shaders(m_shaders)
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
}
}