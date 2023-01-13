#include "meshlibrary.hpp"


namespace villain {

//std::vector<std::string> MeshLibrary::names;
//std::vector<int> MeshLibrary::n_users;
//std::vector<std::shared_ptr<void>> MeshLibrary::load_point;

int MeshLibrary::nxt_id = 0;

std::unordered_map<MeshId, MeshLibrary::MeshEntry> MeshLibrary::id_meshentry;

MeshId MeshLibrary::getId(const std::string name)
{
 for (const auto& mesh : id_meshentry)
 {
  if (mesh.second.name == name)
   return mesh.first;
 }
 ERROR("invalid mesh");//TODO make this warning and make null mesh work
 return -1;
}

void MeshLibrary::init()
{
 if(!std::filesystem::exists(LIB_FOLDER))
  std::filesystem::create_directory(LIB_FOLDER);

 std::string path = MESH_LIB_FOLDER;
 if (!std::filesystem::exists(path))
  std::filesystem::create_directory(path);
 for (const auto& entry : std::filesystem::directory_iterator(path))
 {
  std::cout << entry.path() << std::endl;

  if (entry.is_regular_file())
  {
   std::stringstream ss;
   auto filepath = std::string((char*)entry.path().c_str());
   auto filename = std::string((char*)entry.path().filename().c_str());
   std::ifstream file;
   file.open(filepath, std::ios::binary);
   cereal::BinaryInputArchive archive(file);
   int id;
   archive(id);
   id_meshentry[id] = { filename, 0, NULL };

  }
 }
}

void MeshLibrary::createMeshFromFile()
{
 std::string filepath = FileBrowser::selectFile();
 if (filepath == "")
  return;
 std::cout << filepath << std::endl;

 auto name_start = filepath.find_last_of("\\");
 auto name_end = filepath.find_last_of(".");
 auto name = filepath.substr(name_start + 1, name_end - name_start - 1);
 
 auto filename = MESH_LIB_FOLDER + ("/" + name + ".mesh");
 if (std::filesystem::exists(filename))
 {
  INFO("mesh with same name already exists. import cancelled");
 }


 Assimp::Importer importer;
 const aiScene* scene = importer.ReadFile(
  filepath,
  aiProcess_Triangulate | aiProcess_FlipUVs);
 if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
 {
  ERROR("ASSIMP::" << import.GetErrorString());
  return;
 }
 if (processMeshes(scene, MESH_LIB_FOLDER + std::string("/") + name))
  addEntry(name);
 //TODO read and create folders+datafiles;

}

void MeshLibrary::deleteMesh(MeshId mesh_id)
{
 if (id_meshentry[mesh_id].n_users != 0)
  INFO("mesh has " << id_meshentry[mesh_id].n_users << " users: cant delete")
 else
 {
  std::filesystem::remove(MESH_LIB_FOLDER + std::string("/") + id_meshentry[mesh_id].name);
  id_meshentry.erase(mesh_id);
 }
}

void MeshLibrary::incrementUsers(MeshId mesh_id)
{
 id_meshentry[mesh_id].n_users++;
}

void MeshLibrary::decrementUsers(MeshId mesh_id)
{
 int n_users = id_meshentry[mesh_id].n_users;
 if (n_users == 0)
  ERROR("number of user cant be negative: only active users can call decrementUsers");
 id_meshentry[mesh_id].n_users--;
}

bool MeshLibrary::hasUsers(MeshId mesh_id)
{
 return  id_meshentry[mesh_id].n_users != 0;
}

void MeshLibrary::updateDefaultMaterialIds(MeshId mesh_id, std::vector<int>& material_ids)
{
 if (!id_meshentry.count(mesh_id))
 {
  WARNING("mesh with given id does not exist");
  return;
 }
 auto filename = MESH_LIB_FOLDER + std::string("/") + id_meshentry[mesh_id].name + "/" + MATERIAL_FILE_NAME;
 std::ofstream file;
 file.open(filename, std::ios::binary);
 cereal::BinaryOutputArchive archive(file);
 archive(material_ids);
 file.close();
}

std::vector<int> MeshLibrary::getDefaultMaterialIds(MeshId mesh_id)
{
 if (!id_meshentry.count(mesh_id))
 {
  WARNING("mesh with given id does not exist");
  return std::vector<int>();
 }
 int id;
 std::vector<MeshData> meshdata;
 std::vector<int> result;
 auto filename = std::string(MESH_LIB_FOLDER) + "/" + id_meshentry[mesh_id].name;
 std::ifstream file;
 file.open(filename, std::ios::binary);
 cereal::BinaryInputArchive archive(file);
 archive(id);
 archive(meshdata);
 archive(result);
 return result;
}

void MeshLibrary::setLoadPoint(MeshId mesh_id, std::shared_ptr<void> ptr)
{
 id_meshentry[mesh_id].load_point = ptr;
}

std::shared_ptr<void> MeshLibrary::getLoadPoint(MeshId mesh_id)
{
 return id_meshentry[mesh_id].load_point;
}


void MeshLibrary::getMeshData(MeshId mesh_id, std::vector<MeshData>& data)
{
 auto filename = std::string(MESH_LIB_FOLDER) + "/" + id_meshentry[mesh_id].name;
 std::ifstream file;
 file.open(filename, std::ios::binary);
 cereal::BinaryInputArchive archive(file);
 int id;
 archive(id);
 archive(data);
}

std::unordered_map<MeshId, MeshLibrary::MeshEntry>& MeshLibrary::getEntriesRef()
{
 return id_meshentry;
}

void MeshLibrary::addEntry(std::string name)
{
 //names.push_back(name);
 //n_users.push_back(0);
 //load_point.push_back(NULL);
 id_meshentry[nxt_id] = { name, 0, NULL };
 nxt_id++;
}

//bool MeshLibrary::processNode(const aiNode* node, const aiScene* scene, const std::string& directory)
//{
// for (unsigned int i = 0; i < node->mNumChildren; i++)
// {
//  if (processNode(node->mChildren[i], scene, directory))
//   return true;
// }
// return false;
//}

bool MeshLibrary::processMeshes(const aiScene* scene, const std::string& filename)
{
 std::vector<MeshData> meshdata(scene->mNumMeshes);

 for (unsigned int m = 0; m < scene->mNumMeshes; m++)
 {
  aiMesh* mesh = scene->mMeshes[m];

  meshdata[m].indices.resize(mesh->mNumFaces * 3);
  meshdata[m].positions.resize(mesh->mNumVertices);
  meshdata[m].normals.resize(mesh->mNumVertices);
  meshdata[m].colors.resize(mesh->mNumVertices);
  meshdata[m].tex_coords.resize(mesh->mNumVertices);

  //loading into these vectors
  {
   for (unsigned int i = 0; i < mesh->mNumFaces; i++)
   {
    aiFace& face = mesh->mFaces[i];
    ASSERT(face.mNumIndices == 3);
    for (unsigned int j = 0; j < 3; j++)
     meshdata[m].indices[3 * i + j] = face.mIndices[j];
   }
   for (unsigned int i = 0; i < mesh->mNumVertices; i++)
   {
    meshdata[m].positions[i].x = mesh->mVertices[i].x;
    meshdata[m].positions[i].y = mesh->mVertices[i].y;
    meshdata[m].positions[i].z = mesh->mVertices[i].z;
    meshdata[m].normals[i].x = mesh->mNormals[i].x;
    meshdata[m].normals[i].y = mesh->mNormals[i].y;
    meshdata[m].normals[i].z = mesh->mNormals[i].z;
   }
   if (mesh->mTextureCoords[0] != NULL)
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
     meshdata[m].tex_coords[i].x = mesh->mTextureCoords[0][i].x;
     meshdata[m].tex_coords[i].y = mesh->mTextureCoords[0][i].y;
    }
   else
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
     meshdata[m].tex_coords[i].x = 0;
     meshdata[m].tex_coords[i].y = 0;
    }
   if (mesh->mColors[0] != NULL)
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
     meshdata[m].colors[i].r = mesh->mColors[0][i].r;
     meshdata[m].colors[i].g = mesh->mColors[0][i].g;
     meshdata[m].colors[i].b = mesh->mColors[0][i].b;
     meshdata[m].colors[i].a = mesh->mColors[0][i].a;
    }
   else
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
     meshdata[m].colors[i].r = 1;
     meshdata[m].colors[i].g = 1;
     meshdata[m].colors[i].b = 1;
     meshdata[m].colors[i].a = 1;
    }
  }
 }

 //save to file
 {
  std::ofstream file;
  file.open(filename, std::ios::binary);
  cereal::BinaryOutputArchive archive(file);
  std::vector<int> default_materials(meshdata.size(), -1);
  archive(nxt_id);
  archive(meshdata);
  archive(default_materials);
  file.close();
 }
 return true;
}

//int MeshLibrary::getId(const std::string& name)
//{
// for (int i = 0; i < names.size(); i++)
// {
//  if (names[i] == name)
//   return i;
// }
// return -1;
//}

}