#pragma once

#include <string>
#include <vector>
#include <mesh.hpp>

namespace villain {
class Model
{
private:
  std::string m_name;
  std::vector<Mesh> m_meshes;

  void loadModel(std::string& path);

public:
  Model(std::string& path);
};
}