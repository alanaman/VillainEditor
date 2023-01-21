#include <sstream>
#include <fstream>

#include "shader_opengl.hpp"

namespace villain {

std::shared_ptr<Shader> Shader::create(
 const std::string& name,
 const std::string& vertex_shader,
 const std::string& fragment_shader
)
{
 return std::make_shared<ShaderOpengl>(name, vertex_shader, fragment_shader);
}

std::shared_ptr<Shader> Shader::create(
 const std::string& name,
 const std::string& vertex_shader,
 const std::string& geometry_shader,
 const std::string& fragment_shader
)
{
 return std::make_shared<ShaderOpengl>(name, vertex_shader, geometry_shader, fragment_shader);
}

ShaderOpengl::ShaderOpengl(
 const std::string& name,
 const std::string& vertex_shader,
 const std::string& fragment_shader
):Shader(name), vertex_shader(vertex_shader), geometry_shader(""), fragment_shader(fragment_shader)
{
 std::vector<GLuint> shaderList;
 shaderList.push_back(CreateShader(GL_VERTEX_SHADER, vertex_shader));
 shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, fragment_shader));
 m_programId = CreateProgram(shaderList);
}

ShaderOpengl::ShaderOpengl(
 const std::string& name,
 const std::string& vertex_shader,
 const std::string& geometry_shader,
 const std::string& fragment_shader
):Shader(name), vertex_shader(vertex_shader), geometry_shader(geometry_shader), fragment_shader(fragment_shader)
{
 std::vector<GLuint> shaderList;
 shaderList.push_back(CreateShader(GL_VERTEX_SHADER, vertex_shader));
 shaderList.push_back(CreateShader(GL_GEOMETRY_SHADER, geometry_shader));
 shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, fragment_shader));
 m_programId = CreateProgram(shaderList);
}

GLuint ShaderOpengl::CreateShader(GLenum eShaderType, const std::string& strShaderFile)
{
 GLuint shader = glCreateShader(eShaderType);
 const char* strFileData = strShaderFile.c_str();
 glShaderSource(shader, 1, &strFileData, NULL);

 glCompileShader(shader);

 GLint status;
 glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
 if (status == GL_FALSE)
 {
  int infoLogLength;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

  GLchar* strInfoLog = new GLchar[infoLogLength + 1];
  glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

  const char* strShaderType = NULL;
  switch (eShaderType)
  {
   case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
   case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
   case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
  }
  ERROR("Compile failure in " << strShaderType << " shader:" << strInfoLog);
  delete[] strInfoLog;
 }
 return shader;
}

GLuint ShaderOpengl::CreateProgram(const std::vector<GLuint>& shaderList)
{
 GLuint program = glCreateProgram();
 for (size_t index = 0; index < shaderList.size(); index++)
  glAttachShader(program, shaderList[index]);

 glLinkProgram(program);

 GLint status;
 glGetProgramiv(program, GL_LINK_STATUS, &status);
 if (status == GL_FALSE)
 {
   GLint infoLogLength;
   glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

   GLchar* strInfoLog = new GLchar[infoLogLength + 1];
   glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
   ERROR("GLSL Linker failure: " << strInfoLog);
   delete[] strInfoLog;
 }

 for (size_t index = 0; index < shaderList.size(); index++)
   glDetachShader(program, shaderList[index]);

 return program;
}

//void ShaderOpengl::queryUniforms()
//{
// int n_uniforms = 0;
// glGetProgramiv(m_programId, GL_ACTIVE_UNIFORMS, &n_uniforms);
// std::cout << n_uniforms << "\n";
//
// for (int i = 0; i < n_uniforms; i++)
// {
//   char name[100];
//   glGetActiveUniformName(m_programId, i, 100, NULL, name);
//   std::cout << name << "\n";
// }
//}

