#include "assetlib.hpp"

namespace villain {
AssetLibrary::AssetLibrary()
 :
 mesh_list(MeshLibrary::getEntriesRef()),
 actor_list(ActorLibrary::actor_list)
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
   renderMeshLib();
   ImGui::EndTabItem();
  }
  if (ImGui::BeginTabItem("Actors"))
  {
   renderActorLib();
   ImGui::EndTabItem();
  }
  if (ImGui::BeginTabItem("Materials"))
  {
   renderMaterialLib();
   ImGui::EndTabItem();
  }  
  if (ImGui::BeginTabItem("Shaders"))
  {
   renderShaderLib();
   ImGui::EndTabItem();
  }
  ImGui::EndTabBar();
 }

 ImGui::End();
}

void AssetLibrary::renderMeshLib()
{
 if (ImGui::Button("+##AddMeshToLib"))
  MeshLibrary::createMeshFromFile();
 for (auto& mesh:mesh_list)
 {
  if (ImGui::Selectable(mesh.second.name.c_str()))
  {
   PropertiesPanel::onMeshSelection(mesh.first);
  }

  if (ImGui::BeginDragDropSource())
  {
   ImGui::SetDragDropPayload("ASSET_LIB_MESH", &mesh.first, sizeof(int));
   ImGui::Text(("Add static mesh: " + mesh.second.name).c_str());
   ImGui::EndDragDropSource();
  }

  if (ImGui::BeginPopupContextItem())
  {
   //TODO
   if (ImGui::Selectable("Delete"))
    MeshLibrary::deleteMesh(mesh.first);
   ImGui::EndPopup();
  }
 }
}

void AssetLibrary::renderActorLib()
{
 int i = 0;
 for (int i=0;i<actor_list.size();i++)
 {
  ImGui::Selectable(actor_list[i].c_str());

  if (ImGui::BeginDragDropSource())
  {
   ImGui::SetDragDropPayload("ASSET_LIB_ACTOR", &i, sizeof(int));
   ImGui::Text(("Add actor : " + actor_list[i]).c_str());
   ImGui::EndDragDropSource();
  }

  if (ImGui::BeginPopupContextItem())
  {
   if (ImGui::Selectable("Delete"))
    INFO("pressed delete on " << actor_list[i]);

   ImGui::EndPopup();
  }
  i++;
 }
}

void AssetLibrary::renderMaterialLib()
{
 auto& materials = MaterialLibrary::materials;
 if (ImGui::Button("+"))
 {
  MaterialLibrary::addMaterial();
 }
 static int material_rename_id = -1;
 static char name[128];

 for (auto& mat:materials)
 {
  if (material_rename_id != mat.first)
  {
   if ( ImGui::Selectable(mat.second.getName().c_str()) )
   {
    PropertiesPanel::onMaterialSelection(mat.first);
   }
   if (ImGui::IsItemFocused() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
   {
    material_rename_id = mat.first;
    strcpy_s(name, mat.second.getName().c_str());
   }
   if (ImGui::BeginPopupContextItem())
   {
    if (ImGui::Selectable("Delete"))
    {
     //TODO
     INFO("delete: unimplemented");
    }
    ImGui::EndPopup();
   }
  }
  //renaming display
  else
  {
   ImGui::InputText("##shader_name", name, 128);
   ImGui::SetKeyboardFocusHere(-1);
   if (ImGui::IsItemDeactivated())
   {
    material_rename_id = -1;
    if (ImGui::IsItemDeactivatedAfterEdit())
     MaterialLibrary::renameMaterial(mat.first, name);
   }
  }//end renaming display
 }//end for loop
}

void AssetLibrary::renderShaderLib()
{
 auto& shaders = ShaderLibrary::shaders;
 for (int i = 0; i < shaders.size(); i++)
 {
  ImGui::Selectable(ShaderLibrary::shaders[i]->getName().c_str());
  if (ImGui::BeginPopupContextItem())
  {
   if (ImGui::Selectable("Create Material"))
   {
    MaterialLibrary::addMaterial(shaders[i]);
   }
   ImGui::EndPopup();
  }
 }

}


}