#pragma once

#include "logging.hpp"
#include <memory>
#include <string>

#include "scene/actor.hpp"

namespace villain {


class ActorLibrary
{
public:
 using create_funtion = std::shared_ptr<Actor>();

private:
 static void registerMethod(std::string const& name, create_funtion* fp)
 {
  actor_list().insert({name, fp});
 }
public:
 static std::shared_ptr<Actor> instantiate(std::string const& name)
 {
  auto it = actor_list().find(name);
  return it == actor_list().end() ? nullptr : (it->second)();
 }
 static std::shared_ptr<Actor> instantiate(int index)
 {
  if (index >= actor_list().size())
   return NULL;
  auto actor = actor_list().begin();
  std::advance(actor, index);
  return actor->second();
 }

 template <typename DerivedActor>
 struct Registrar
 {
  explicit Registrar(std::string const& name)
  {
   ActorLibrary::registerMethod(name, &DerivedActor::create);
  }
  Registrar(const Registrar&) = delete;
  Registrar& operator=(const Registrar&) = delete;
 };

 //in function form so that map is initialized before insert is called
 static std::map<std::string, ActorLibrary::create_funtion*>& actor_list();
};

#define REGISTER_ACTOR(x) namespace{ActorLibrary::Registrar<x> registrar(#x);}

}