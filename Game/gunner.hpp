#pragma once

#include "logging.hpp"
#include "actorBP.hpp"
//#include "bullet.hpp"
//#include "graphics/mesh.hpp"

//#include "bullet.hpp"
namespace villain {
class Gunner : public Actor
{
 //make properties member vars
 //property classes shud have references to these member vars
private:
 //shared vars

 //per instance editable vars
 float spin_speed = 1.0f;
 float fire_interval = 1.0f;
 std::string actor_name;

 //unexposed vars
 //std::shared_ptr<Mesh> gunner_mesh = Mesh::create(MeshLibrary::getId("gunner"));
 
 float bullet_timer = 0;

public:
 Gunner() {};
 //static std::shared_ptr<Actor> create();

 Gunner(std::string name);
 virtual void beginPlay() override;
 virtual void updateOnFrame(const float& deltatime) override;



 //virtual void collectMeshes(std::vector<std::shared_ptr<Mesh>*>& meshes) override;

 //virtual void collectProperties(Properties& properties) override;

 void spawnBullet();
};
}