#include "assetlib.hpp"

namespace villain {
AssetLibrary::AssetLibrary()
 :mesh_list(MeshLibrary::getMeshListRef())
{
}
void AssetLibrary::render()
{
 ImGui::Begin("AssetLib");

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
   if (ImGui::Selectable("Delete"))
    INFO("pressed delete on " << mesh_list[i]);

   ImGui::EndPopup();
  }

 }

 ImGui::End();
}
}