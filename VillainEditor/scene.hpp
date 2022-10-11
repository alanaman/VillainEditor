#pragma once

#include <string>
#include <vector>
#include "model.hpp"

namespace villain {
class Scene
{
private:
 std::string m_name;
 std::vector<Model> m_models;

public:
 Scene();
};
}