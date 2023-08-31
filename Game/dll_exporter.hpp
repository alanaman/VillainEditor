#pragma once

#include <string>
#include "Actor.hpp"
#include "editor_rep.hpp"


extern "C" __declspec(dllexport) villain::Actor* createActor(const std::string& name);

extern "C" __declspec(dllexport) const std::map<std::string, villain::Actor* (*)()>& getActorMap();

//extern "C" __declspec(dllexport) std::shared_ptr<villain::Actor> createActorsh(std::string name);

//extern "C" __declspec(dllexport) void set_spawnFP(std::shared_ptr<villain::Actor>(*spawnActor_FP)(std::string));

//these are used to create a EditorRep instance to set callback functions.
//delete the instance after the static function pointers are set.
extern "C" __declspec(dllexport) void* createEditorRepInstance() { return (void*)(new EditorRep()); };
extern "C" __declspec(dllexport) void deleteEditorRepInstance(void* editorRepPtr) { delete (EditorRep*)editorRepPtr; };


////export class functions here.
//extern "C" __declspec(dllexport) ret_type classname_funcname(void* obj_ptr, Args...);
//
//ret_type classname_funcname(void* obj_ptr, Args...)
//{
// return ((classname*)obj_ptr)->funcname(Args...);
//}

