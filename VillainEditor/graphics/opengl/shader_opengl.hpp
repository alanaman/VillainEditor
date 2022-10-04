#pragma once

#include <glad/glad.h>
#include <glm.hpp>

#include "shader.hpp"


namespace villain {

class ShaderOpengl : public Shader
{
private:
	GLuint m_programId;
	static GLuint LoadShader(GLenum eShaderType, const std::string& strFilename);
	static GLuint CreateShader(GLenum eShaderType, const std::string& strShaderFile);
	static GLuint CreateProgram(const std::vector<GLuint>& shaderList);

public:
	ShaderOpengl(const std::string& vertex_path, const std::string& fragment_path);
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

	void queryUniforms();
};
}

