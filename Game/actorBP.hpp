#pragma once

#include "entity.hpp"


namespace villain {

//class Actor;
//
//class World
//{
//private:
//public:
// std::shared_ptr<Actor>(*spawnActor_FP)(std::string);
// std::shared_ptr <Actor> spawnActor(std::string x) { return spawnActor_FP(x); };
//};

class Actor: public Entity
{
protected:
public:
 Properties p;
 //static World world;//in dll_exporter.cpp
 //World& getWorld() { return world; };

 Actor() {};
 Transform& getActorTransform() { return m_transform; };
 void setActorTransform(const Transform& t) { m_transform = t; };
 //Actor(std::string name);
 
 virtual void beginPlay() {};
 virtual void actorBeginOverlap(Actor& otherActor) {};
 virtual void updateOnFrame(const float& deltatime) {};

 virtual void collectMeshes() {};

 //virtual void collectProperties(Properties& properties) override;

 //template<class Archive>
 //void save(Archive& archive) const
 //{
 // archive(
 //  cereal::base_class<Entity>(this)
 // );
 //};
 //template<class Archive>
 //void load(Archive& archive)
 //{
 // archive(
 //  cereal::base_class<Entity>(this)
 // );
 //};
 //friend class cereal::access;
};
}

//CEREAL_REGISTER_TYPE(villain::Actor);
