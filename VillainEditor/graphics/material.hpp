#pragma once


#include "logging.hpp"
#include <glm/glm.hpp>

#include <cereal/archives/binary.hpp>
#include <cereal/access.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include "graphics/shader.hpp"

#include "asset_library/shader_library.hpp"

namespace villain {
class Material
{
private:
 std::string name;

 std::string shader;
 std::shared_ptr<Shader> shader_cache = NULL;

 Properties m_properties;
 Material() {};//cereal
public:
 ~Material();
 Material(std::string name);
 Material(std::string name, std::shared_ptr<Shader>& shader);

 std::string& getName() { return name; };
 void setName(std::string name) { this->name = name; };

 std::shared_ptr<Shader> getShader();
 void setShader(std::shared_ptr<Shader> shader);
 void bind();

 Properties collectectProperties() { return m_properties; };

 friend class MaterialLibrary;
 friend class AssetLibrary;

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   CEREAL_NVP(name),
   CEREAL_NVP(shader)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   name,
   shader
  );
 };
 friend class cereal::access;
};
}