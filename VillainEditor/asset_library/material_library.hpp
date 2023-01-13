#pragma once

#include "logging.hpp"
#include "name_handler.hpp"
#include "window/filedialog.hpp"
#include <filesystem>

#include "graphics/material.hpp"

#include "asset_lib_macros.hpp"
#include "asset_library/shader_library.hpp"

namespace villain {

class MaterialLibrary
{
 static std::unordered_map<int, Material> materials;
 static Material default_material;
 static int nxt_id;
 static NameHandler mName_handler;

public:
 static void init();
 static void addMaterial();
 static void addMaterial(std::shared_ptr<Shader> shader);
 static int getNumMaterials() { return (int)materials.size(); };
 static int getMaterialIdByName(std::string& name);
 static Material& getMaterial(int mat_id);

 static void renameMaterial(int mat_id, std::string new_name);

 static void saveLibFile();
 static void loadLibFile();

 static void onSave();
 static void bind(int mat_id, const glm::mat4& model_trans) 
 { 
  materials[mat_id].bind();
  materials[mat_id].getShader()->setUniformMat4("uTransform", model_trans);
 };

 //static void resolve(std::vector<std::shared_ptr<Material>>& loaded_materials);

 friend class AssetLibrary;
 friend class PropertiesPanel;
 
};

}