#pragma once

#include <string>
#include <memory>
#include "material.hpp"
#include "entity.hpp"
#include "transform.hpp"
#include "properties.hpp"
#include "alternate_impl/mesh_component.hpp"
#include "asset_library/meshlibrary.hpp"

//class villain::MeshId;

namespace villain {

class Mesh
{
protected:
 int mesh_id;

 std::vector<int> material_ids;
 //std::weak_ptr<Entity> m_owner;

 Mesh(){};//for cereal
 virtual bool isLoaded() = 0;
 //TODO Add proper deconstructors that cleans up opengl side also
public:
 Mesh(int id) :mesh_id(id) {};
 Mesh(const MeshComponent& meshComp) :
  mesh_id(meshComp.mesh_id),
  material_ids(meshComp.material_ids)
 {};
 virtual ~Mesh() = default;
 //std::string getName();

 static std::shared_ptr<Mesh> create(const int mesh_id);
 static std::shared_ptr<Mesh> create(const std::string& path);
 static std::shared_ptr<Mesh> create(const MeshComponent& meshComp);

 virtual void loadMesh() = 0;
 virtual void unLoadMesh() = 0;
 virtual void draw(std::shared_ptr<Entity> parent) = 0;
 int getId() { return mesh_id; };

 //void setParent(std::weak_ptr<Entity> parent) { m_owner = parent; };
 //std::shared_ptr<Entity> getParent() { return m_owner.lock(); };

 //glm::mat4 getTransformMatrix()
 //{
 // if (std::shared_ptr<Entity> temp_ptr = m_owner.lock())
 //  return temp_ptr->getTransformMatrix();
 // else
 //  VLLN_ERR("Mesh needs to have an existing owner");
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
   CEREAL_NVP(mesh_id),
   CEREAL_NVP(material_ids)
   //CEREAL_NVP(m_owner)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  try { archive(CEREAL_NVP(mesh_id)); }
  catch (const std::exception&) { VLLN_ERR("id couldnt load") };//might wanna assign default mesh id
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
