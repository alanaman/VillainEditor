#include "outliner.hpp"

namespace villain {


static void HelpMarker(const char* desc)
{
 ImGui::TextDisabled("(?)");
 if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
 {
  ImGui::BeginTooltip();
  ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
  ImGui::TextUnformatted(desc);
  ImGui::PopTextWrapPos();
  ImGui::EndTooltip();
 }
}

villain::Outliner::Outliner(Scene*& scene)
 :m_scene(scene)
{
 m_base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

}

void Outliner::render()
{
 ImGui::Begin("Outliner");
 
 //HelpMarker(
 // "This is a more typical looking tree with selectable nodes.\n"
 // "Click to select, CTRL+Click to toggle, click on arrows or double-click to open.");
 static bool align_label_with_current_x_position = true;
 //ImGui::CheckboxFlags("ImGuiTreeNodeFlags_OpenOnArrow", &m_base_flags, ImGuiTreeNodeFlags_OpenOnArrow);
 //ImGui::CheckboxFlags("ImGuiTreeNodeFlags_OpenOnDoubleClick", &m_base_flags, ImGuiTreeNodeFlags_OpenOnDoubleClick);
 //ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanAvailWidth", &m_base_flags, ImGuiTreeNodeFlags_SpanAvailWidth); ImGui::SameLine(); HelpMarker("Extend hit area to all available width instead of allowing more items to be laid out after the node.");
 //ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanFullWidth", &m_base_flags, ImGuiTreeNodeFlags_SpanFullWidth);
 //ImGui::Checkbox("Align label with current X position", &align_label_with_current_x_position);
 //ImGui::Checkbox("Test tree node as drag source", &test_drag_and_drop);
 //ImGui::Text("Hello!");
 if (ImGui::Button("+"))
  addCollection();
 
 ImGui::Separator();
 if (align_label_with_current_x_position)
  ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

 renderCollection(m_scene->root_collection);
 
 if (align_label_with_current_x_position)
  ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());

 ImGui::End();
}

void villain::Outliner::renderCollection(std::shared_ptr<Collection> collection)
{
 ImGuiTreeNodeFlags node_flags = m_base_flags;
 if (collection->is_selected)
  node_flags |= ImGuiTreeNodeFlags_Selected;
 bool node_open = ImGui::TreeNodeEx(collection->name.data(), node_flags);
 if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
 {
  deselect(m_scene->root_collection);
  collection->is_selected = true;
  m_selected_entity = NULL;
  m_selected_collection = collection;

  PropertiesPanel::onEntitySelection(NULL);
 }
 if (test_drag_and_drop && ImGui::BeginDragDropSource())
 {
  ImGui::SetDragDropPayload("OUTLINER_COLLECTION", &collection->id, sizeof(int));
  ImGui::Text(collection->name.data());
  ImGui::EndDragDropSource();
 }
 if (ImGui::BeginDragDropTarget())
 {
  if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("OUTLINER_COLLECTION"))
  {
   IM_ASSERT(payload->DataSize == sizeof(int));
   int id = *(const int*)payload->Data;
   auto coll_to_be_dropped = getCollectionFromId(id, m_scene->root_collection);

   if (!coll_to_be_dropped->isParentOf(collection))
   {
    //remove from current parent
    assert(removeCollection(coll_to_be_dropped, m_scene->root_collection));
    //add to collection->child_collections
    collection->addCollection(coll_to_be_dropped);
   }
  }
  if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("OUTLINER_ENTITY"))
  {
   IM_ASSERT(payload->DataSize == sizeof(int));
   int id = *(const int*)payload->Data;
   auto entt_to_be_dropped = getEntityFromId(id, m_scene->root_collection);

   assert(removeEntity(entt_to_be_dropped, m_scene->root_collection));
   collection->addEntity(entt_to_be_dropped);
  }

  if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_LIB_MESH"))
  {
   IM_ASSERT(payload->DataSize == sizeof(int));
   int index = *(const int*)payload->Data;

   auto entity = m_scene->addStaticMesh(MeshLibrary::getMeshListRef()[index]);
   collection->addEntity(entity);
  }
  if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_LIB_ACTOR"))
  {
   IM_ASSERT(payload->DataSize == sizeof(int));
   int index = *(const int*)payload->Data;
   auto actor = ActorLibrary::instantiate(index);
   m_scene->addActor(actor);
   collection->addEntity(actor);
  }
  ImGui::EndDragDropTarget();
 }
 if (node_open)
 {
  //ImGui::TreePush(collection->name.data());
  for (int i = 0; i < collection->child_collections.size(); i++)
   renderCollection(collection->child_collections[i]);
  for (int i = 0; i < collection->child_entities.size(); i++)
   renderEntity(collection->child_entities[i]);
  //if (collection->child_collections.size() || collection->child_entities.size())
  ImGui::TreePop();
 }
}

