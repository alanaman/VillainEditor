#pragma once

#include "logging.hpp"
#include "window/filedialog.hpp"
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>


#include <cereal/archives/binary.hpp>
#include <cereal/access.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include "asset_lib_macros.hpp"
#include "asset_library/material_library.hpp"

namespace villain {

struct MeshData
{
 std::vector<int> indices;
 std::vector<glm::vec3> positions;
 std::vector<glm::vec3> normals;
 std::vector<glm::vec4> colors;
 std::vector<glm::vec2> tex_coords;

 template<class Archive>
 void save(Archive& archive) const
 {
  archive(
   indices,
   positions,
   normals,
   colors,
   tex_coords
  );
 };
 template<class Archive>
 void load(Archive& archive)
 {
  archive(
   indices,
   positions,
   normals,
   colors,
   tex_coords
  );
 };
};


class MeshLibrary
{
 static std::vector<std::string> names;
 static std::vector<int> n_users;
 static std::vector<std::shared_ptr<void>> load_point;

//TODO cahnge data queries to use index instaed of names;
 static void addEntry(std::string name);
 static bool processNode(const aiNode* node, const aiScene* scene, const std::string& directory);
 static bool processMeshes(const aiScene* scene, const std::string& directory);
public:
 static int getIndex(const std::string& name);
 static void init();
 static void createMeshFromFile();
 static void deleteMesh(int index);
 static void incrementUsers(std::string& name);
 static void decrementUsers(std::string& name);
 static bool hasUsers(std::string& name);

 static void updateDefaultMaterials(std::string& name, std::vector<std::shared_ptr<Material>>& materials);
 static std::vector<std::shared_ptr<Material>> getDefaultMaterials(std::string& name);

 static void setLoadPoint(std::string& name, std::shared_ptr<void> ptr);
 static std::shared_ptr<void> getLoadPoint(std::string& name);

 static std::vector<std::string>& getMeshListRef();
 static void getMeshData(std::string name, std::vector<MeshData>& data);

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