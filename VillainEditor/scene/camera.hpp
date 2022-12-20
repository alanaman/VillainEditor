#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "input.hpp"
#include "events.hpp"
#include "logging.hpp"

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>


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


 float mVerticalFOV = 45.0f; //in degrees TODO:test
 float distance_to_center = 10.0f;

 static int aspectX, aspectY;
 static float aspectRatio;

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
 void updateOnFrame(const float& deltatime);
 void eventHandler(Event& e);


 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   CEREAL_NVP(mPitch),
   CEREAL_NVP(mYaw),
   CEREAL_NVP(mPosition.x),
   CEREAL_NVP(mPosition.y),
   CEREAL_NVP(mPosition.z),
   CEREAL_NVP(mUp.x),
   CEREAL_NVP(mUp.y),
   CEREAL_NVP(mUp.z),
   CEREAL_NVP(mFarPlane),
   CEREAL_NVP(mNearPlane),
   CEREAL_NVP(mVerticalFOV),
   CEREAL_NVP(distance_to_center)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   mPitch,
   mYaw,
   mPosition.x,
   mPosition.y,
   mPosition.z,
   mUp.x,
   mUp.y,
   mUp.z,
   mFarPlane,
   mNearPlane,
   mVerticalFOV,
   distance_to_center
  );
 };
 friend class cereal::access;
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
 static void updateOnFrame(Camera& cam, const float& deltatime);
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

 static void updateOnFrame(Camera& cam, const float& deltatime);
 static void eventHandler(Event& e, Camera& cam);
};

}