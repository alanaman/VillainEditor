#pragma once

#include "logging.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "collection.hpp"
#include "events.hpp"
#include "input.hpp"
#include "static_mesh.hpp"
#include "gunner.hpp"
#include "window/filedialog.hpp"



namespace villain {

class Scene
{
private:
 std::string m_name;
 std::vector<std::shared_ptr<StaticMesh>> mMeshes;
 std::vector<std::shared_ptr<Actor>> mActors;

 //std::shared_ptr<Entity> m_last_selected_entity = NULL;
 bool is_playing=false;
 
 Renderer mRenderer;
 std::shared_ptr<Camera> m_view_cam;

 std::string m_filename;
public:
 std::shared_ptr<Collection> root_collection;

 Scene(std::string name, int aspectX, int aspectY);
 void updateOnFrame();
 void addStaticMesh(std::shared_ptr<Mesh> mesh);
 void addActor(std::shared_ptr<Actor> actor);

 void startPlay();
 void stopPlay();

 void dispatchEvent(Event& e);
 void onResizeEvent(int width, int height);

 //std::shared_ptr<Entity> getLastSelectedEntity();
 //TODO
 void saveScene();
 void loadScene();

 friend class GuiLayer;
};
}