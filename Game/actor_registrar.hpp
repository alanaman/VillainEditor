#pragma once

#include "logging.hpp"
#include <memory>
#include <string>

#include "actor.hpp"

namespace villain {


class ActorDllLibrary
{
public:
 using create_funtion = Actor*(*)();

private:
 static void registerMethod(std::string const& name, create_funtion fp)
 {
  actor_list().insert({ name, fp });
 }
public:
 static Actor* instantiate(std::string const& name)
 {
  auto it = actor_list().find(name);
  if (it == actor_list().end())
   return nullptr;
  else
   return it->second();
 }
 //static std::shared_ptr<Actor> instantiate(int index)
 //{
 // if (index >= actor_list().size())
 //  return NULL;
 // auto actor = actor_list().begin();
 // std::advance(actor, index);
 // return actor->second();
 //}

 template <typename DerivedActor>
 struct Registrar
 {
  explicit Registrar(std::string const& name)
  {
   ActorDllLibrary::registerMethod(name, DerivedActor::create);
  }
  Registrar(const Registrar&) = delete;
  Registrar& operator=(const Registrar&) = delete;
 };

 //in function form so that map is initialized before insert is called
 static std::map<std::string, create_funtion>& actor_list();
};

#define REGISTER_ACTOR(x) namespace{ActorDllLibrary::Registrar<x> registrar(#x);}

}