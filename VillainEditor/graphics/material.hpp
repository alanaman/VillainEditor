#pragma once


#include "logging.hpp"
#include <glm/glm.hpp>

#include <cereal/archives/binary.hpp>
#include <cereal/access.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/unordered_map.hpp>

#include "graphics/shader.hpp"

#include "asset_library/shader_library.hpp"

namespace villain {
class Material
{
private:
 std::string name;

 std::shared_ptr<Shader> shader = NULL;

 std::string shader_name;
 Parameters m_parameters;
public:
 Material() {};//cereal
 ~Material();
 Material(std::string name);
 Material(std::string name, std::shared_ptr<Shader> shader);

 std::string getName() { return name; };
 //void rename(std::string name) { this->name = name; };//Through library namehandler

 std::shared_ptr<Shader> getShader();
 void setShader(std::shared_ptr<Shader> shader);
 void bind();

 virtual void collectProperties(Properties& properties);

 friend class MaterialLibrary;
 friend class cereal::access;

 //friend class AssetLibrary;

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(CEREAL_NVP(name));
  archive(CEREAL_NVP(shader_name));
  //archive(CEREAL_NVP(m_parameters));
 };
 template<class Archive>
 void load(Archive& archive)
 {
  try { archive(CEREAL_NVP(name)); }
  catch (const std::exception&) {};
  try { archive(CEREAL_NVP(shader_name)); }
  catch (const std::exception&) {};
  //try { archive(CEREAL_NVP(m_parameters)); }
  //catch (const std::exception&) {};
 };
};
}