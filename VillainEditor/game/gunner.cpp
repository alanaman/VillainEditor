#include "gunner.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "VillainEditor.hpp"

namespace villain {

REGISTER_ACTOR(Gunner);

const std::vector<std::shared_ptr<PropDef>> Gunner::default_properties = {
 std::make_shared<PropDefFloat>(std::string("spin_speed"), 1.0f),
 std::make_shared<PropDefFloat>(std::string("fire_interval"), 1.0f)
 //std::make_shared<PropDefFloat>(std::string("scale"), 1.5f)
};


//std::shared_ptr<Mesh> Gunner::gunner_mesh = NULL;


std::shared_ptr<Actor> Gunner::create()
{
 auto ptr = std::make_shared<Gunner>(std::string("gunner_inst"));
 std::vector<std::shared_ptr<Mesh>> meshes;
 ptr->collectMeshes(meshes);
 for (auto& mesh : meshes)
  mesh->setParent(ptr);
 return ptr;
}

Gunner::Gunner(std::string name)
 :Actor(name)
{
 auto x = std::string("gunner");
 gunner_mesh = Mesh::create(x);

 for (const auto& prop : default_properties)
 {
  props.addPropertyFromDefault(prop.get());
 }

}
void Gunner::beginPlay()
{
}


void Gunner::updateOnFrame(const float& deltatime)
{
 m_transform.setRotation(m_transform.getRotation() + glm::vec3(0, deltatime*props.getFloatFromName("spin_speed"), 0));
 bullet_timer += deltatime;
 float fire_interval = props.getFloatFromName("fire_interval");
 if (bullet_timer >= fire_interval)
 {
  bullet_timer -= fire_interval;
  spawnBullet();
 }
}
void Gunner::collectMeshes(std::vector<std::shared_ptr<Mesh>>& meshes)
{
 this->Actor::collectMeshes(meshes);
 meshes.push_back(gunner_mesh);
 return;
}

void Gunner::collectProperties(std::vector<std::shared_ptr<Property>>& properties)
{
 this->Actor::collectProperties(properties);
 for (auto& prop : props.properties)
 {
  properties.push_back(prop);
 }
 return;
}
void Gunner::spawnBullet()
{
 std::string bullet_name = "Bullet";
 auto bullet = ActorLibrary::instantiate(bullet_name);

 glm::vec3 dir = glm::vec3(m_transform.getTransformMatrix() * glm::vec4(0, 0, 1, 0));
 bullet->setProperty("direction", dir);

 glm::mat4 transform = glm::mat4(1);
 transform = glm::rotate(
  transform,
  glm::radians(90.0f),
  glm::vec3(1, 0, 0)
 );
 auto rot = glm::radians(m_transform.getRotation());
 transform = glm::eulerAngleXYZ(rot.x, rot.y, rot.z) * transform;
 glm::vec3 eulerXYZ;
 glm::extractEulerAngleXYZ(transform, eulerXYZ.x, eulerXYZ.y, eulerXYZ.z);
 bullet->m_transform.setRotation(glm::degrees(eulerXYZ));

 glm::vec3 origin = glm::vec3(m_transform.getTransformMatrix() * glm::vec4(0, 1, 0.5, 1));
 bullet->m_transform.setPosition(origin);


 Editor::getEditorInstance()->getScene()->addActor(bullet);
}
}