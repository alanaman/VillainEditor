#include "material_library.hpp"

namespace villain {

std::vector<std::shared_ptr<Material>> MaterialLibrary::materials;
std::shared_ptr<Material> MaterialLibrary::default_material;

void MaterialLibrary::init()
{
 ShaderLibrary::init();
 auto def_shader = ShaderLibrary::getDefaultShader();
 default_material = std::make_shared<Material>("default_mat", def_shader);


}

void MaterialLibrary::addMaterial(std::shared_ptr<Material> new_material)
{
 for (auto& mat : materials)
 {
  if (mat->name == new_material->name)
   return;
 }
 materials.push_back(new_material);
}

std::shared_ptr<Material> MaterialLibrary::getDefaultMaterial()
{
 if (default_material == NULL)
  ERROR("default material not initialised");
 return default_material;
}

std::shared_ptr<Material> MaterialLibrary::getMaterialByIndex(int index)
{
 return materials[index];
}

std::shared_ptr<Material> MaterialLibrary::getMaterialByName(std::string& name)
{
 for (const auto& material:materials)
 {
  if (material->name == name)
   return material;
 }
 return default_material;
}

void MaterialLibrary::resolve(std::vector<std::shared_ptr<Material>>& loaded_materials)
{
 for (auto& loaded_mat : loaded_materials)
 {
  auto& name = loaded_mat->name;
  bool found = false;
  for (auto& mat : materials)
  {
   if (mat->name == name)
   {
    loaded_mat = mat;
    found = true;
    break;
   }
  }
  //if material not in library add it
  if(!found)
   materials.push_back(loaded_mat);
 }
}

}//end namespace villain