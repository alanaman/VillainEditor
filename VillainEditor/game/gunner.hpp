#include "logging.hpp"
#include "actor.hpp"
#include "mesh.hpp"

namespace villain {


class Gunner : public Actor
{
private:
 std::shared_ptr<Mesh> mesh;

public:
 Gunner(std::string name, std::shared_ptr<Mesh> mesh);
 virtual void beginPlay() override;
 virtual void updateOnFrame() override;

 virtual std::shared_ptr<Mesh> getMesh() override;

};
}