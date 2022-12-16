#include "actor_library.hpp"
#include "meshlibrary.hpp"
#include "logging.hpp"
#include "actor.hpp"
#include "mesh.hpp"

namespace villain {


class Gunner : public Actor
{
private:
 std::shared_ptr<Mesh> gunner_mesh;

public:
 static std::shared_ptr<Actor> create();

 Gunner(std::string name);
 virtual void beginPlay() override;
 virtual void updateOnFrame() override;



 virtual void getMesh(std::vector<std::shared_ptr<Mesh>>& meshes) override;


};
}