#pragma once

#include "logging.hpp"
#include "graphics/mesh.hpp"
#include "camera.hpp"
#include "graphics/renderer.hpp"
#include "collection.hpp"
#include "events.hpp"
#include "input.hpp"
#include "static_mesh.hpp"
#include "window/filedialog.hpp"



namespace villain {

class Scene
{
private:
 std::string m_name;
 std::vector<std::shared_ptr<StaticMesh>> mStaticMeshes;
 std::vector<std::shared_ptr<Actor>> mActors;

 //std::shared_ptr<Entity> m_last_selected_entity = NULL;
 bool is_playing=false;
 
 Renderer mRenderer;
 std::shared_ptr<Camera> m_view_cam;

 std::string m_filename;
public:
 std::shared_ptr<Collection> root_collection;

 Scene(std::string name, int aspectX, int aspectY);
 void updateOnFrame(const float& deltatime);
 std::shared_ptr<StaticMesh> addStaticMesh(const std::string& name);
 void addActor(std::shared_ptr<Actor> actor);

 void startPlay();
 bool isPlaying();
 void stopPlay();

 void eventHandler(Event& e);
 void onResizeEvent(int width, int height);

 //std::shared_ptr<Entity> getLastSelectedEntity();
 //TODO
 void saveScene();
 void loadScene();

 friend class GuiLayer;
};
}