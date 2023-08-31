#include "properties_gui.hpp"

namespace villain {

bool PropertiesPanel::show_properties_window = true;
Properties PropertiesPanel::m_properties;

std::shared_ptr<Entity> PropertiesPanel::selected_entity = NULL;
int PropertiesPanel::selected_material_id = -1;
int PropertiesPanel::selected_mesh_id = -1;
std::shared_ptr<Shader> PropertiesPanel::selected_shader = NULL;
std::vector<int> PropertiesPanel::mesh_def_mats;
bool PropertiesPanel::is_context_default = true;

void PropertiesPanel::onEntitySelection(std::shared_ptr<Entity> entity)
{
 clear();
 if (entity == NULL)
  return;
 selected_entity = entity;
 entity->collectProperties(PropertiesPanel::m_properties);
 is_context_default = false;
}

void PropertiesPanel::onMaterialSelection(int material_id)
{
 clear();
 is_context_default = false;
 selected_material_id = material_id;
 MaterialLibrary::getMaterial(material_id).collectProperties(m_properties);
}

void PropertiesPanel::clear()
{
 m_properties.clear();
 selected_entity = NULL;
 selected_material_id = -1;
 selected_mesh_id = -1;
 selected_shader = NULL;
 mesh_def_mats.clear();
}

void PropertiesPanel::onMeshSelection(int mesh_id)
{
 clear();
 is_context_default = true;
 selected_mesh_id = mesh_id;
 mesh_def_mats = MeshLibrary::getDefaultMaterialIds(mesh_id);
}

void PropertiesPanel::render()
{
 ImGui::Begin("Properties", &show_properties_window);

 if (is_context_default)
  renderDefaultProperties();
 else
  renderInstanceProperties();

 ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
 //ImGui::Text("%.5f   %.5f", ImGui::GetIO().DeltaTime, ImGui::GetIO().Framerate);
 ImGui::End();
}

void PropertiesPanel::renderInstanceProperties()
{
 auto& properties = m_properties.getPropertiesVector();

 for (int i = 0;i< properties.size();i++)
 {
  auto& property = properties[i];
  switch (property->getType())
  {
 
  case DataType::FLOAT:
   renderFloatProperty((Property<float>*)property);
   break;
  
  case DataType::INT:
   renderIntProperty((Property<int>*)property);
   break;
  
  case DataType::VEC3:
   renderVec3Property((Property<glm::vec3>*)property);
   break;
  
  case DataType::TRANSFORM:
   renderTransformProperty((Property<Transform>*)property);
   break;

  case DataType::MESH:
   renderMeshProperty((Property<std::shared_ptr<Mesh>>*)property);
  break;

  case DataType::SHADER:
   renderShaderProperty((Property<std::shared_ptr<Shader>>*)property);
  break;

  //case DataType::MATERIAL:
   //renderMaterialProperty((Property<std::shared_ptr<Material>>*)property);
   //break;
  
  default:
   VLLN_ERR("unimplemented type");
   break;
  }
 }//end for loop



}

void PropertiesPanel::renderDefaultProperties()
{
 if (selected_mesh_id == -1)
  return;

 renderDefaultMaterialProperty();
}

inline void PropertiesPanel::renderFloatProperty(Property<float>* prop)
{
 ImGui::DragFloat(
  prop->name.c_str(),
  &(prop->val)
 );
}

inline void PropertiesPanel::renderVec3Property(Property<glm::vec3>* prop)
{
 ImGui::DragFloat3(
  prop->name.c_str(),
  (float*)&(prop->val)
 );
}

inline void PropertiesPanel::renderIntProperty(Property<int>* prop)
{
 ImGui::DragInt(
  prop->name.c_str(),
  &(prop->val)
 );
}

inline void PropertiesPanel::renderTransformProperty(Property<Transform>* prop)
{
 auto& trans = prop->val;
 ImGui::DragFloat3(
  "Position",
  (float*)&(trans.getPositionRef())
 );
 ImGui::DragFloat3(
  "Rotation",
  (float*)&(trans.getRotationRef())
 );
 ImGui::DragFloat3(
  "Scale",
  (float*)&(trans.getScaleRef())
 );
}

inline void PropertiesPanel::renderMeshProperty(Property<std::shared_ptr<Mesh>>* prop)
{
 ImGui::Text("Mesh");
 auto& meshes = MeshLibrary::getEntriesRef();
 if (
  ImGui::BeginCombo(
   "##Mesh",
   MeshLibrary::getEntriesRef()[prop->val->getId()].name.c_str(),
   ImGuiComboFlags_PopupAlignLeft
  ))
 {
  for (auto& mesh:meshes)
  {
   const bool is_selected = (mesh.first == prop->val->getId());
   if (ImGui::Selectable(mesh.second.name.c_str(), is_selected))
   {
    prop->val = Mesh::create(mesh.first);
   }

   // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
   if (is_selected)
    ImGui::SetItemDefaultFocus();
  }
  ImGui::EndCombo();
 }

 ImGui::SameLine(0.0f, -1.0f);

 if (ImGui::Button("\u02C5Mat\u02C5"))
  ImGui::OpenPopup("Material_edit_popup");
 if (ImGui::BeginPopup("Material_edit_popup"))
 {
  auto n_slots = prop->val->getNumMaterialSlots();
  int n_mats = MaterialLibrary::getNumMaterials();
  for (int slot_index = 0; slot_index < n_slots; slot_index++)
  {
   auto current_mat_id = prop->val->getMaterialId(slot_index);
   if (
    ImGui::BeginCombo(
     "Material",
     MaterialLibrary::getMaterial(current_mat_id).getName().c_str(),
     ImGuiComboFlags_PopupAlignLeft
    ))
   {
    for (auto& mat:MaterialLibrary::materials)
    {
     const bool is_selected = (mat.first == current_mat_id);
     if (ImGui::Selectable(mat.second.getName().c_str(), is_selected))
     {
      prop->val->setMaterial(slot_index, mat.first);
     }

     // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
     if (is_selected)
      ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
   }
  }
  ImGui::EndPopup();
 }

 //Materials




}

inline void PropertiesPanel::renderShaderProperty(Property<std::shared_ptr<Shader>>* prop)
{
 
 int n_shaders = ShaderLibrary::getNumShaders();

 if (
  ImGui::BeginCombo(
   "Shader",
   prop->val->getName().c_str(),
   ImGuiComboFlags_PopupAlignLeft
  ))
 {
  for (int n = 0; n < n_shaders; n++)
  {
   auto shader = ShaderLibrary::getShaderByIndex(n);
   const bool is_selected = (shader == prop->val);
   if (ImGui::Selectable(shader->getName().c_str(), is_selected))
   {
    MaterialLibrary::getMaterial(selected_material_id).setShader(shader);
    PropertiesPanel::onMaterialSelection(selected_material_id);
    //prop changed
    //dont render rest of shaders
    break;
   }

   // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
   if (is_selected)
    ImGui::SetItemDefaultFocus();
  }
  ImGui::EndCombo();
 }
}

inline void PropertiesPanel::renderDefaultMaterialProperty()
{
 auto n_slots = mesh_def_mats.size();
 int n_mats = MaterialLibrary::getNumMaterials();
 for (int slot_index = 0; slot_index < n_slots; slot_index++)
 {
  auto current_mat_id = mesh_def_mats[slot_index];
  if (
   ImGui::BeginCombo(
    "Material",
    MaterialLibrary::getMaterial(current_mat_id).getName().c_str(),
    ImGuiComboFlags_PopupAlignLeft
   ))
  {
   for (auto& mat : MaterialLibrary::materials)
   {
    const bool is_selected = (mat.first == current_mat_id);
    if (ImGui::Selectable(mat.second.getName().c_str(), is_selected))
    {
     mesh_def_mats[slot_index]= mat.first;
     MeshLibrary::updateDefaultMaterialIds(selected_mesh_id, mesh_def_mats);
    }

    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
    if (is_selected)
     ImGui::SetItemDefaultFocus();
   }
   ImGui::EndCombo();
  }
 }
}



}//end namespace