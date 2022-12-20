#pragma once


#include "logging.hpp"
#include "glm/glm.hpp"

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

namespace villain {

class Transform
{
protected:
 glm::vec3 position = glm::vec3(0);
 glm::vec3 scale = glm::vec3(1);
 glm::vec3 rotation = glm::vec3(0);
public:
 void setPosition(const glm::vec3& position);
 glm::vec3& getPositionRef();
 glm::vec3 getPosition() const;
 void setScale(const glm::vec3& scale);
 glm::vec3& getScaleRef();
 glm::vec3 getScale() const;
 void setRotation(const glm::vec3& rotation);
 glm::vec3& getRotationRef();
 glm::vec3 getRotation() const;

 glm::mat4 getTransformMatrix();


 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   CEREAL_NVP(position.x),
   CEREAL_NVP(position.y),
   CEREAL_NVP(position.z),
   CEREAL_NVP(scale.x),
   CEREAL_NVP(scale.y),
   CEREAL_NVP(scale.z),
   CEREAL_NVP(rotation.x),
   CEREAL_NVP(rotation.y),
   CEREAL_NVP(rotation.z)   
   );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   position.x,
   position.y,
   position.z,
   scale.x,
   scale.y,
   scale.z,
   rotation.x,
   rotation.y,
   rotation.z
  );
 };
 friend class cereal::access;
};
std::ostream& operator<<(std::ostream& os, Transform const& m);
std::istream& operator>>(std::istream& is, Transform& m);
}