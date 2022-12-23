#pragma once

#include <string>
#include <memory>
#include "material.hpp"
#include "scene/entity.hpp"
#include "scene/transform.hpp"
#include "scene/properties.hpp"

namespace villain {

class Mesh
{
protected:
 std::string name;

 std::vector<std::shared_ptr<Material>> m_materials;
 std::weak_ptr<Entity> m_owner;

 Mesh(){};//for cereal
public:
 //TODO Add proper deconstructors that cleans up opengl side also
 Mesh(std::string name) :name(name) {};
 virtual ~Mesh() = default;

 static std::shared_ptr<Mesh> create(const std::string& name);
 virtual void loadMesh() = 0;
 virtual bool isLoaded() = 0;
 virtual void unLoadMesh() = 0;
 virtual void draw() = 0;

 void setParent(std::weak_ptr<Entity> parent) { m_owner = parent; };

 glm::mat4 getTransformMatrix()
 {
  if (std::shared_ptr<Entity> temp_ptr = m_owner.lock())
   return temp_ptr->getTransformMatrix();
  else
   ERROR("Mesh needs to have an existing owner");
  return glm::mat4(1);
 };

 void setMaterial(int slot, std::shared_ptr<Material>& material) { m_materials[slot] = material; };
 std::shared_ptr<Material> getMaterial(int slot) { return m_materials[slot]; };

 friend class Scene;

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   CEREAL_NVP(name),
   CEREAL_NVP(m_materials),
   CEREAL_NVP(m_owner)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   name,
   m_materials,
   m_owner
  );

  
  //TODO: might have load mesh here
 };
 friend class cereal::access;
};
}