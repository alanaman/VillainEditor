#include "actor_registrar.hpp"

namespace villain {

std::map<std::string, ActorDllLibrary::create_funtion>& ActorDllLibrary::actor_list()
{
 static std::map<std::string, ActorDllLibrary::create_funtion> register_impl;
 return register_impl;
}
}