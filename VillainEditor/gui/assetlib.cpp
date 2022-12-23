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
  }  if (ImGui::BeginTabItem("Shaders"))
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
    MeshLibrary::deleteMesh(i);
   ImGui::EndPopup();
  }
 }
}

void AssetLibrary::renderActorLib()
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
}

void AssetLibrary::renderMaterialLib()
{
 auto& materials = MaterialLibrary::materials;
 if (ImGui::Button("+"))
 {
  MaterialLibrary::addMaterial(
   std::make_shared<Material>(std::string("Material"), ShaderLibrary::default_shader)
  );
 }
 static int material_rename_index = -1;
 static char name[128];

 for (int i = 0; i < materials.size(); i++)
 {
  if (material_rename_index != i)
  {
   ImGui::Selectable(materials[i]->name.c_str());
   if (ImGui::IsItemFocused() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
   {
    material_rename_index = i;
    strcpy_s(name, materials[i]->getName().c_str());
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
    material_rename_index = -1;
    if (ImGui::IsItemDeactivatedAfterEdit())
     materials[i]->setName(name);
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
    MaterialLibrary::addMaterial(
     std::make_shared<Material>(shaders[i]->getName() + "mat", shaders[i])
    );
   }
   ImGui::EndPopup();
  }
 }

}


}