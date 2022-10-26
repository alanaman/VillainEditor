#pragma once

#include <vector>
#include <glm.hpp>

namespace villain {
class Camera
{
private:

 glm::vec3 m_position = glm::vec3(10.0f, 10.0f, 10.0f);
 glm::vec3 m_center = glm::vec3(0.0f, 0.0f, 0.0f);
 //glm::vec3 m_direction = glm::vec3(1 / sqrt(3), 1 / sqrt(3), 1 / sqrt(3));
 glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

 float m_far_plane = 100.0f, m_near_plane = 0.1f;

 unsigned int m_aspectx, m_aspecty;
 float m_aspectratio;

 float m_vertical_fov = 45.0F; //TODO degree/rad

public:
 Camera(int aspectX, int aspectY);

 glm::mat4 getProjectionViewMatrix() const;
};


}