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

 int name_start = filepath.find_last_of("\\");
 int name_end = filepath.find_last_of(".");
 auto name = filepath.substr(name_start + 1, name_end - name_start - 1);
 if (getIndex(name) != -1)
 {
  auto new_name = name;
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
 if (processNode(scene->mRootNode, scene, mesh_dir))
  addEntry(name);


 //TODO read and create folders+datafiles;

}

void MeshLibrary::incrementUsers(std::string& name)
{
 n_users[getIndex(name)]++;
}

void MeshLibrary::decrementUsers(std::string& name)
{
 int index = getIndex(name);
 if (n_users[index] == 0)
  ERROR();
 n_users[index]--;
}

bool MeshLibrary::hasUsers(std::string& name)
{
 if (n_users[getIndex(name)] == 0)
  return false;
 return true;
}

void MeshLibrary::setLoadPoint(std::string& name, std::shared_ptr<void> ptr)
{
 load_point[getIndex(name)] = ptr;
}

std::shared_ptr<void> MeshLibrary::getLoadPoint(std::string& name)
{
 return load_point[getIndex(name)];
}

const std::vector<std::string>& MeshLibrary::getMeshListRef()
{
 return names;
}

std::shared_ptr<MeshData> MeshLibrary::getMeshData(std::string name)
{
 auto mesh_data = std::make_shared<MeshData>();
 auto filename = std::string(MESH_LIB_FOLDER) + "/" + name + "/" + MESH_FILE_NAME;
 std::ifstream file;
 file.open(filename, std::ios::binary);
 cereal::BinaryInputArchive archive(file);
 archive(
  mesh_data->indices,
  mesh_data->positions,
  mesh_data->normals,
  mesh_data->colors,
  mesh_data->tex_coords
 );

 return mesh_data;
}

void MeshLibrary::addEntry(std::string name)
{
 names.push_back(name);
 n_users.push_back(0);
 load_point.push_back(NULL);
}

bool MeshLibrary::processNode(const aiNode* node, const aiScene* scene, const std::string& directory)
{
 //find a mesh and process it
 for (unsigned int i = 0; i < node->mNumMeshes; i++)
 {
  
  aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
  processMesh(mesh, scene, directory);
  return true;
 }

 for (unsigned int i = 0; i < node->mNumChildren; i++)
 {
  if (processNode(node->mChildren[i], scene, directory))
   return true;
 }
 return false;
}

bool MeshLibrary::processMesh(const aiMesh* ai_mesh, const aiScene* scene, const std::string& directory)
{

 std::vector<unsigned int> indices(ai_mesh->mNumFaces * 3);
 std::vector<glm::vec3> positions(ai_mesh->mNumVertices);
 std::vector<glm::vec3> normals(ai_mesh->mNumVertices);
 std::vector<glm::vec4> colors(ai_mesh->mNumVertices);
 std::vector<glm::vec2> tex_coords(ai_mesh->mNumVertices);
 
 //loading into these vectors
 {
  for (unsigned int i = 0; i < ai_mesh->mNumFaces; i++)
  {
   aiFace& face = ai_mesh->mFaces[i];
   ASSERT(face.mNumIndices == 3);
   for (unsigned int j = 0; j < 3; j++)
    indices[3 * i + j] = face.mIndices[j];
  }
  for (int i = 0; i < ai_mesh->mNumVertices; i++)
  {
   positions[i].x = ai_mesh->mVertices[i].x;
   positions[i].y = ai_mesh->mVertices[i].y;
   positions[i].z = ai_mesh->mVertices[i].z;
   normals[i].x = ai_mesh->mNormals[i].x;
   normals[i].y = ai_mesh->mNormals[i].y;
   normals[i].z = ai_mesh->mNormals[i].z;
  }
  if (ai_mesh->mTextureCoords[0] != NULL)
   for (int i = 0; i < ai_mesh->mNumVertices; i++)
   {
    tex_coords[i].x = ai_mesh->mTextureCoords[0][i].x;
    tex_coords[i].y = ai_mesh->mTextureCoords[0][i].y;
   }
  else
   for (int i = 0; i < ai_mesh->mNumVertices; i++)
   {
    tex_coords[i].x = 0;
    tex_coords[i].y = 0;
   }
  if (ai_mesh->mColors[0] != NULL)
   for (int i = 0; i < ai_mesh->mNumVertices; i++)
   {
    colors[i].r = ai_mesh->mColors[0][i].r;
    colors[i].g = ai_mesh->mColors[0][i].g;
    colors[i].b = ai_mesh->mColors[0][i].b;
    colors[i].a = ai_mesh->mColors[0][i].a;
   }
  else
   for (int i = 0; i < ai_mesh->mNumVertices; i++)
   {
    colors[i].r = 1;
    colors[i].g = 1;
    colors[i].b = 1;
    colors[i].a = 1;
   }
 }

 //save to file
 auto filename = directory + "/" + MESH_FILE_NAME;
 std::ofstream file;
 file.open(filename, std::ios::binary);
 cereal::BinaryOutputArchive archive(file);
 archive(indices, positions, normals, colors, tex_coords);

 return true;
}

int MeshLibrary::getIndex(std::string& name)
{
 for (int i = 0; i < names.size(); i++)
 {
  if (names[i] == name)
   return i;
 }
 return -1;
}

}