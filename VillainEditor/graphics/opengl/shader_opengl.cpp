#include <sstream>
#include <fstream>

#include "shader_opengl.hpp"

namespace villain {

std::shared_ptr<Shader> Shader::create(const std::string& vertex_path, const std::string& fragment_path)
{
 return std::make_shared<ShaderOpengl>(vertex_path, fragment_path);
}

ShaderOpengl::ShaderOpengl(const std::string& vertex_path, const std::string& fragment_path)
{
 std::vector<GLuint> shaderList;
 shaderList.push_back(LoadShader(GL_VERTEX_SHADER, vertex_path));
 shaderList.push_back(LoadShader(GL_FRAGMENT_SHADER, fragment_path));
 m_programId = CreateProgram(shaderList);
}

GLuint ShaderOpengl::LoadShader(GLenum shaderType, const std::string& filename)
{
 std::ifstream shaderFile(filename.c_str());
 if (!shaderFile.is_open())
  ERROR("Cannot find file: " + filename);
 std::stringstream shaderData;
 shaderData << shaderFile.rdbuf();
 shaderFile.close();
 return CreateShader(shaderType, shaderData.str());
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

void ShaderOpengl::queryUniforms()
{
 int n_ind = 0;
 glGetProgramiv(m_programId, GL_ACTIVE_UNIFORMS, &n_ind);
 std::cout << n_ind << "\n";
 for (int i = 0; i < n_ind; i++)
 {
   char name[100];
   glGetActiveUniformName(m_programId, i, 100, NULL, name);
   std::cout << name << "\n";
 }
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