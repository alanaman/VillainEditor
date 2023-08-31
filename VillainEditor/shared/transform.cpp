#include "transform.hpp"
#include "logging.hpp"
#include "transform.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace villain {

 void Transform::setPosition(const glm::vec3& position)
 {
  this->position = position;
 }

 glm::vec3& Transform::getPositionRef()
 {
  return position;
 }
 glm::vec3 Transform::getPosition() const
 {
  return position;
 }
 void Transform::setScale(const glm::vec3& scale)
 {
  this->scale = scale;
 }
 glm::vec3& Transform::getScaleRef()
 {
  return scale;
 }
 glm::vec3 Transform::getScale() const
 {
  return scale;
 }
 void Transform::setRotation(const glm::vec3& rotation)
 {
  this->rotation = rotation;
 }
 glm::vec3& Transform::getRotationRef()
 {
  return rotation;
 }
 glm::vec3 Transform::getRotation() const
 {
  return rotation;
 }

 glm::mat4 Transform::getTransformMatrix() const
 {
  auto transformation = glm::mat4(1.0f);

  transformation = glm::translate(transformation, position);
  transformation = glm::rotate(transformation, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  transformation = glm::rotate(transformation, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  transformation = glm::rotate(transformation, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  transformation = glm::scale(transformation, glm::vec3(scale));

  return transformation;
 }

 std::ostream& operator<<(std::ostream& os, Transform const& m)
 {
  os
   << m.getPosition().x << " " << m.getPosition().y << " " << m.getPosition().z << " "
   << m.getScale().x << " " << m.getScale().y << " " << m.getScale().z << " "
   << m.getRotation().x << " " << m.getRotation().y << " " << m.getRotation().z << " ";
   return os;
 }

 std::istream& operator>>(std::istream& is, Transform& m)
 {
  is 
   >> m.getPositionRef().x >> m.getPositionRef().y >> m.getPositionRef().z
   >> m.getScaleRef().x >> m.getScaleRef().y >> m.getScaleRef().z
   >> m.getRotationRef().x >> m.getRotationRef().y >> m.getRotationRef().z;
 return is;
 }
}