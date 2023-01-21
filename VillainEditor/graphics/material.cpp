#include "material.hpp"

namespace villain {

Material::Material(std::string name)
 :name(name)
{
 setShader(ShaderLibrary::getDefaultShader());
}

Material::~Material()
{

}

Material::Material(std::string name, std::shared_ptr<Shader> shader)
 :name(name)
{
 setShader(shader);
}

std::shared_ptr<Shader> Material::getShader()
{
 if (shader == NULL)
 {
  shader = ShaderLibrary::getShaderByName(shader_name);
  WARNING("shader_cache is NULL: setShader may not have been called");
 }
 return shader;
}

void Material::setShader(std::shared_ptr<Shader> shader)
{
 m_parameters.clear();
 this->shader = shader;
 this->shader_name = shader->getName();
 auto parameter_list = shader->queryParameters();

 for (auto& param : parameter_list)
 {
  ParameterBase* new_prop = NULL;
  switch (param.second)
  {
  case UniformType::FLOAT:
   new_prop = new Parameter(param.first, 0.0f);
   break;
  case UniformType::INT:
   new_prop = new Parameter(param.first, 0);
   break;
  case UniformType::VEC3:
   new_prop = new Parameter(param.first, glm::vec3(1,0,0));
   break;
  default:
   ERROR("unimplemented type");
   break;
  }
  m_parameters.addParameter(new_prop);
 }
}

void Material::bind()
{
 getShader()->bind();
 for (auto& param : m_parameters.getParameterVector())
 {
  auto name = param->name;
  switch (param->getType())
  {
  case DataType::FLOAT:
   getShader()->setUniformFloat(name, ((Parameter<float>*)param)->val);
   break;
  case DataType::INT:
   getShader()->setUniformInt(name, ((Parameter<int>*)param)->val);
   break;
  case DataType::VEC3:
   getShader()->setUniformVec3(name, ((Parameter<glm::vec3>*)param)->val);
   break;
  default:
   break;
  }
 }
}

void Material::collectProperties(Properties& properties)
{
 properties.addProperty(new Property(std::string("shader"), shader));

 for (auto& param : m_parameters.getParameterVector())
 {
  properties.addProperty(param->getProperty());
 }
}


}//end namespace