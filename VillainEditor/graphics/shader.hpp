#pragma once

#include <string>
#include <vector>
#include <memory>
#include "glm.hpp"

#include <logging.hpp>

namespace villain {
class Shader
{
protected:
 std::string vertex_path;
 std::string fragment_path;
public:
	//TODO Add proper deconstructors that cleans up opengl side also
 static std::shared_ptr<Shader> create(const std::string& vertex_path, const std::string& fragment_path);


	virtual void bind() const = 0;
	virtual void setUniformBool(const std::string& name, bool value) const = 0;
	virtual void setUniformInt(const std::string& name, int value) const = 0;
	virtual void setUniformFloat(const std::string& name, float value) const = 0;
	virtual void setUniformVec2(const std::string& name, const glm::vec2& value) const = 0;
	virtual void setUniformVec3(const std::string& name, const glm::vec3& value) const = 0;
	virtual void setUniformVec4(const std::string& name, const glm::vec4& value) const = 0;
	virtual void setUniformMat2(const std::string& name, const glm::mat2& mat) const = 0;
	virtual void setUniformMat3(const std::string& name, const glm::mat3& mat) const = 0;
	virtual void setUniformMat4(const std::string& name, const glm::mat4& mat) const = 0;

	virtual void queryUniforms() = 0;//TODO: maybe make this queryParameters

 friend class Scene;
};
}