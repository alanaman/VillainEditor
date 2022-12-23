#pragma once

#include "logging.hpp"
#include "window/filedialog.hpp"
#include <filesystem>

#include "graphics/material.hpp"

#include "asset_lib_macros.hpp"
#include "asset_library/shader_library.hpp"

namespace villain {

class MaterialLibrary
{
 static std::vector<std::shared_ptr<Material>> materials;
 static std::shared_ptr<Material> default_material;

public:
 static void init();
 static void addMaterial(std::shared_ptr<Material> new_material);
 static std::shared_ptr<Material> getDefaultMaterial();
 static std::shared_ptr<Material> getMaterialByIndex(int index);
 static std::shared_ptr<Material> getMaterialByName(std::string& name);

 static void resolve(std::vector<std::shared_ptr<Material>>& loaded_materials);

 friend class AssetLibrary;

};

}