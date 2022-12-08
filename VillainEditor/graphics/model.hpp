#pragma once

#include <string>
#include <memory>
#include "shader.hpp"

namespace villain {
class Model
{
protected:
 std::string m_name;
 std::string m_path;
 std::shared_ptr<Shader> m_shader;

public:
 static std::shared_ptr<Model> create(const std::string& path);
 virtual void loadMesh() = 0;
 virtual void draw(glm::mat4 &cameraMatrix) = 0;
 void setShader(std::shared_ptr<Shader> shader) { m_shader = shader; }

};
}