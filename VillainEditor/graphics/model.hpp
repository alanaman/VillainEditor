#pragma once

#include <string>
#include <memory>
#include "shader.hpp"

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
protected:
 std::string m_name;
 std::string m_path;
 std::shared_ptr<Mesh> m_mesh;
 std::shared_ptr<Shader> m_shader;

public:
 static std::shared_ptr<Model> create(const std::string& path);
 virtual void loadMesh() = 0;
 virtual void draw() = 0;
 void setShader(std::shared_ptr<Shader> shader) { m_shader = shader; }

};
}