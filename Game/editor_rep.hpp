#pragma once
#include "dll_handover_interface.hpp"

class EditorRep : public villain::FunctionHandoverPrivateInterface
{
 static int (*m_getMeshIdFP)(const std::string&);
 virtual void set_getMeshIdFP(int (*getMeshIdFP)(const std::string&)) override { m_getMeshIdFP = getMeshIdFP; };

public:
 static int getMeshId(std::string& path) { return m_getMeshIdFP(path); };
};
