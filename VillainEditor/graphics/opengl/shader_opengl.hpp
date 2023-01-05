#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "graphics/shader.hpp"


namespace villain {

class ShaderOpengl : public Shader
{
private:
 std::string vertex_shader;
 std::string geometry_shader;
 std::string fragment_shader;

 GLuint m_programId = -1;
	static GLuint CreateShader(GLenum eShaderType, const std::string& strShaderFile);
	static GLuint CreateProgram(const std::vector<GLuint>& shaderList);

public:
	ShaderOpengl(
  const std::string& name, 
  const std::string& vertex_shader, 
  const std::string& fragment_shader
 );
 ShaderOpengl(
  const std::string& name, 
  const std::string& vertex_shader, 
  const std::string& geometry_shader, 
  const std::string& fragment_shader
 );
	void bind() const override;
	void setUniformBool(const std::string& name, bool value) const;
	void setUniformInt(const std::string& name, int value) const;
	void setUniformFloat(const std::string& name, float value) const;
	void setUniformVec2(const std::string& name, const glm::vec2& value) const;
	void setUniformVec3(const std::string& name, const glm::vec3& value) const;
	void setUniformVec4(const std::string& name, const glm::vec4& value) const;
	void setUniformMat2(const std::string& name, const glm::mat2& mat) const;
	void setUniformMat3(const std::string& name, const glm::mat3& mat) const;
	void setUniformMat4(const std::string& name, const glm::mat4& mat) const;

 std::vector<std::pair<std::string, UniformType>> queryParameters() const;
};
}

