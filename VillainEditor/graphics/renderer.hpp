#include "logging.hpp"
#include "model.hpp"
#include "actor.hpp"
#include "camera.hpp"
#include "shader.hpp"

namespace villain{

class Renderer
{

 //std::vector<Mesh> m_meshes;
 std::vector<std::shared_ptr<Model>>& m_models;
 std::vector<std::shared_ptr<Actor>>& m_actors;
 std::vector<std::shared_ptr<Shader>>& m_shaders;

 std::shared_ptr<Camera> m_view_cam;
 
public:
 Renderer(
  std::vector<std::shared_ptr<Model>>& models,
  std::vector<std::shared_ptr<Actor>>& actors,
  std::vector<std::shared_ptr<Shader>>& shaders
 );

 void submitModel(Model& model);
 void submitCamera(std::shared_ptr<Camera> cam);
 //void addShaderFromFile(const std::string& vertexpath, const std::string& fragmentpath);


 void renderFrame();




};

}