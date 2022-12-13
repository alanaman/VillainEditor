#pragma once

#include <vector>
#include <glm.hpp>
#include "events.hpp"
#include "logging.hpp"

namespace villain {

enum class CameraControllerType
{
 LookAround,
 OrbitAroundPoint,
};

class Camera
{
 friend class LookAroundCameraController;
 friend class OrbitAroundCameraController;
protected:
 float mPitch = 0.0f;
 float mYaw = 270.0f;

 glm::vec3 mPosition = glm::vec3(0.0f, 0.0f, 10.0f);
 glm::vec3 mUp = glm::vec3(0.0f, 1.0f, 0.0f);

 float mFarPlane = 100.0f, mNearPlane = 0.1f;

 static int aspectX, aspectY;
 static float aspectRatio;

 float mVerticalFOV = 45.0f; //in degrees TODO:test

 float distance_to_center = 10.0f;

 static CameraControllerType m_type;
public:
 Camera();

 glm::mat4 getProjectionViewMatrix() const;
 glm::vec3 getForwardVector() const;
 glm::vec3 getRightVector() const;
 glm::vec3 getUpVector() const;

 void increasePitch(float val);
 void increaseYaw(float val);

 static void setControlType(CameraControllerType type);
 static void setAspect(int width, int height);
 void updateOnFrame();
 void eventHandler(Event& e);
};

class CameraController{};
class LookAroundCameraController : public CameraController
{
private:
 static bool w;
 static bool a;
 static bool s;
 static bool d;
 static bool lookaround_active;

 static float lookaround_speed;
 static float move_speed;
public:
 static void init();
 static void updateOnFrame(Camera& cam);
 static void eventHandler(Event& e, Camera& cam);
};

class OrbitAroundCameraController : public CameraController
{
private:
 static bool orbit_active;
 static bool pan_active;
 static bool zoom_active;

 static float orbit_speed;
 static float pan_speed;
 static float zoom_speed;
public:
 static void init();

 static void updateOnFrame(Camera& cam);
 static void eventHandler(Event& e, Camera& cam);
};

}