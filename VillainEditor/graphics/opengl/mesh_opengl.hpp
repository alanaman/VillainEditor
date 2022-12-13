#pragma once

#include <glad/glad.h>
#include <string>
#include "mesh.hpp"

namespace villain {

class MeshOpengl : public Mesh
{
private:
 //returns true if mesh found
 bool processNode(aiNode* node, const aiScene* scene);
 MeshOpengl processMesh(aiMesh* mesh, const aiScene* scene);
public:
 GLuint vao = -1, vbo = -1, ibo = -1;
 unsigned long long n_indices = 0;

 //MeshOpengl(std::string name) :Mesh(name) {};
 MeshOpengl(const std::string& path);
 void loadMesh() override;
 virtual bool isLoaded() override;
 virtual void unLoadMesh() override;
 void draw() override;
};
}