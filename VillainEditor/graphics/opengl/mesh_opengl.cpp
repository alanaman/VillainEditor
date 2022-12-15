#include "mesh_opengl.hpp"

namespace villain {

std::shared_ptr<Mesh> Mesh::create(const std::string& name)
{
 return std::make_shared<MeshOpengl>(name);
}

MeshOpengl::MeshOpengl(const std::string& name)
 :Mesh(name), mesh_ref(NULL)
{
 m_shader_id = 0;
}

void MeshOpengl::loadMesh()
{
 if (isLoaded())
  return;
 if (MeshLibrary::hasUsers(name))
 {
  mesh_ref = std::static_pointer_cast<MeshMemoryRef>(MeshLibrary::getLoadPoint(name));

  MeshLibrary::incrementUsers(name);
  return;
 }

 auto mesh_data = MeshLibrary::getMeshData(name);
 mesh_ref = std::make_shared<MeshMemoryRef>();
 MeshLibrary::incrementUsers(name);
 MeshLibrary::setLoadPoint(name, mesh_ref);

 glGenVertexArrays(1, &mesh_ref->vao);
 glBindVertexArray(mesh_ref->vao);

 glGenBuffers(5, &mesh_ref->buffer_object_ids[0]);
 
 //index buffer object
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ref->buffer_object_ids[0]);
 glBufferData(
  GL_ELEMENT_ARRAY_BUFFER,
  mesh_data->indices.size() * sizeof(unsigned int),
  &mesh_data->indices[0],
  GL_STATIC_DRAW);
 mesh_ref->n_indices = mesh_data->indices.size();
 
 //vertex positions
 glBindBuffer(GL_ARRAY_BUFFER, mesh_ref->buffer_object_ids[1]);
 glBufferData(
  GL_ARRAY_BUFFER,
  (unsigned long long)mesh_data->positions.size() * 3 * sizeof(float),
  &mesh_data->positions[0],
  GL_STATIC_DRAW);
 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
 glEnableVertexAttribArray(0);
 
 //vertex normals
 glBindBuffer(GL_ARRAY_BUFFER, mesh_ref->buffer_object_ids[2]);
 glBufferData(
  GL_ARRAY_BUFFER,
  (unsigned long long)mesh_data->normals.size() * 3 * sizeof(float),
  &mesh_data->normals[0],
  GL_STATIC_DRAW);
 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
 glEnableVertexAttribArray(1);
 
 //vertex colors
 glBindBuffer(GL_ARRAY_BUFFER, mesh_ref->buffer_object_ids[3]);
 glBufferData(
  GL_ARRAY_BUFFER,
  (unsigned long long)mesh_data->colors.size() * 4 * sizeof(float),
  &mesh_data->colors[0],
  GL_STATIC_DRAW);
 glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
 glEnableVertexAttribArray(2);
 
 //vertex texture coords
 glBindBuffer(GL_ARRAY_BUFFER, mesh_ref->buffer_object_ids[4]);
 glBufferData(
  GL_ARRAY_BUFFER,
  (unsigned long long)mesh_data->tex_coords.size() * 2 * sizeof(float),
  &mesh_data->tex_coords[0],
  GL_STATIC_DRAW);
 glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
 glEnableVertexAttribArray(3);

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
 glDeleteBuffers(5, &mesh_ref->buffer_object_ids[0]);
 glDeleteVertexArrays(1, &mesh_ref->vao);
 mesh_ref = NULL;
 MeshLibrary::setLoadPoint(name, NULL);
}

void MeshOpengl::draw()
{
 if (!isLoaded())
  ERROR("load mesh before draw call");
 glBindVertexArray(mesh_ref->vao);
 glDrawElements(GL_TRIANGLES, mesh_ref->n_indices, GL_UNSIGNED_INT, 0);
}
MeshOpengl::MeshMemoryRef::MeshMemoryRef()
 :buffer_object_ids(std::vector<GLuint>(5, -1))
{
}
}