std::vector<std::pair<std::string, UniformType>> ShaderOpengl::queryParameters() const
{
 std::vector<std::pair<std::string, UniformType>> result;
 //const char* property_blockname = "Properties";
 //auto index = glGetUniformBlockIndex(m_programId, property_blockname);
 /*if (index == -1)
  return result;
 */
 //GLint n_uniforms;

 //glGetActiveUniformBlockiv(m_programId, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &n_uniforms);

 //GLint* uniform_indices = new GLint[n_uniforms];
 //glGetActiveUniformBlockiv(m_programId, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, uniform_indices);

 //GLint* uniform_type = new GLint[n_uniforms];
 //glGetActiveUniformsiv(m_programId, n_uniforms, (const GLuint*)uniform_indices, GL_UNIFORM_TYPE, uniform_type);
 //
 //int* uniform_namelength = new GLint[n_uniforms];
 //glGetActiveUniformsiv(m_programId, n_uniforms, (const GLuint*)uniform_indices, GL_UNIFORM_NAME_LENGTH, uniform_namelength);

 //for (int i = 0; i < n_uniforms; i++)
 //{
 // std::string name(uniform_namelength[i], '\0');
 // glGetActiveUniformName(m_programId, uniform_indices[i], uniform_namelength[i], NULL, &name[0]);

 GLint n_uniforms;

 glGetProgramiv(m_programId, GL_ACTIVE_UNIFORMS, &n_uniforms);

 std::vector<std::string> uniform_names;
 std::vector<GLenum> uniform_types;

 for (int uniform_idx = 0; uniform_idx < n_uniforms; uniform_idx++)
 {
  char uniform_name[64];
  GLenum type;
  GLsizei length;
  GLint size;
  glGetActiveUniform(m_programId, (GLuint)uniform_idx, 64, &length, &size, &type, uniform_name);
  std::string name_str(uniform_name);
  if (name_str.substr(0, 5) == "prop_")
  {
   uniform_names.push_back(name_str);
   uniform_types.push_back(type);
  }
 }
 for(int prop_index=0;prop_index< uniform_names.size(); prop_index++)
 {
  switch (uniform_types[prop_index])
  {
  case GL_FLOAT:
   result.push_back(std::make_pair(uniform_names[prop_index], UniformType::FLOAT));
   break;
  case GL_FLOAT_VEC3:
   result.push_back(std::make_pair(uniform_names[prop_index], UniformType::VEC3));
   break;
  case GL_INT:
   result.push_back(std::make_pair(uniform_names[prop_index], UniformType::INT));
   break;
  default:
   break;
  }
 }
 return result;
}

void ShaderOpengl::bind() const
{
 glUseProgram(m_programId);
}

void ShaderOpengl::setUniformBool(const std::string& name, bool value) const
{
 glUseProgram(m_programId);
 glUniform1i(glGetUniformLocation(m_programId, name.c_str()), (int)value);
}

void ShaderOpengl::setUniformInt(const std::string& name, int value) const
{
 glUseProgram(m_programId);
 glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
}

void ShaderOpengl::setUniformFloat(const std::string& name, float value) const
{
 glUseProgram(m_programId);
 glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
}

void ShaderOpengl::setUniformVec2(const std::string& name, const glm::vec2& value) const
{
 glUseProgram(m_programId);
 glUniform2fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void ShaderOpengl::setUniformVec3(const std::string& name, const glm::vec3& value) const
{
 glUseProgram(m_programId);
 glUniform3fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void ShaderOpengl::setUniformVec4(const std::string& name, const glm::vec4& value) const
{
 glUseProgram(m_programId);
 glUniform4fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void ShaderOpengl::setUniformMat2(const std::string& name, const glm::mat2& mat) const
{
 glUseProgram(m_programId);
 glUniformMatrix2fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderOpengl::setUniformMat3(const std::string& name, const glm::mat3& mat) const
{
 glUseProgram(m_programId);
 glUniformMatrix3fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderOpengl::setUniformMat4(const std::string& name, const glm::mat4& mat) const
{
 glUseProgram(m_programId);
 glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

}