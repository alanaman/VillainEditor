#include "logging.hpp"
#include "entity.hpp"
#include "mesh.hpp"

namespace villain {

class StaticMesh : public Entity
{
 std::shared_ptr<Mesh> mesh;

public:
 StaticMesh(std::shared_ptr<Mesh>& mesh);
 StaticMesh(std::string name, std::shared_ptr<Mesh>& mesh);
 std::shared_ptr<Mesh> getModel();
};

}