#pragma once

#include "logging.hpp"
#include "name_handler.hpp"
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

#include "graphics/mesh.hpp"
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
 //static std::vector<std::string> names;
 //static std::vector<int> n_users;
 //static std::vector<std::shared_ptr<void>> load_point;

 struct MeshEntry
 {
  std::string name;
  int n_users;
  std::shared_ptr<void> load_point;
 };

 static int nxt_id;
 static std::unordered_map<MeshId, MeshEntry> id_meshentry;
 static NameHandler mName_handler;

 static std::unordered_map<MeshId, MeshEntry>& getEntriesRef();//for gui

//TODO cahnge data queries to use index instaed of names;
 static void addEntry(std::string name);
 //static bool processNode(const aiNode* node, const aiScene* scene, const std::string& directory);
 static bool processMeshes(const aiScene* scene, const std::string& filename);
public:
 static MeshId getId(const std::string name);
 static void init();
 static void createMeshFromFile();
 static void deleteMesh(MeshId mesh_id);
 static void incrementUsers(MeshId mesh_id);
 static void decrementUsers(MeshId mesh_id);
 static bool hasUsers(MeshId mesh_id);

 //static void updateDefaultMaterials(std::string& name, std::vector<std::shared_ptr<Material>>& materials);
 static void updateDefaultMaterialIds(MeshId mesh_id, std::vector<int>& material_ids);
 //static std::vector<std::shared_ptr<Material>> getDefaultMaterials(std::string& name);
 static std::vector<int> getDefaultMaterialIds(MeshId mesh_id);

 static void setLoadPoint(MeshId mesh_id, std::shared_ptr<void> ptr);
 static std::shared_ptr<void> getLoadPoint(MeshId mesh_id);

 //static void getMeshData(std::string name, std::vector<MeshData>& data);
 static void getMeshData(MeshId id, std::vector<MeshData>& data);

 friend class AssetLibrary;
 friend class PropertiesPanel;
};
}

