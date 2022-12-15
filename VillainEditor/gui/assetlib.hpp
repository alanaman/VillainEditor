#pragma once

#include <imgui.h>
#include "meshlibrary.hpp"
#include "actor_library.hpp"


namespace villain {

class AssetLibrary
{
private:
 const std::vector<std::string>& mesh_list;
 const std::map<std::string, ActorLibrary::create_funtion*>& actor_list;

public:
 AssetLibrary();
 void render();
};

}