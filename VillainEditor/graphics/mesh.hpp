#pragma once

#include <string>
#include <memory>
#include "material.hpp"
#include "scene/entity.hpp"
#include "scene/transform.hpp"
#include "scene/properties.hpp"
#include "asset_library/meshlibrary.hpp"

//class villain::MeshId;

namespace villain {

class MeshId
{
public:
 int id = -1;
 MeshId() {};
 MeshId(const MeshId& m_id) { this->id = m_id.id; };
 MeshId(const int& id) { this->id = id; };
 MeshId operator=(const int& id) { return MeshId(id); };
 bool operator==(const MeshId& rhs) const { return (this->id == rhs.id); };
 //bool operator==(const int& rhs) { return (this->id == rhs); };
};
}
template<>
struct std::hash<villain::MeshId> {
 inline size_t operator()(const villain::MeshId& x) const {
  // size_t value = your hash computations over x
  return std::hash<int>()(x.id);
 }
};


namespace villain {


class Mesh
{
protected:
 MeshId mesh_id;

 std::vector<int> material_ids;
 //std::weak_ptr<Entity> m_owner;

 Mesh(){};//for cereal
 virtual bool isLoaded() = 0;
 //TODO Add proper deconstructors that cleans up opengl side also
public:
 Mesh(MeshId id) { mesh_id = id; };
 virtual ~Mesh() = default;
 std::string getName();

 static std::shared_ptr<Mesh> create(const MeshId mesh_id);
 virtual void loadMesh() = 0;
 virtual void unLoadMesh() = 0;
 virtual void draw(std::shared_ptr<Entity> parent) = 0;
 MeshId getId() { return mesh_id; };

 //void setParent(std::weak_ptr<Entity> parent) { m_owner = parent; };
 //std::shared_ptr<Entity> getParent() { return m_owner.lock(); };

 //glm::mat4 getTransformMatrix()
 //{
 // if (std::shared_ptr<Entity> temp_ptr = m_owner.lock())
 //  return temp_ptr->getTransformMatrix();
 // else
 //  ERROR("Mesh needs to have an existing owner");
 // return glm::mat4(1);
 //};

 //TODO: maybe pass id here
 void setMaterial(int slot, int mat_id) { material_ids[slot] = mat_id; };
 int getMaterialId(int slot) { return material_ids[slot]; };
 int getNumMaterialSlots() { return (int)material_ids.size(); };

 friend class Scene;

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   CEREAL_NVP(mesh_id.id),
   CEREAL_NVP(material_ids)
   //CEREAL_NVP(m_owner)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  try { archive(CEREAL_NVP(mesh_id.id)); }
  catch (const std::exception&) { ERROR("id couldnt load") };//might wanna assign default mesh id
  try { archive(CEREAL_NVP(material_ids)); }
  catch (const std::exception&)
  { 
   //WARNING("material_ids did not load. assigning default materials")
   //material_ids = villain::MeshLibrary::getDefaultMaterialIds(mesh_id);
  };
  //TODO: might have load mesh here
 };
 friend class cereal::access;
};
}
CEREAL_REGISTER_TYPE(villain::Parameter<std::shared_ptr<villain::Mesh>>);
