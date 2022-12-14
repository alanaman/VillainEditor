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

public:
 //TODO Add proper deconstructors that cleans up opengl side also
 Mesh(){};
 Mesh(std::string name) :name(name) {};

 static std::shared_ptr<Mesh> create(const std::string& path);
 virtual void loadMesh() = 0;
 virtual bool isLoaded() = 0;
 virtual void unLoadMesh() = 0;
 virtual void draw() = 0;
 //void setShader(std::shared_ptr<Shader> shader) { m_shader = shader; };
 void setShader(int id) { m_shader_id = id; };
 int getShader() { return m_shader_id; };

 friend class Scene;
};
}