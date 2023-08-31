#include "gunner.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

namespace villain {

//std::shared_ptr<ActorBP> Gunner::create()
//{
// auto ptr = std::make_shared<Gunner>(std::string("gunner_inst"));
// return ptr;
//}

void Gunner::beginPlay()
{
}


void Gunner::updateOnFrame(const float& deltatime)
{
 Transform t = getActorTransform();
 t.setRotation(t.getRotation() + glm::vec3(0, deltatime*spin_speed, 0));
 setActorTransform(t);
 bullet_timer += deltatime;
 if (bullet_timer >= fire_interval)
 {
  bullet_timer -= fire_interval;
  spawnBullet();
 }
}

//void Gunner::collectMeshes(std::vector<std::shared_ptr<Mesh>*>& meshes)
//{
// this->Actor::collectMeshes(meshes);
// meshes.push_back(&gunner_mesh);
// return;
//}

//void Gunner::collectProperties(Properties& properties)
//{
// this->Actor::collectProperties(properties);
// properties.addProperty(new Property<float>("spin_speed", spin_speed));
// properties.addProperty(new Property<float>("fire_interval", fire_interval));
// return;
//}

void Gunner::spawnBullet()
{
 std::string bullet_name = "Bullet";
 //Bullet* bullet = (bullet_name);

 glm::vec3 dir = glm::vec3(getActorTransform().getTransformMatrix() * glm::vec4(0, 0, 1, 0));
 //std::dynamic_pointer_cast<Bullet>(bullet)->setDirection(dir);

 glm::mat4 transform = glm::mat4(1);
 transform = glm::rotate(
  transform,
  glm::radians(90.0f),
  glm::vec3(1, 0, 0)
 );
 auto rot = glm::radians(getActorTransform().getRotation());
 transform = glm::eulerAngleXYZ(rot.x, rot.y, rot.z) * transform;
 glm::vec3 eulerXYZ;
 glm::extractEulerAngleXYZ(transform, eulerXYZ.x, eulerXYZ.y, eulerXYZ.z);

 glm::vec3 origin = glm::vec3(getActorTransform().getTransformMatrix() * glm::vec4(0, 1, 0.5, 1));


 //auto bullet = getWorld().spawnActor("bullet");
 //bullet->getActorTransform().setRotation(glm::degrees(eulerXYZ));
 //bullet->getActorTransform().setPosition(origin);
}
}