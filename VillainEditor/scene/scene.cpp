#include "scene.hpp"


namespace villain {

int Collection::next_id = 0;


Scene::Scene(std::string name, int aspectX, int aspectY) :
 m_name(name), m_renderer(m_models, m_shaders), root_collection(std::make_shared<Collection>("Scene Collection"))
{

 m_view_cam = std::make_shared<Camera>(aspectX, aspectY);
 m_renderer.submitCamera(m_view_cam);

 m_shaders.push_back(Shader::create(
  "resources/shaders/basic_vertex.glsl",
  "resources/shaders/basic_fragment.glsl"));
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
 root_collection->addEntity(model);
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

//void Scene::saveScene()
//{
// auto filepath = FileBrowser::saveFile();
// if (filepath == "")
//  return;
// //TODO convert this to binary file
// std::ofstream file;
// file.open(filepath, std::ios::out);
//
// if (!file)
// {
//  ERROR("Error in creating file!!!");
//  return;
// }
//
// file << m_models.size() << std::endl;
// for (auto& model : m_models)
// {
//  file
//   << model->m_path << " "
//   << model->m_shader_index << " "
//   << model->m_transform << " "
//   << std::endl;
// }
// file << m_shaders.size() << std::endl;
// for (auto& shader : m_shaders)
// {
//  file
//   << shader->vertex_path << " "
//   << shader->fragment_path << " "
//   << std::endl;
// }
//}
//
//void Scene::loadScene()
//{
// auto filepath = FileBrowser::selectFile();
// if (filepath == "")
//  return;
// //TODO convert this to binary file
// std::ifstream file;
// file.open(filepath, std::ios::in);
//
// if (!file)
// {
//  ERROR("Error in creating file!!!");
//  return;
// }
//
// m_models.clear();
// m_shaders.clear();
// int num_models = 0, num_shaders = 0;
// file >> num_models;
// for (int i = 0; i < num_models; i++)
// {
//  std::string filepath;
//  file >> filepath;
//  auto model = Model::create(filepath);
//  model->setShader(0);//default shader
//  model->loadMesh();
//
//  addModel(model);
//
//  file
//   >> model->m_shader_index
//   >> model->m_transform;
// }
//
// file >> num_shaders;
// for (int i = 0; i < num_shaders; i++)
// {
//  std::string vertex_path, fragmentpath;
//  file
//   >> vertex_path
//   >> fragmentpath;
//  m_shaders.push_back(Shader::create(vertex_path, fragmentpath));
// }
//}

//std::shared_ptr<Entity> villain::Scene::getLastSelectedEntity()
//{
// return m_last_selected_entity;
//}




void Scene::saveScene()
{


 if(m_filename=="")
  m_filename = FileBrowser::saveFile();
 if (m_filename == "")
  return;
 //TODO convert this to binary file
 std::ofstream file;
 file.open(m_filename, std::ios::out);
 cereal::JSONOutputArchive archive(file);
 
 archive(root_collection);

}

void Scene::loadScene()
{
 if (m_filename == "")
  m_filename = FileBrowser::selectFile();
 if (m_filename == "")
  return;
 //TODO convert this to binary file
 std::ifstream file;
 file.open(m_filename, std::ios::in);

 cereal::JSONInputArchive archive(file);

 Collection::resetIdCount();
 archive(root_collection);

}
}