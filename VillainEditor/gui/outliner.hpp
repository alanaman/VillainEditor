#include <imgui.h>

#include "scene.hpp"

namespace villain {

class Outliner
{
 std::shared_ptr<Collection> m_collection;

 ImGuiTreeNodeFlags m_base_flags;
 bool test_drag_and_drop = true;

 std::shared_ptr<Entity> m_selected_entity;
 std::shared_ptr<Collection> m_selected_collection;


 void renderCollection(std::shared_ptr<Collection> collection);
 void renderEntity(std::shared_ptr<Entity> entity);

public:
 Outliner();
 
 void render();
 void attachRootCollection(std::shared_ptr<Collection> collection);
 std::shared_ptr<Entity> getSelectedEntity();
 void deselect(std::shared_ptr<Collection> collection);
 void addCollection();
 std::shared_ptr<Collection> getCollectionFromId(int id, std::shared_ptr<Collection>& root);
 std::shared_ptr<Entity> getEntityFromId(int id, std::shared_ptr<Collection>& root);
 std::shared_ptr<Collection> getParentOfEntity(int id, std::shared_ptr<Collection>& root);
 bool removeCollection(std::shared_ptr<Collection>& coll, std::shared_ptr<Collection>& root);
 bool removeEntity(std::shared_ptr<Entity>& entt, std::shared_ptr<Collection>& root);
};

}