#include "properties_gui.hpp"

namespace villain {

bool PropertiesPanel::show_properties_window = true;
Properties PropertiesPanel::m_properties;

std::shared_ptr<Entity> PropertiesPanel::selected_entity = NULL;
std::shared_ptr<Material> PropertiesPanel::selected_material = NULL;
std::shared_ptr<Shader> PropertiesPanel::selected_shader = NULL;

void PropertiesPanel::onEntitySelection(std::shared_ptr<Entity> entity)
{
 PropertiesPanel::m_properties.clear();
 if (entity == NULL)
  return;
 selected_entity = entity;
 selected_material = NULL;
 selected_shader = NULL;
 entity->collectProperties(PropertiesPanel::m_properties);
}

void PropertiesPanel::onMaterialSelection(std::shared_ptr<Material> material)
{
 m_properties.clear();
 if (material == NULL)
 {
  return;
 }
 selected_entity = NULL;
 selected_material = material;
 selected_shader = NULL;
 material->collectProperties(m_properties);
}

void PropertiesPanel::render()
{
 ImGui::Begin("Properties", &show_properties_window);
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

  case DataType::SHADER:
   renderShaderProperty((Property<std::shared_ptr<Shader>>*)property);
  break;

  case DataType::MATERIAL:
   renderMaterialProperty((Property<std::shared_ptr<Material>>*)property);
   break;
  
  default:
   ERROR("unimplemented type");
   break;
  }
 }//end for loop


 ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
 //ImGui::Text("%.5f   %.5f", ImGui::GetIO().DeltaTime, ImGui::GetIO().Framerate);
 ImGui::End();
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

inline void PropertiesPanel::renderShaderProperty(Property<std::shared_ptr<Shader>>* prop)
{
 
 int n_shaders = ShaderLibrary::getNumShaders();

 if (
  ImGui::BeginCombo(
   "Shader",
   prop->val->getName().c_str(),
   ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_PopupAlignLeft
  ))
 {
  for (int n = 0; n < n_shaders; n++)
  {
   auto shader = ShaderLibrary::getShaderByIndex(n);
   const bool is_selected = (shader == prop->val);
   if (ImGui::Selectable(shader->getName().c_str(), is_selected))
   {
    selected_material->setShader(shader);
    PropertiesPanel::onMaterialSelection(selected_material);
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

inline void PropertiesPanel::renderMaterialProperty(Property<std::shared_ptr<Material>>* prop)
{
}



}//end namespace