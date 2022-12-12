#pragma once

#include "logging.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "collection.hpp"
#include "events.hpp"
#include "input.hpp"
#include "gunner.hpp"
#include "window/filedialog.hpp"

#include <cereal/archives/json.hpp>


namespace villain {

class Scene
{
private:
 std::string m_name;
 std::vector<std::shared_ptr<Model>> m_models;
 std::vector<std::shared_ptr<Actor>> m_actors;
 std::vector<std::shared_ptr<Shader>> m_shaders;

 //std::shared_ptr<Entity> m_last_selected_entity = NULL;
 bool is_playing=false;
 
 Renderer m_renderer;
 std::shared_ptr<Camera> m_view_cam;

 std::string m_filename;
public:
 std::shared_ptr<Collection> root_collection;

 Scene(std::string name, int aspectX, int aspectY);
 void updateOnFrame();
 void addModelFromFile();
 void addModel(std::shared_ptr<Model> model);

 void startPlay();
 void stopPlay();

 void dispatchEvent(Event& e);

 //std::shared_ptr<Entity> getLastSelectedEntity();
 //TODO
 void saveScene();
 void loadScene();

 friend class GuiLayer;
};
}