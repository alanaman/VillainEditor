#include "material.hpp"

namespace villain {

Material::Material(std::string name)
 :name(name)
{
 setShader(ShaderLibrary::getDefaultShader());
}

Material::Material(std::string name, std::shared_ptr<Shader>& shader)
 :name(name)
{
 setShader(shader);
}

std::shared_ptr<Shader> Material::getShader()
{
 if (shader_cache == NULL)
 {
  shader_cache = ShaderLibrary::getShaderByName(shader);
 }
 return shader_cache;
}

void Material::setShader(std::shared_ptr<Shader> shader)
{
 this->shader = shader->getName();
 shader_cache = shader;
 props = shader->queryProperties();
}

void Material::bind()
{
 getShader()->bind();
 for (auto& prop : props.properties)
 {
  switch (prop->getType())
  {
  case PropertyType::FLOAT:
   getShader()->setUniformFloat(prop->name, std::dynamic_pointer_cast<PropertyFloat>(prop)->val);
   break;
  case PropertyType::VEC3:
   getShader()->setUniformVec3(prop->name, std::dynamic_pointer_cast<PropertyVec3>(prop)->val);
   break;
  default:
   break;
  }
 }
}

}//end namespace