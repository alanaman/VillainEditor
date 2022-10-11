#include "glad/glad.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "logging.hpp"
#include "model_opengl.hpp"

namespace villain {

std::shared_ptr<Model> Model::create(const std::string& name, const std::string& path)
{
 return std::make_shared<ModelOpengl>(name, path);
}

ModelOpengl::ModelOpengl(const std::string& name, const std::string& path)
{
 m_name = name;
 m_path = path;
}


void ModelOpengl::loadMeshes()
{
 Assimp::Importer importer;
 const aiScene* scene = importer.ReadFile(
  m_path,
  aiProcess_Triangulate | aiProcess_FlipUVs);
 if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
 {
  ERROR("ASSIMP::" << import.GetErrorString());
  return;
 }
 //directory = m_path.substr(0, m_path.find_last_of('/'));

 processNode(scene->mRootNode, scene);
}

void ModelOpengl::processNode(aiNode* node, const aiScene* scene)
{
 // process all the node's meshes
 for (unsigned int i = 0; i < node->mNumMeshes; i++)
 {
  aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
  m_meshes.push_back(processMesh(mesh, scene));
 }
 // then do the same for each of its children
 for (unsigned int i = 0; i < node->mNumChildren; i++)
 {
  processNode(node->mChildren[i], scene);
 }
}

MeshOpengl ModelOpengl::processMesh(aiMesh* mesh, const aiScene* scene)
{
 GLuint vao, vbo, ibo;

 glGenVertexArrays(1, &vao);
 glBindVertexArray(vao);

 glGenBuffers(1, &vbo);
 glBindBuffer(GL_ARRAY_BUFFER, vbo);
 glBufferData(
  GL_ARRAY_BUFFER,
  (unsigned long long)mesh->mNumVertices*3*sizeof(float),
  &mesh->mVertices[0],
  GL_STATIC_DRAW);

 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
 glEnableVertexAttribArray(0);

 std::vector<unsigned int> indices;
 for (unsigned int i = 0; i < mesh->mNumFaces; i++)
 {
  aiFace face = mesh->mFaces[i];
  for (unsigned int j = 0; j < face.mNumIndices; j++)
   indices.push_back(face.mIndices[j]);
 }
 glGenBuffers(1, &ibo);
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
 glBufferData(
  GL_ELEMENT_ARRAY_BUFFER,
  indices.size()*sizeof(unsigned int),
  &indices[0],
  GL_STATIC_DRAW);

 return { vao, vbo, ibo, indices.size() };
}

void ModelOpengl::draw()
{
 for (const auto &mesh : m_meshes)
 {
  glBindVertexArray(mesh.vao);
  glDrawElements(GL_TRIANGLES, mesh.n_indices, GL_UNSIGNED_INT, 0);
 }
}
}