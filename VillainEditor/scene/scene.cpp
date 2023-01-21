#include "scene.hpp"
#include "VillainEditor.hpp"


namespace villain {



Scene::Scene(std::string name, int aspectX, int aspectY) :
 m_name(name), root_collection(std::make_shared<Collection>("Scene Collection"))
{
 Camera::setAspect(aspectX, aspectY);
 m_view_cam = std::make_shared<Camera>();


 mRenderer.submitCamera(m_view_cam);



 //addActor(std::make_shared<Gunner>(
 // "gun1", 
 // Mesh::create("resources/models/gunner.fbx"))
 //);
}
void Scene::updateOnFrame(const float& deltatime)
{
 m_view_cam->updateOnFrame(deltatime);
 if(is_playing)
  for (int i =0;i< mActors.size();i++)
   mActors[i]->updateOnFrame(deltatime);
 mRenderer.renderFrame();
}

std::shared_ptr<StaticMesh> Scene::addStaticMesh(const MeshId mesh_id)
{
 auto mesh = Mesh::create(mesh_id);
 auto static_mesh = StaticMesh::create("NewStaticMesh", mesh);
 mStaticMeshes.push_back(static_mesh);
 mRenderer.submitMesh(static_mesh->getMeshRef(), static_mesh);
 return static_mesh;
}

void Scene::addActor(std::shared_ptr<Actor> actor)
{
 mActors.push_back(actor);
 std::vector<std::shared_ptr<Mesh>*> meshes;
 actor->collectMeshes(meshes);
 mRenderer.submitMeshes(meshes, actor);
}

void Scene::startPlay()
{
 //TODO: create new scene for game
 saveScene();
 is_playing = true;
 for (auto& actor : mActors)
  actor->beginPlay();
}

bool Scene::isPlaying()
{
 return is_playing;
}

void Scene::stopPlay()
{
 is_playing = false;
 loadScene();
}

void Scene::eventHandler(Event& e)
{
 switch (e.getEventType())
 {
 case EventType::KeyPress:
 {
  KeyPressEvent* ke = (KeyPressEvent*)&e;
  int key = ke->key;
  //if (key == KEY::A && (e.mods & MOD::SHIFT))
  if (key == KEY::P && (e.mods & MOD::CONTROL))
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

void Scene::saveScene()
{
 if (isPlaying())
 {
  return;
 }
 if(m_filename=="")
  m_filename = FileBrowser::saveFile();
 if (m_filename == "")
  return;
 //TODO convert this to binary file
 std::ofstream file;
 file.open(m_filename, std::ios::out);
 cereal::JSONOutputArchive archive(file);
 
 archive(
  CEREAL_NVP(m_name),
  CEREAL_NVP(mStaticMeshes),
  CEREAL_NVP(mActors),
  CEREAL_NVP(root_collection),
  CEREAL_NVP(m_view_cam)
 );

}

void Scene::loadScene()
{
 if (isPlaying())
 {
  return;
 }
 if (m_filename == "")
  m_filename = FileBrowser::selectFile();
 if (m_filename == "")
  return;
 //TODO convert this to binary file
 std::ifstream file;
 file.open(m_filename, std::ios::in);

 cereal::JSONInputArchive archive(file);

 Collection::resetIdCount();
 archive(
  m_name,
  mStaticMeshes,
  mActors,
  root_collection,
  m_view_cam
 );
 mRenderer.clearAll();
 mRenderer.submitCamera(m_view_cam);
 for (auto& static_mesh : mStaticMeshes)
 {
  mRenderer.submitMesh(static_mesh->getMeshRef(), static_mesh);
 }
 for (auto& actor : mActors)
 {
  std::vector<std::shared_ptr<Mesh>*> meshes;
  actor->collectMeshes(meshes);
  mRenderer.submitMeshes(meshes, actor);
 }

 Editor::getEditorInstance()->onSceneReload();
}
}