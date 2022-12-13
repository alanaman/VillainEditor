#include "scene.hpp"


namespace villain {

int Collection::next_id = 0;


Scene::Scene(std::string name, int aspectX, int aspectY) :
 m_name(name), root_collection(std::make_shared<Collection>("Scene Collection"))
{
 Camera::setAspect(aspectX, aspectY);
 m_view_cam = std::make_shared<Camera>();


 mRenderer.submitCamera(m_view_cam);



 addActor(std::make_shared<Gunner>(
  "gun1", 
  Mesh::create("resources/models/gunner.fbx"))
 );
}
void Scene::updateOnFrame()
{
 m_view_cam->updateOnFrame();
 if(is_playing)
  for (auto& actor : mActors)
   actor->updateOnFrame();
 mRenderer.renderFrame();
}

void Scene::addMeshFromFile()
{
 std::string filepath = FileBrowser::selectFile();
 if (filepath == "")
  return;
 auto mesh = Mesh::create(filepath);
 mesh->setShader(0);//default shader

 addMesh(mesh);
}

void Scene::addMesh(std::shared_ptr<Mesh> mesh)
{
 auto static_mesh = std::make_shared<StaticMesh>(mesh);
 mMeshes.push_back(static_mesh);
 mRenderer.submitMesh(mesh, &(static_mesh->getTransformRef()));
 root_collection->addEntity(static_mesh);
}

void Scene::addActor(std::shared_ptr<Actor> actor)
{
 mActors.push_back(actor);
 mRenderer.submitMesh(actor->getMesh(), &(actor->getTransformRef()));
}

void Scene::startPlay()
{
 is_playing = true;
 for (auto& actor : mActors)
  actor->beginPlay();
}

void Scene::stopPlay()
{
 is_playing = false;
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
   addMeshFromFile();
  else if (key == KEY::S && (e.mods & MOD::CONTROL))
   saveScene();
  else if (key == KEY::L && (e.mods & MOD::CONTROL))
   loadScene();
  else if (key == KEY::P && (e.mods & MOD::CONTROL))
  {
   if (is_playing)
    stopPlay();
   else
    startPlay();
  }
  break;
 }
 default:
  break;
 }
 m_view_cam->eventHandler(e);
}

void Scene::onResizeEvent(int width, int height)
{
 Camera::setAspect(width, height);

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
//  addMesh(model);
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