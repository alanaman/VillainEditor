#include "glad/glad.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "logging.hpp"
#include "mesh_opengl.hpp"

namespace villain {

std::shared_ptr<Mesh> Mesh::create(const std::string& path)
{
 return std::make_shared<MeshOpengl>(path);
}

MeshOpengl::MeshOpengl(const std::string& path)
{
 m_shader_index = 0;
 m_path = path;
}

void MeshOpengl::loadMesh()
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

bool MeshOpengl::isLoaded()
{
 if (vao == -1)
  return false;
 return true;
}

void MeshOpengl::unLoadMesh()
{
 glDeleteBuffers(1, &vbo);
 glDeleteBuffers(1, &ibo);
 glDeleteVertexArrays(1, &vao);

 vao = -1;
 vbo = -1;
 ibo = -1;
}

bool MeshOpengl::processNode(aiNode* node, const aiScene* scene)
{
 // process all the node's meshes
 for (unsigned int i = 0; i < node->mNumMeshes; i++)
 {
  name = node->mName.C_Str();
  aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
  m_mesh = std::make_shared<MeshOpengl>(processMesh(mesh, scene));
  return true;
 }
 // then do the same for each of its children
 for (unsigned int i = 0; i < node->mNumChildren; i++)
 {
  if(processNode(node->mChildren[i], scene))
   return true;
 }
 return false;
}

MeshOpengl MeshOpengl::processMesh(aiMesh* ai_mesh, const aiScene* scene)
{
 MeshOpengl mesh(ai_mesh->mName.C_Str());

 glGenVertexArrays(1, &mesh.vao);
 glBindVertexArray(mesh.vao);

 glGenBuffers(1, &mesh.vbo);
 glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
 glBufferData(
  GL_ARRAY_BUFFER,
  (unsigned long long)ai_mesh->mNumVertices*3*sizeof(float),
  &ai_mesh->mVertices[0],
  GL_STATIC_DRAW);

 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
 glEnableVertexAttribArray(0);

 std::vector<unsigned int> indices;
 for (unsigned int i = 0; i < ai_mesh->mNumFaces; i++)
 {
  aiFace face = ai_mesh->mFaces[i];
  for (unsigned int j = 0; j < face.mNumIndices; j++)
   indices.push_back(face.mIndices[j]);
 }
 glGenBuffers(1, &mesh.ibo);
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
 glBufferData(
  GL_ELEMENT_ARRAY_BUFFER,
  indices.size()*sizeof(unsigned int),
  &indices[0],
  GL_STATIC_DRAW);

 mesh.n_indices = indices.size();
 
 return mesh;
}

void MeshOpengl::draw()
{
 auto mesh = (MeshOpengl*)m_mesh.get();
 glBindVertexArray(mesh->vao);
 glDrawElements(GL_TRIANGLES, mesh->n_indices, GL_UNSIGNED_INT, 0);
}
}