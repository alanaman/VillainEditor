#include "actor_library.hpp"

namespace villain {

std::map<std::string, ActorLibrary::create_funtion*>& ActorLibrary::actor_list()
{
 static std::map<std::string, ActorLibrary::create_funtion*> register_impl;
 return register_impl;
}
}