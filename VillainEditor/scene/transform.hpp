#pragma once


#include "logging.hpp"
#include "glm.hpp"


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


};
std::ostream& operator<<(std::ostream& os, Transform const& m);
std::istream& operator>>(std::istream& is, Transform& m);
}