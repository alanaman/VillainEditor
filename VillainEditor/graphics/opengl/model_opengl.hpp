#pragma once

#include <glad/glad.h>
#include <string>
#include "model.hpp"
#include "mesh.hpp"

namespace villain {

struct MeshOpengl
{
 GLuint vao, vbo, ibo;
 unsigned long long n_indices;
};


class ModelOpengl : public Model
{
private:
 std::vector<MeshOpengl> m_meshes;
 void processNode(aiNode* node, const aiScene* scene);
 MeshOpengl processMesh(aiMesh* mesh, const aiScene* scene);
public:
 ModelOpengl(const std::string& name, const std::string& path);
 void loadMeshes();
 void draw();
};



}