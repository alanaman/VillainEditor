#pragma once

#include "logging.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "events.hpp"

#include <cereal/archives/binary.hpp>

namespace villain {


class Collection
{
 static int next_id;
public:
 int id;
 std::string name;

 bool is_selected = false;

 std::vector<std::shared_ptr<Collection>> child_collections;
 std::vector<std::shared_ptr<Entity>> child_entities;

 Collection();
 Collection(std::string name);
 void addCollection(std::shared_ptr<Collection> coll);
 void addEntity(std::shared_ptr<Entity> entt);
 bool isParentOf(std::shared_ptr<Collection> coll);
};





class Scene
{
private:
 std::string m_name;
 std::vector<std::shared_ptr<Model>> m_models;
 std::vector<std::shared_ptr<Shader>> m_shaders;

 //std::shared_ptr<Entity> m_last_selected_entity = NULL;

 std::shared_ptr<Collection> const m_collection;
 
 Renderer m_renderer;
 std::shared_ptr<Camera> m_view_cam;
public:
 Scene(std::string name, int aspectX, int aspectY);
 void updateOnFrame();
 void addModelFromFile();
 void addModel(std::shared_ptr<Model> model);

 void dispatchEvent(Event& e);

 //std::shared_ptr<Entity> getLastSelectedEntity();
 //TODO
 void saveScene();
 void loadScene();

 friend class GuiLayer;
};
}