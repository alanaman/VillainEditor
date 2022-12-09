#include "scene.hpp"
#include "input.hpp"
#include "window/filedialog.hpp"

namespace villain {
Scene::Scene(std::string name, int aspectX, int aspectY) :
 m_name(name), m_renderer(m_models, m_shaders)
{
 m_view_cam = std::make_shared<Camera>(aspectX, aspectY);
 m_renderer.submitCamera(m_view_cam);

 m_shaders.push_back(Shader::create(
  "resources/shaders/basic_vertex2.glsl",
  "resources/shaders/basic_fragment2.glsl"));
 m_shaders.push_back(Shader::create(
  "resources/shaders/basic_vertex2.glsl",
  "resources/shaders/basic_fragment2.glsl"));
}
void Scene::updateOnFrame()
{
 m_view_cam->updateOnFrame();
 m_renderer.renderFrame();
}

void Scene::addModelFromFile()
{
 std::string filepath = FileBrowser::selectFile();
 if (filepath == "")
  return;
 auto model = Model::create(filepath);
 model->setShader(0);//default shader
 model->loadMesh();

 addModel(model);
}

void Scene::addModel(std::shared_ptr<Model> model)
{
 m_models.push_back(model);
 m_renderer.submitModel(*model);
}

void Scene::dispatchEvent(Event& e)
{
 switch (e.getEventType())
 {
 case EventType::KeyPress:
 {
  KeyPressEvent* ke = (KeyPressEvent*)&e;
  int key = ke->key;
  if (key == KEY::A && (e.mods & MOD::SHIFT))
   addModelFromFile();
  else if (key == KEY::S && (e.mods & MOD::CONTROL))
   saveScene();
  else if (key == KEY::L && (e.mods & MOD::CONTROL))
   loadScene();
  break;
 }
 default:
  break;
 }
 m_view_cam->eventHandler(e);
}

void Scene::saveScene()
{
 auto filepath = FileBrowser::saveFile();
 if (filepath == "")
  return;
 //TODO convert this to binary file
 std::ofstream file;
 file.open(filepath, std::ios::out);

 if (!file)
 {
  ERROR("Error in creating file!!!");
  return;
 }

 file << m_models.size() << std::endl;
 for (auto model : m_models)
 {
  file
   << model->m_path << " "
   << model->m_shader_index << " "
   << model->m_tranform << " "
   << std::endl;
 }
 file << m_shaders.size() << std::endl;
 for (auto shader : m_shaders)
 {
  file
   << shader->vertex_path << " "
   << shader->fragment_path << " "
   << std::endl;
 }
}

void Scene::loadScene()
{
 auto filepath = FileBrowser::selectFile();
 if (filepath == "")
  return;
 //TODO convert this to binary file
 std::ifstream file;
 file.open(filepath, std::ios::in);

 if (!file)
 {
  ERROR("Error in creating file!!!");
  return;
 }

 m_models.clear();
 m_shaders.clear();
 int num_models = 0, num_shaders = 0;
 file >> num_models;
 for (int i = 0; i < num_models; i++)
 {
  std::string filepath;
  file >> filepath;
  auto model = Model::create(filepath);
  model->setShader(0);//default shader
  model->loadMesh();

  addModel(model);

  file
   >> model->m_shader_index
   >> model->m_tranform;
 }

 file >> num_shaders;
 for (int i = 0; i < num_shaders; i++)
 {
  std::string vertex_path, fragmentpath;
  file
   >> vertex_path
   >> fragmentpath;
  m_shaders.push_back(Shader::create(vertex_path, fragmentpath));
 }
}

Model* Scene::getCurrentModel()
{
 if (m_models.size())
  return m_models[m_models.size() - 1].get();
 else
  return NULL;
}

}