#include "meshlibrary.hpp"


namespace villain {

std::vector<std::string> MeshLibrary::names;
std::vector<int> MeshLibrary::n_users;
std::vector<std::shared_ptr<void>> MeshLibrary::load_point;


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

  if (entry.is_directory())
  {
   std::stringstream ss;
   ss << entry.path().filename();
   auto temp = ss.str();
   addEntry(temp.substr(1, temp.length()-2));
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
 if (getIndex(name) != -1)
 {
  std::string new_name = name;
  int i = 1;
  while (getIndex(new_name) != -1)
  {
   auto numstr = std::to_string(i);
   new_name = name + "." + std::string(4 - numstr.size(), '0') + numstr;
  }
  name = new_name;
 }
 
 std::string mesh_dir = MESH_LIB_FOLDER + ("/" + name);

 std::filesystem::create_directory(mesh_dir);


 Assimp::Importer importer;
 const aiScene* scene = importer.ReadFile(
  filepath,
  aiProcess_Triangulate | aiProcess_FlipUVs);
 if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
 {
  ERROR("ASSIMP::" << import.GetErrorString());
  return;
 }
 if (processMeshes(scene, mesh_dir))
  addEntry(name);
 //TODO read and create folders+datafiles;

}

void MeshLibrary::deleteMesh(int index)
{
 if (n_users[index] != 0)
  INFO("mesh has " << n_users[index] << " users: cant delete")
 else
 {
  std::filesystem::remove_all(MESH_LIB_FOLDER + std::string("/") + names[index]);
  names.erase(std::next(names.begin(), index));
  n_users.erase(std::next(n_users.begin(), index));
  load_point.erase(std::next(load_point.begin(), index));
 }
}

void MeshLibrary::incrementUsers(std::string& name)
{
 n_users[getIndex(name)]++;
}

void MeshLibrary::decrementUsers(std::string& name)
{
 int index = getIndex(name);
 if (n_users[index] == 0)
  ERROR("number of user cant be negative: only active users can call decrementUsers");
 n_users[index]--;
}

bool MeshLibrary::hasUsers(std::string& name)
{
 if (n_users[getIndex(name)] == 0)
  return false;
 return true;
}

void MeshLibrary::updateDefaultMaterials(std::string& name, std::vector<std::shared_ptr<Material>>& materials)
{
 auto filename = MESH_LIB_FOLDER + std::string("/") + name + "/" + MATERIAL_FILE_NAME;
 std::ofstream file;
 file.open(filename, std::ios::binary);
 cereal::BinaryOutputArchive archive(file);
 archive(materials);
 file.close();
}

std::vector<std::shared_ptr<Material>> MeshLibrary::getDefaultMaterials(std::string& name)
{
 std::vector<std::shared_ptr<Material>> result;
 auto filename = std::string(MESH_LIB_FOLDER) + "/" + name + "/" + MATERIAL_FILE_NAME;
 std::ifstream file;
 file.open(filename, std::ios::binary);
 cereal::BinaryInputArchive archive(file);
 archive(
  result
 );
 return result;
}

void MeshLibrary::setLoadPoint(std::string& name, std::shared_ptr<void> ptr)
{
 load_point[getIndex(name)] = ptr;
}

std::shared_ptr<void> MeshLibrary::getLoadPoint(std::string& name)
{
 return load_point[getIndex(name)];
}

std::vector<std::string>& MeshLibrary::getMeshListRef()
{
 return names;
}

void MeshLibrary::getMeshData(std::string name, std::vector<MeshData>& data)
{
 auto filename = std::string(MESH_LIB_FOLDER) + "/" + name + "/" + MESH_FILE_NAME;
 std::ifstream file;
 file.open(filename, std::ios::binary);
 cereal::BinaryInputArchive archive(file);
 archive(
  data
 );
}

void MeshLibrary::addEntry(std::string name)
{
 names.push_back(name);
 n_users.push_back(0);
 load_point.push_back(NULL);
}

bool MeshLibrary::processNode(const aiNode* node, const aiScene* scene, const std::string& directory)
{
 for (unsigned int i = 0; i < node->mNumChildren; i++)
 {
  if (processNode(node->mChildren[i], scene, directory))
   return true;
 }
 return false;
}

bool MeshLibrary::processMeshes(const aiScene* scene, const std::string& directory)
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
  auto filename = directory + "/" + MESH_FILE_NAME;
  std::ofstream file;
  file.open(filename, std::ios::binary);
  cereal::BinaryOutputArchive archive(file);
  archive(meshdata);
  file.close();
 }
 //save default shaders for all mesh parts
 {
  std::vector<std::shared_ptr<Material>> materials(meshdata.size(), MaterialLibrary::getDefaultMaterial());
  auto filename = directory + "/" + MATERIAL_FILE_NAME;
  std::ofstream file;
  file.open(filename, std::ios::binary);
  cereal::BinaryOutputArchive archive(file);
  archive(materials);
  file.close();
 }
 return true;
}

int MeshLibrary::getIndex(const std::string& name)
{
 for (int i = 0; i < names.size(); i++)
 {
  if (names[i] == name)
   return i;
 }
 return -1;
}

}