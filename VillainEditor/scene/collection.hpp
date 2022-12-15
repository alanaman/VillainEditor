#include "logging.hpp"
#include "entity.hpp"



namespace villain {

class Collection
{
 static int next_id;
public:
 int id;
 std::string name;

 bool is_selected = false;

 std::vector<std::shared_ptr<Collection>> child_collections;
 std::vector<std::shared_ptr<Entity>> child_entities;

 Collection();
 Collection(std::string name);
 void addCollection(std::shared_ptr<Collection> coll);
 void addEntity(std::shared_ptr<Entity> entt);
 bool isParentOf(std::shared_ptr<Collection> coll);

 static void resetIdCount();

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   CEREAL_NVP(id),
   CEREAL_NVP(name),
   CEREAL_NVP(is_selected),
   CEREAL_NVP(child_collections),
   CEREAL_NVP(child_entities)
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   id,
   name,
   is_selected,
   child_collections,
   child_entities
  );
 };
 friend class cereal::access;
};
}