#include <gtc/matrix_transform.hpp>
#include "camera.hpp"
#include "input.hpp"
//#include <gtc/type_ptr.hpp>

namespace villain {
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

void Camera::changePitch(float val)
{
 mPitch += val;
 if (mPitch >= 90.0f)
  mPitch = 89.9f;
 else if (mPitch <= -90.0f)
  mPitch = -89.9f;
}

void Camera::changeYaw(float val)
{
 mYaw += val;
 if (mYaw >= 360.0f)
  mYaw -= 360.0f;
 else if (mYaw <= 0.0f)
  mYaw += 360.0f;
}



void LookAroundCamera::updateOnFrame()
{
 if (w)
  mPosition += getForwardVector()*0.05f;
 if (s)
  mPosition -= getForwardVector()*0.05f;
 if (d)
  mPosition += getRightVector()*0.05f;
 if (a)
  mPosition -= getRightVector()*0.05f;

 //mPosition.x += 0.01f;
 //mPosition.y += 0.01f;
}

void LookAroundCamera::eventHandler(Event& e)
{
 switch (e.getEventType())
 {
 case EventType::MouseMove:
 {
  CursorMoveEvent* cme = (CursorMoveEvent*)&e;
  if (lookaround_active)
  {
   changeYaw(cme->delta_x*0.05f);
   changePitch(-cme->delta_y*0.05f);
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
}
