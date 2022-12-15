#pragma once

#include <string>
#include <memory>
#include "shader.hpp"
#include "entity.hpp"
#include "transform.hpp"
#include "properties.hpp"

namespace villain {

class Mesh
{
protected:
 std::string name;

 int m_shader_id = 0;

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

 void setShader(int id) { m_shader_id = id; };
 int getShader() { return m_shader_id; };

 friend class Scene;

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   CEREAL_NVP(name),
   CEREAL_NVP(m_shader_id)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   name,
   m_shader_id
  );

  //TODO: might have load mesh here
 };
 friend class cereal::access;
};
}