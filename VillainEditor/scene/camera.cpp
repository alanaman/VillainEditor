#include <gtc/matrix_transform.hpp>
#include "camera.hpp"
#include "input.hpp"
//#include <gtc/type_ptr.hpp>

namespace villain {

CameraControllerType Camera::m_type = CameraControllerType::OrbitAroundPoint;

bool LookAroundCameraController::w = false;
bool LookAroundCameraController::a = false;
bool LookAroundCameraController::s = false;
bool LookAroundCameraController::d = false;
bool LookAroundCameraController::lookaround_active = false;
float LookAroundCameraController::lookaround_speed = 0.05f;
float LookAroundCameraController::move_speed = 0.05f;

bool OrbitAroundCameraController::orbit_active = false;
bool OrbitAroundCameraController::pan_active = false;
bool OrbitAroundCameraController::zoom_active = false;
float OrbitAroundCameraController::orbit_speed = 0.2f;
float OrbitAroundCameraController::pan_speed = 0.001f;
float OrbitAroundCameraController::zoom_speed = 0.1f;

Camera::Camera(int aspectX, int aspectY):
 mAspectX(aspectX), mAspectY(aspectY)
{
 mAspectRatio = (float)mAspectX / (float)mAspectY;
}

glm::mat4 Camera::getProjectionViewMatrix() const
{


 glm::mat4 view = glm::lookAt(
  mPosition,
  mPosition+getForwardVector(),
  mUp);

 glm::mat4 project = glm::perspective(
  glm::radians(mVerticalFOV),
  mAspectRatio,
  mNearPlane,
  mFarPlane);

 return project * view;

}

glm::vec3 Camera::getForwardVector() const
{
 glm::vec3 direction;

 direction.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
 direction.y = sin(glm::radians(mPitch));
 direction.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
 
 return direction;
}

glm::vec3 Camera::getRightVector() const
{
 return glm::normalize(glm::cross(getForwardVector(), mUp));
}

glm::vec3 Camera::getUpVector() const
{
 return glm::cross(getRightVector(), getForwardVector());
}

void Camera::increasePitch(float val)
{
 mPitch += val;
 if (mPitch >= 90.0f)
  mPitch = 89.9f;
 else if (mPitch <= -90.0f)
  mPitch = -89.9f;
}

void Camera::increaseYaw(float val)
{
 mYaw += val;
 if (mYaw >= 360.0f)
  mYaw -= 360.0f;
 else if (mYaw <= 0.0f)
  mYaw += 360.0f;
}

void Camera::setControlType(CameraControllerType type)
{
 m_type = type;
 if (type == CameraControllerType::LookAround)
  LookAroundCameraController::init();
 else if (type == CameraControllerType::OrbitAroundPoint)
  OrbitAroundCameraController::init();
}

void Camera::updateOnFrame()
{
 if (m_type == CameraControllerType::LookAround)
  LookAroundCameraController::updateOnFrame(*this);
 else if (m_type == CameraControllerType::OrbitAroundPoint)
  OrbitAroundCameraController::updateOnFrame(*this);
}

void Camera::eventHandler(Event& e)
{
 if (m_type == CameraControllerType::LookAround)
  LookAroundCameraController::eventHandler(e, *this);
 else if (m_type == CameraControllerType::OrbitAroundPoint)
  OrbitAroundCameraController::eventHandler(e, *this);
}

void LookAroundCameraController::init()
{
 w = false;
 a = false;
 s = false;
 d = false;
 lookaround_active = false;
}

void LookAroundCameraController::updateOnFrame(Camera& cam)
{
 if (w)
  cam.mPosition += cam.getForwardVector()*move_speed;
 if (s)
  cam.mPosition -= cam.getForwardVector()*move_speed;
 if (d)
  cam.mPosition += cam.getRightVector()*move_speed;
 if (a)
  cam.mPosition -= cam.getRightVector()*move_speed;
}

void LookAroundCameraController::eventHandler(Event& e, Camera& cam)
{
 switch (e.getEventType())
 {
 case EventType::MouseMove:
 {
  CursorMoveEvent* cme = (CursorMoveEvent*)&e;
  if (lookaround_active)
  {
   cam.increaseYaw(cme->delta_x*lookaround_speed);
   cam.increasePitch(-cme->delta_y*lookaround_speed);
  }
  break;
 }
 case EventType::MouseButtonPressed:
 {
  MouseButtonPressEvent* mbp = (MouseButtonPressEvent*)&e;
  if (mbp->button == MOUSE::BUTTON_3)
   lookaround_active = true;
  break;
 }
 case EventType::MouseButtonReleased:
 {
  MouseButtonReleaseEvent* mbp = (MouseButtonReleaseEvent*)&e;
  if (mbp->button == MOUSE::BUTTON_3)
   lookaround_active = false;
  break;
 }
 case EventType::KeyPress:
 {
  KeyPressEvent* ke = (KeyPressEvent*)&e;
  int key = ke->key;
  if (key == KEY::W)
   w = true;
  else if (key == KEY::A)
   a = true;
  else if (key == KEY::S)
   s = true;
  else if (key == KEY::D)
   d = true;
  break;
 }
 case EventType::KeyRelease:
 {
  KeyReleaseEvent* ke = (KeyReleaseEvent*)&e;
  int key = ke->key;
  if (key == KEY::W)
   w = false;
  else if (key == KEY::A)
   a = false;
  else if (key == KEY::S)
   s = false;
  else if (key == KEY::D)
   d = false;
  break;
 }
 default:
  break;
 }
}

void OrbitAroundCameraController::init()
{

}

void OrbitAroundCameraController::updateOnFrame(Camera& cam)
{

}

void OrbitAroundCameraController::eventHandler(Event& e, Camera& cam)
{
 switch (e.getEventType())
 {
 case EventType::MouseMove:
 {
  CursorMoveEvent* cme = (CursorMoveEvent*)&e;
  if (orbit_active)
  {
   glm::vec3 center_point = cam.mPosition + cam.distance_to_center * cam.getForwardVector();
   cam.increaseYaw(cme->delta_x * 0.2f);
   cam.increasePitch(-cme->delta_y * 0.2f);
   cam.mPosition = center_point - cam.distance_to_center * cam.getForwardVector();
  }
  else if (zoom_active)
  {
   float zoom_dist = std::min(
    -(float)cme->delta_y * zoom_speed,
    cam.distance_to_center - cam.mNearPlane);
   cam.mPosition += cam.getForwardVector() * zoom_dist;
   cam.distance_to_center -= zoom_dist;

  }
  else if (pan_active)
  {
   cam.mPosition -= cam.getRightVector() * (float)cme->delta_x * pan_speed * cam.distance_to_center;
   cam.mPosition += cam.getUpVector() * (float)cme->delta_y * pan_speed * cam.distance_to_center;
  }
  break;
 }
 case EventType::MouseButtonPressed:
 {
  MouseButtonPressEvent* mbp = (MouseButtonPressEvent*)&e;
  if (mbp->button == MOUSE::BUTTON_3)
  {
   if (mbp->mods == 0)
    orbit_active = true;
   else if (mbp->mods & MOD::CONTROL)
    zoom_active = true;
   else if (mbp->mods & MOD::SHIFT)
    pan_active = true;
  }
  break;
 }
 case EventType::MouseButtonReleased:
 {
  MouseButtonReleaseEvent* mbp = (MouseButtonReleaseEvent*)&e;
  if (mbp->button == MOUSE::BUTTON_3)
  {
   orbit_active = false;
   pan_active = false;
   zoom_active = false;
  }
  break;
 }
 }
}

}
