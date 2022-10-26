#include <gtc/matrix_transform.hpp>
#include "camera.hpp"
//#include <gtc/type_ptr.hpp>

namespace villain {
Camera::Camera(int aspectX, int aspectY):
 m_aspectx(aspectX), m_aspecty(aspectY)
{
 m_aspectratio = (float)m_aspectx / (float)m_aspecty;
}

glm::mat4 Camera::getProjectionViewMatrix() const
{
 glm::mat4 view = glm::lookAt(
  m_position,
  m_center,
  m_up);

 glm::mat4 project = glm::perspective(
  m_vertical_fov,
  m_aspectratio,
  m_near_plane,
  m_far_plane);

 return project * view;

}

}
