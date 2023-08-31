#pragma once

#include "logging.hpp"
#include <memory>
#include <string>

#include "actor.hpp"

namespace villain {


class ActorLibrary
{
public:
 //using create_funtion = std::shared_ptr<Actor>();

 using createActorFT = Actor * (*)(const std::string&);

 static createActorFT createActorFP;

public:
 static std::vector<std::string> actor_list;
 
 static std::shared_ptr<Actor> instantiate(const std::string& name)
 {
  return std::shared_ptr<Actor>(createActorFP(name));
 }

 static std::shared_ptr<Actor> instantiate(int index)
 {
  if (index >= actor_list.size())
   return NULL;
  return std::shared_ptr<Actor>(createActorFP(actor_list[index]));
 }

 static void updateActorsFromDll(const std::map<std::string, Actor* (*)()>& actor_map);

};
}