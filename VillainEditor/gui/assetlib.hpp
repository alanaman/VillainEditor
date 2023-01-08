#pragma once

#include <imgui/imgui.h>
#include "asset_library/meshlibrary.hpp"
#include "asset_library/actor_library.hpp"
#include "asset_library/material_library.hpp"

#include "properties_gui.hpp"


namespace villain {

class AssetLibrary
{
private:
 const std::vector<std::string>& mesh_list;
 const std::map<std::string, ActorLibrary::create_funtion*>& actor_list;

public:
 AssetLibrary();
 void render();
 void renderMeshLib();
 void renderActorLib();
 void renderMaterialLib();
 void renderShaderLib();
};

}