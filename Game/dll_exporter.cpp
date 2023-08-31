#include "dll_exporter.hpp"
#include "actor_registrar.hpp"

int (*EditorRep ::m_getMeshIdFP)(const std::string&)=NULL;

//namespace villain {
//
//World Actor::world;
//}

villain::Actor* createActor(const std::string& actor)
{
 return villain::ActorDllLibrary::instantiate(actor);
}

const std::map<std::string, villain::Actor* (*)()>& getActorMap()
{
 return villain::ActorDllLibrary::actor_list();
}

//std::shared_ptr<villain::Actor> createActorsh(std::string name)
//{
// return villain::Bullet::create();
//}

void setSpawnFP(std::shared_ptr<villain::Actor> (*spawnActor_FP)(std::string))
{
 //villain::Actor::world.spawnActor_FP = spawnActor_FP;
}



