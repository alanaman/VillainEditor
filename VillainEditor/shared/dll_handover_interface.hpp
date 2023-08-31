#pragma once

#include "logging.hpp"

namespace villain {

class FunctionHandoverPrivateInterface
{
 virtual void set_getMeshIdFP(int (*getMeshIdFP)(const std::string&)) = 0;
 //virtual void set_SpawnActorFP(void (*getMeshIdFP)(ActorId)) = 0;
public:

 friend class FunctionHandoverInterface;
};

class FunctionHandoverInterface
{
 FunctionHandoverPrivateInterface* m_actualInterface;
public:
 FunctionHandoverInterface(void* dllInterfaceObjPtr) :m_actualInterface((FunctionHandoverPrivateInterface*)dllInterfaceObjPtr) {};

 void set_getMeshIdFP(int (*getMeshIdFP)(const std::string&)) { m_actualInterface->set_getMeshIdFP(getMeshIdFP); };

};

}

