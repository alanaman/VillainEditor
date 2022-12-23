#include "mesh_opengl.hpp"


namespace villain {

std::shared_ptr<Mesh> Mesh::create(const std::string& name)
{
 if (MeshLibrary::getIndex(name) == -1)
  ERROR("mesh does not exist in library:check mesh name");
 return std::make_shared<MeshOpengl>(name);
}

MeshOpengl::MeshOpengl(const std::string& name)
 :Mesh(name), mesh_ref(NULL)
{
 if (MeshLibrary::hasUsers(this->name))
 {
  mesh_ref = std::static_pointer_cast<std::vector<MeshMemoryRef>>(MeshLibrary::getLoadPoint(this->name));
  m_materials.resize((*mesh_ref).size());
 }
 m_materials = MeshLibrary::getDefaultMaterials(this->name);
}

void MeshOpengl::loadMesh()
{
 if (isLoaded())
  return;
 if (MeshLibrary::hasUsers(name))
 {
  mesh_ref = std::static_pointer_cast<std::vector<MeshMemoryRef>>(MeshLibrary::getLoadPoint(name));

  MeshLibrary::incrementUsers(name);
  return;
 }

 std::vector<MeshData> mesh_data;
 MeshLibrary::getMeshData(name, mesh_data);
 mesh_ref = std::make_shared<std::vector<MeshMemoryRef>>();
 MeshLibrary::incrementUsers(name);
 MeshLibrary::setLoadPoint(name, mesh_ref);

 mesh_ref->resize(mesh_data.size());
 for (int i = 0; i < mesh_data.size(); i++)
 {
  auto& meshpart = (*mesh_ref)[i];
  glGenVertexArrays(1, &meshpart.vao);
  glBindVertexArray(meshpart.vao);


  glGenBuffers(5, &meshpart.buffer_object_ids[0]);

  //index buffer object
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshpart.buffer_object_ids[0]);
  glBufferData(
   GL_ELEMENT_ARRAY_BUFFER,
   mesh_data[i].indices.size() * sizeof(unsigned int),
   &mesh_data[i].indices[0],
   GL_STATIC_DRAW);
  meshpart.n_indices = mesh_data[i].indices.size();

  //vertex positions
  glBindBuffer(GL_ARRAY_BUFFER, meshpart.buffer_object_ids[1]);
  glBufferData(
   GL_ARRAY_BUFFER,
   (unsigned long long)mesh_data[i].positions.size() * 3 * sizeof(float),
   &mesh_data[i].positions[0],
   GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  //vertex normals
  glBindBuffer(GL_ARRAY_BUFFER, meshpart.buffer_object_ids[2]);
  glBufferData(
   GL_ARRAY_BUFFER,
   (unsigned long long)mesh_data[i].normals.size() * 3 * sizeof(float),
   &mesh_data[i].normals[0],
   GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(1);

  //vertex colors
  glBindBuffer(GL_ARRAY_BUFFER, meshpart.buffer_object_ids[3]);
  glBufferData(
   GL_ARRAY_BUFFER,
   (unsigned long long)mesh_data[i].colors.size() * 4 * sizeof(float),
   &mesh_data[i].colors[0],
   GL_STATIC_DRAW);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(2);

  //vertex texture coords
  glBindBuffer(GL_ARRAY_BUFFER, meshpart.buffer_object_ids[4]);
  glBufferData(
   GL_ARRAY_BUFFER,
   (unsigned long long)mesh_data[i].tex_coords.size() * 2 * sizeof(float),
   &mesh_data[i].tex_coords[0],
   GL_STATIC_DRAW);
  glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(3);
 }
}

bool MeshOpengl::isLoaded()
{
 if(mesh_ref==NULL)
  return false;
 return true;
}

void MeshOpengl::unLoadMesh()
{
 if (!isLoaded())
  return;
 MeshLibrary::decrementUsers(name);
 if (MeshLibrary::hasUsers(name))
  return;

 auto& meshparts = (*mesh_ref);

 for (int i = 0; i < meshparts.size(); i++)
 {
  glDeleteBuffers(5, &meshparts[i].buffer_object_ids[0]);
  glDeleteVertexArrays(1, &meshparts[i].vao);
 }
 mesh_ref = NULL;
 MeshLibrary::setLoadPoint(name, NULL);
}

void MeshOpengl::draw()
{
 if (!isLoaded())
  ERROR("load mesh before draw call");

 auto& meshparts = (*mesh_ref);
 for (int i = 0; i < meshparts.size(); i++)
 {
  m_materials[i]->bind();
  m_materials[i]->getShader()->setUniformMat4("uTransform", getTransformMatrix());
  glBindVertexArray(meshparts[i].vao);
  glDrawElements(GL_TRIANGLES, meshparts[i].n_indices, GL_UNSIGNED_INT, 0);
 }
}

MeshOpengl::MeshMemoryRef::MeshMemoryRef()
 :buffer_object_ids(std::vector<GLuint>(5, -1))
{
}
}