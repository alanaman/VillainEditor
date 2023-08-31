#include "dll_importer.hpp"
#include "asset_library/actor_library.hpp"


namespace villain {


//Actor* DllImporter::createActor(std::string name)
//{
// return createActorFP(name);
//}

bool DllImporter::load(const std::string& projectFolder)
{
 m_dllHandle = LoadLibrary(L"E:\\Villain\\VillainEditor\\x64\\Debug\\Game.dll");
 if (m_dllHandle == nullptr) {
  //TODO: Handle error
  return false;
 }

 ActorLibrary::createActorFP = reinterpret_cast<ActorLibrary::createActorFT>(
  GetProcAddress(m_dllHandle, "createActor"));
 if (ActorLibrary::createActorFP == nullptr)
  return false;

 createEditorRepFP = reinterpret_cast<createEditorRepFT>(
  GetProcAddress(m_dllHandle, "createEditorRepInstance"));
 if (createEditorRepFP == nullptr)
  return false;


 using getActorMapFT = const std::map<std::string, Actor* (*)()>& (*)();
 getActorMapFT getActorMapFP = reinterpret_cast<getActorMapFT>(
  GetProcAddress(m_dllHandle, "getActorMap"));
 ActorLibrary::updateActorsFromDll(getActorMapFP());

 return true;
}

void DllImporter::unload()
{
 FreeLibrary(m_dllHandle);
}




}