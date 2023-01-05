#include "material.hpp"

namespace villain {

Material::Material(std::string name)
 :name(name)
{
 setShader(ShaderLibrary::getDefaultShader());
}

Material::~Material()
{
 for (auto& prop : m_properties.getPropertiesVector())
  free((void*)&(((Property<float>*)prop)->val));
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
 for (auto& prop : m_properties.getPropertiesVector())
  free((void*)&(((Property<float>*)prop)->val));
 m_properties.clear();
 this->shader = shader->getName();
 shader_cache = shader;
 auto parameter_list = shader->queryParameters();

 for (auto& param : parameter_list)
 {
  PropertyBase* new_prop = NULL;
  switch (param.second)
  {
  case UniformType::FLOAT:
   new_prop = new Property(param.first, *(new float));
   break;
  case UniformType::INT:
   new_prop = new Property(param.first, *(new int));
   break;
  case UniformType::VEC3:
   new_prop = new Property(param.first, *(new glm::vec3));
   break;
  default:
   ERROR("unimplemented type");
   break;
  }
  m_properties.addProperty(new_prop);
 }
}

void Material::bind()
{
 getShader()->bind();
 for (auto& prop : m_properties.getPropertiesVector())
 {
  switch (prop->getType())
  {
  case PropertyType::FLOAT:
   getShader()->setUniformFloat(prop->name, ((Property<float>*)prop)->val);
   break;
  case PropertyType::INT:
   getShader()->setUniformInt(prop->name, ((Property<int>*)prop)->val);
   break;
  case PropertyType::VEC3:
   getShader()->setUniformVec3(prop->name, ((Property<glm::vec3>*)prop)->val);
   break;
  default:
   break;
  }
 }
}

}//end namespace