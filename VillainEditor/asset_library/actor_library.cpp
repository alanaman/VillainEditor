#include "actor_library.hpp"

namespace villain {

//std::map<std::string, ActorLibrary::create_funtion*>& ActorLibrary::actor_list()
//{
// static std::map<std::string, ActorLibrary::create_funtion*> register_impl;
// return register_impl;
//}

std::vector<std::string> ActorLibrary::actor_list;
ActorLibrary::createActorFT ActorLibrary::createActorFP;


void ActorLibrary::updateActorsFromDll(const std::map<std::string, Actor* (*)()>& actor_map)
{
 for (const auto& elem : actor_map)
  actor_list.push_back(elem.first);
}

}