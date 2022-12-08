#pragma once

#include <glad/glad.h>
#include <string>
#include "model.hpp"
#include "mesh.hpp"

namespace villain {

struct MeshOpengl
{
 GLuint vao = -1, vbo = -1, ibo = -1;
 unsigned long long n_indices = 0;
};


class ModelOpengl : public Model
{
private:
 MeshOpengl m_mesh;
 //returns true if mesh found
 bool processNode(aiNode* node, const aiScene* scene);
 MeshOpengl processMesh(aiMesh* mesh, const aiScene* scene);
public:
 ModelOpengl(const std::string& path);
 void loadMesh();
 void draw(glm::mat4& cameraMatrix);
};



}