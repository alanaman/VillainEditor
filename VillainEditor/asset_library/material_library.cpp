#include "material_library.hpp"

namespace villain {

//std::vector<std::shared_ptr<Material>> MaterialLibrary::materials;

std::unordered_map<int, Material> MaterialLibrary::materials;
Material MaterialLibrary::default_material;
int MaterialLibrary::nxt_id = 0;
NameHandler MaterialLibrary::mName_handler;

void MaterialLibrary::init()
{
 ShaderLibrary::init();
 default_material = Material("default_mat", ShaderLibrary::getDefaultShader());

 loadLibFile();
}

void MaterialLibrary::loadLibFile()
{
 if (!std::filesystem::exists(MATERIAL_LIB_FILE))
  return;
 auto filename = MATERIAL_LIB_FILE;
 std::ifstream file;
 file.open(filename, std::ios::binary);

 cereal::BinaryInputArchive archive(file);
 archive(nxt_id, materials);
 mName_handler.clear();
 for (auto& id_material : materials)
 {
  id_material.second.setShader(ShaderLibrary::getShaderByName(id_material.second.shader_name));
  mName_handler.addEntry(id_material.second.name);
 }
}

void MaterialLibrary::addMaterial()
{
 materials[nxt_id] = Material("Material", ShaderLibrary::getDefaultShader());
 mName_handler.addEntry(materials[nxt_id].name);
 nxt_id++;
}

void MaterialLibrary::addMaterial(std::shared_ptr<Shader> shader)
{
 materials[nxt_id] = Material("Material", shader);
 mName_handler.addEntry(materials[nxt_id].name);
 nxt_id++;
}


int MaterialLibrary::getMaterialIdByName(std::string& name)
{
 for (const auto& id_material:materials)
 {
  if (id_material.second.name == name)
   return id_material.first;
 }
 return -1;
}

Material& MaterialLibrary::getMaterial(int mat_id)
{
 if(materials.count(mat_id))
  return materials[mat_id];
 return default_material;
}

void MaterialLibrary::renameMaterial(int mat_id, std::string new_name)
{
 mName_handler.rename(materials[mat_id].name, new_name);
}

void MaterialLibrary::saveLibFile()
{
 auto filename = MATERIAL_LIB_FILE;
 std::ofstream file;
 file.open(filename, std::ios::binary);
 cereal::BinaryOutputArchive archive(file);
 archive(nxt_id, materials);
 file.close();
}


void MaterialLibrary::onSave()
{
 saveLibFile();
}

void MaterialLibrary::onLoad()
{
 loadLibFile();
}

//void MaterialLibrary::resolve(std::vector<std::shared_ptr<Material>>& loaded_materials)
//{
// for (auto& loaded_mat : loaded_materials)
// {
//  auto& name = loaded_mat->name;
//  bool found = false;
//  for (auto& mat : materials)
//  {
//   if (mat->name == name)
//   {
//    loaded_mat = mat;
//    found = true;
//    break;
//   }
//  }
//  //if material not in library add it
//  if(!found)
//   materials.push_back(loaded_mat);
// }
//}

}//end namespace villain