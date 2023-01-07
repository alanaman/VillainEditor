#include "properties_gui.hpp"

namespace villain {

bool PropertiesPanel::show_properties_window = true;
Properties PropertiesPanel::m_properties;

void PropertiesPanel::onEntitySelection(std::shared_ptr<Entity> entity)
{
 PropertiesPanel::m_properties.clear();
 if (entity == NULL)
  return;
 entity->collectProperties(PropertiesPanel::m_properties);
}

void PropertiesPanel::render()
{
 ImGui::Begin("Properties", &show_properties_window);                          // Create a window called "Hello, world!" and append into it.

 auto& properties = m_properties.getPropertiesVector();

 for (auto& property : properties)
 {
  switch (property->getType())
  {
 
  case PropertyType::FLOAT:
   renderFloatProperty((Property<float>*)property);
   break;
  
  case PropertyType::INT:
   renderIntProperty((Property<int>*)property);
   break;
  
  case PropertyType::VEC3:
   renderVec3Property((Property<glm::vec3>*)property);
   break;
  
  case PropertyType::TRANSFORM:
   renderTransformProperty((Property<Transform>*)property);
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


}//end namespace