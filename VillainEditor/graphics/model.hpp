#pragma once

#include <string>
#include <memory>
#include "shader.hpp"
#include "transform.hpp"
#include "properties.hpp"

namespace villain {

class Mesh
{
protected:
 std::string m_name;
public:
 Mesh(std::string name):m_name(name){};
};


class Model
{
private:
 Transform m_tranform;
 Properties m_properties;

protected:
 std::string m_name;
 std::string m_path;
 std::shared_ptr<Mesh> m_mesh;
 int m_shader_index;

public:
 //TODO Add proper deconstructors that cleans up opengl side also

 Model();
 static std::shared_ptr<Model> create(const std::string& path);
 virtual void loadMesh() = 0;
 virtual void draw() = 0;
 //void setShader(std::shared_ptr<Shader> shader) { m_shader = shader; };
 void setShader(int index) { m_shader_index = index; };
 int getShader() { return m_shader_index; };

 friend class Scene;
};
}