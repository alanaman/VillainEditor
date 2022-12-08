#pragma once

#include <glad/glad.h>
#include <string>
#include "model.hpp"

namespace villain {

class MeshOpengl : public Mesh
{
public:
 GLuint vao = -1, vbo = -1, ibo = -1;
 unsigned long long n_indices = 0;

 MeshOpengl(std::string name) :Mesh(name) {};
};


class ModelOpengl : public Model
{
private:
 //returns true if mesh found
 bool processNode(aiNode* node, const aiScene* scene);
 MeshOpengl processMesh(aiMesh* mesh, const aiScene* scene);
public:
 ModelOpengl(const std::string& path);
 void loadMesh();
 void draw();
};



}