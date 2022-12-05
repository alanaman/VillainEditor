#pragma once

#include <vector>
#include <glm.hpp>
#include "events.hpp"
#include "logging.hpp"

namespace villain {
class Camera
{
protected:

 float mPitch = 0.0f;
 float mYaw = 270.0f;

 glm::vec3 mPosition = glm::vec3(0.0f, 0.0f, 10.0f);
 glm::vec3 mUp = glm::vec3(0.0f, 1.0f, 0.0f);

 float mFarPlane = 100.0f, mNearPlane = 0.1f;

 unsigned int mAspectX, mAspectY;
 float mAspectRatio;

 float mVerticalFOV = 45.0f; //in degrees TODO:test

public:
 Camera(int aspectX, int aspectY);

 glm::mat4 getProjectionViewMatrix() const;
 glm::vec3 getForwardVector() const;
 glm::vec3 getRightVector() const;
 //glm::vec3 getUpDirection() const;

 void changePitch(float val);
 void changeYaw(float val);

 virtual void updateOnFrame() = 0;
 virtual void eventHandler(Event& e) = 0;
};

class LookAroundCamera : public Camera
{
private:
 bool w = false;
 bool a = false;
 bool s = false;
 bool d = false;
 bool lookaround_active = false;

public:
 LookAroundCamera(int aspectX, int aspectY)
  :Camera(aspectX, aspectY) {};

 virtual void updateOnFrame() override;
 virtual void eventHandler(Event& e) override;
};

//class Camera
//{
//private:
//
// glm::vec3 mPosition = glm::vec3(10.0f, 10.0f, 10.0f);
// glm::vec3 mCenter = glm::vec3(0.0f, 0.0f, 0.0f);
// //glm::vec3 m_direction = glm::vec3(1 / sqrt(3), 1 / sqrt(3), 1 / sqrt(3));
// glm::vec3 mUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
// float mFarPlane = 100.0f, mNearPlane = 0.1f;
//
// float mYaw = 0.0f;
// float mPitch = 0.0f;
//
// unsigned int mAspectX, mAspectY;
// float mAspectRatio;
//
// float mVerticalFOV = 45.0f; //in degrees TODO:test
//
//public:
// Camera(int aspectX, int aspectY);
//
// glm::mat4 getProjectionViewMatrix() const;
// glm::vec3 getForwardVector() const;
//
// //void eventHandler(Event& e);
//};
}