void Outliner::renderEntity(std::shared_ptr<Entity> entity)
{
 ImGuiTreeNodeFlags node_flags = m_base_flags;
 node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
 if (entity->is_selected)
  node_flags |= ImGuiTreeNodeFlags_Selected; 
 ImGui::TreeNodeEx(entity->name.data(), node_flags);
 if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
 {
  deselect(m_scene->root_collection);
  entity->is_selected = true;
  m_selected_collection = NULL;
  m_selected_entity = entity;
 }
 if (test_drag_and_drop && ImGui::BeginDragDropSource())
 {
  ImGui::SetDragDropPayload("OUTLINER_ENTITY", &entity->id, sizeof(int));
  ImGui::Text(entity->name.data());
  ImGui::EndDragDropSource();
 }
}
std::shared_ptr<Entity> villain::Outliner::getSelectedEntity()
{
 return m_selected_entity;
}

void villain::Outliner::deselect(std::shared_ptr<Collection> collection)
{
 collection->is_selected = false;
 for (auto& child : collection->child_collections)
  deselect(child);
 for (auto& child : collection->child_entities)
  child->is_selected = false;
}

std::shared_ptr<Collection> Outliner::getCollectionFromId(int id, std::shared_ptr<Collection>& root)
{
 if (root->id == id)
  return root;
 for (auto& child : root->child_collections)
 {
  auto coll = getCollectionFromId(id, child);
  if (coll != NULL)
   return coll;
 }
 return NULL;
}

std::shared_ptr<Entity> Outliner::getEntityFromId(int id, std::shared_ptr<Collection>& root)
{
 for (auto& child : root->child_entities)
 {
  if (child->id == id)
   return child;
 }
 for (auto& child : root->child_collections)
 {
  auto entt = getEntityFromId(id, child);
  if (entt != NULL)
   return entt;
 }
 return NULL;
}

std::shared_ptr<Collection> Outliner::getParentOfEntity(int id, std::shared_ptr<Collection>& root)
{
 for (auto& child : root->child_entities)
 {
  if (child->id == id)
  {
   return root;
  }
 }
 for (auto& child : root->child_collections)
 {
  auto parent = getParentOfEntity(id, child);
  if (parent != NULL)
   return parent;
 }
 return NULL;
}

bool Outliner::removeCollection(std::shared_ptr<Collection>& coll, std::shared_ptr<Collection>& root)
{
 auto& children = root->child_collections;
 for (int i=0;i<children.size();i++)
 {
  if (children[i] == coll)
  {
   children.erase(children.begin() + i);
   return true;
  }
  if(removeCollection(coll, children[i]))
   return true;
 }
 return false;
}

bool Outliner::removeEntity(std::shared_ptr<Entity>& entt, std::shared_ptr<Collection>& root)
{
 auto& children = root->child_entities;
 for (int i=0;i<children.size();i++)
 {
  if (children[i] == entt)
  {
   children.erase(children.begin() + i);
   return true;
  }
 }
 for (auto &child : root->child_collections)
 {
  if (removeEntity(entt, child))
   return true;
 }
 return false;
}

void Outliner::onSceneReload()
{
 deselect(m_scene->root_collection);
 m_selected_entity = NULL;
 m_selected_collection = NULL;
}

void Outliner::addCollection()
{
 m_scene->root_collection->addCollection(std::make_shared<Collection>());
}

}