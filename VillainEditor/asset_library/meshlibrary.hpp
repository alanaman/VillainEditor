#include "logging.hpp"
#include "window/filedialog.hpp"
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <../external/glm/glm/glm.hpp>


#include <cereal/archives/binary.hpp>
#include <cereal/access.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>



namespace villain {

#define LIB_FOLDER "./asset_library"
#define MESH_LIB_FOLDER "./asset_library/mesh_library"
#define MESH_FILE_NAME "mesh.pkd"

struct MeshData
{
 std::vector<int> indices;
 std::vector<glm::vec3> positions;
 std::vector<glm::vec3> normals;
 std::vector<glm::vec4> colors;
 std::vector<glm::vec2> tex_coords;
};


class MeshLibrary
{
 static std::vector<std::string> names;
 static std::vector<int> n_users;
 static std::vector<std::shared_ptr<void>> load_point;

 static void addEntry(std::string name);
 static bool processNode(const aiNode* node, const aiScene* scene, const std::string& directory);
 static bool processMesh(const aiMesh* ai_mesh, const aiScene* scene, const std::string& directory);
 static int getIndex(std::string& name);
public:
 static void init();
 static void createMeshFromFile();
 //static void deleteMesh();
 static void incrementUsers(std::string& name);
 static void decrementUsers(std::string& name);
 static bool hasUsers(std::string& name);

 static void setLoadPoint(std::string& name, std::shared_ptr<void> ptr);
 static std::shared_ptr<void> getLoadPoint(std::string& name);

 static const std::vector<std::string>& getMeshListRef();
 static std::shared_ptr<MeshData> getMeshData(std::string name);

};
}

namespace glm {
template<class Archive>
void serialize(Archive& archive, glm::vec2& m)
{
 archive(m.x, m.y);
};
template<class Archive>
void serialize(Archive& archive, glm::vec3& m)
{
 archive(m.x, m.y, m.z);
};
template<class Archive>
void serialize(Archive& archive, glm::vec4& m)
{
 archive(m.r, m.g, m.b, m.a);
};
}