#pragma once

#include <imgui.h>
#include "meshlibrary.hpp"


namespace villain {

class AssetLibrary
{
private:
 const std::vector<std::string>& mesh_list;
public:
 AssetLibrary();
 void render();
};

}