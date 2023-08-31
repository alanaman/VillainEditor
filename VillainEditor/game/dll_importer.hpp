#pragma once
#include "actor.hpp"
#include <Windows.h>
#include "alternate_impl/mesh_component.hpp"
#include "dll_handover_interface.hpp"

namespace villain {

class DllImporter
{
 //copy from bin path to load path before loading.
 HMODULE m_dllHandle;

 //using createActorFT = Actor*(*)(std::string);
 //createActorFT createActorFP;

 using createEditorRepFT = void*(*)();

 createEditorRepFT createEditorRepFP;

public:

 //Actor* createActor(std::string name);

 void* getEditorRep() { return createEditorRepFP(); };

 bool load(const std::string& projectFolder);
 //void reload();
 void unload();


};

}