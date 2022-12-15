#include "VillainEditor.hpp"


int main()
{
 villain::Editor editor;
 editor.run();
}
//#include "logging.hpp"

//#include "base.hpp"
//#include "derived.hpp"
//
//
//
//using namespace villain;
//int main()
//{
//
// std::string workPath = "./";
//
// {
//  std::ofstream os(workPath + "polymorphism_test.json");
//  cereal::JSONOutputArchive oarchive(os);
//
//  std::shared_ptr<Base> ptr1 = std::make_shared<A>();
//
//
//  oarchive(ptr1);
// }
//
// {
//  std::ifstream is(workPath + "polymorphism_test.json");
//  cereal::JSONInputArchive iarchive(is);
//  std::shared_ptr<Base> ptr1;
//  iarchive(ptr1);
// }
//
// return 0;
//}

//#include "static_mesh.hpp"
//#include "entity.hpp"
//using namespace villain;
//int main()
//{
//
// std::string workPath = "./";
//
// {
//  std::ofstream os(workPath + "polymorphism_test.json");
//  cereal::JSONOutputArchive oarchive(os);
//
//  std::shared_ptr<Entity> ptr1 = std::make_shared<StaticMesh>();
//
//
//  oarchive(ptr1);
// }
//
// {
//  std::ifstream is(workPath + "polymorphism_test.json");
//  cereal::JSONInputArchive iarchive(is);
//  std::shared_ptr<Entity> ptr1;
//  iarchive(ptr1);
// }
//
// return 0;
//}