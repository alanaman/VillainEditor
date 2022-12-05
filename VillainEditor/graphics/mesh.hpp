#pragma once

#include <string>
#include <vector>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace villain {

struct Vertex
{
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texcoord;
};


class Mesh
{
  std::vector<Vertex> m_vertices;
  std::vector<unsigned int> m_indices;
public:
  Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};
}