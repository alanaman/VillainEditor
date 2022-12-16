#include "assetlib.hpp"

namespace villain {
AssetLibrary::AssetLibrary()
 :
 mesh_list(MeshLibrary::getMeshListRef()),
 actor_list(ActorLibrary::actor_list())
{
}
void AssetLibrary::render()
{
 ImGui::Begin("AssetLib");

 ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_TabListPopupButton;
 if (ImGui::BeginTabBar("AssetType", tab_bar_flags))
 {
  if (ImGui::BeginTabItem("Meshes"))
  {
   for (int i = 0; i < mesh_list.size(); i++)
   {
    ImGui::Selectable(mesh_list[i].c_str());
    
    if (ImGui::BeginDragDropSource())
    {
     ImGui::SetDragDropPayload("ASSET_LIB_MESH", &i, sizeof(int));
     ImGui::Text(("Add static mesh: " + mesh_list[i]).c_str());
     ImGui::EndDragDropSource();
    }

    if (ImGui::BeginPopupContextItem())
    {
     //TODO
     if (ImGui::Selectable("Delete"))
      INFO("pressed delete on " << mesh_list[i]);
     ImGui::EndPopup();
    }
   }
   ImGui::EndTabItem();//meshes
  }

  if (ImGui::BeginTabItem("Actors"))
  {
   int i = 0;
   for (auto actor = actor_list.begin(); actor != actor_list.end(); actor++)
   {
    ImGui::Selectable(actor->first.c_str());
    
    if (ImGui::BeginDragDropSource())
    {
     ImGui::SetDragDropPayload("ASSET_LIB_ACTOR", &i, sizeof(int));
     ImGui::Text(("Add actor : " + actor->first).c_str());
     ImGui::EndDragDropSource();
    }

    if (ImGui::BeginPopupContextItem())
    {
     if (ImGui::Selectable("Delete"))
      INFO("pressed delete on " << actor->first);

     ImGui::EndPopup();
    }
    i++;
   }
   ImGui::EndTabItem();//actors
  }
  ImGui::EndTabBar();
 }

 ImGui::End();
}
}