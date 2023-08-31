#include "shader_library.hpp"

namespace villain {

std::vector<std::shared_ptr<Shader>> ShaderLibrary::shaders;
std::shared_ptr<Shader> ShaderLibrary::default_shader;

std::string ShaderLibrary::readShaderFromFile(std::string& filepath)
{
 std::ifstream shaderFile(filepath.c_str());
 if (!shaderFile.is_open())
  VLLN_ERR("Cannot find file: " + filepath);
 std::stringstream shaderData;
 shaderData << shaderFile.rdbuf();
 shaderFile.close();
 return shaderData.str();
}

void ShaderLibrary::init()
{
 std::vector<ShaderFiles> shader_list;

 std::string path = SHADER_LIB_FOLDER;
 for (const auto& entry : std::filesystem::directory_iterator(path))
 {
  std::cout << entry.path() << std::endl;

  if (entry.is_regular_file())
  {
   std::string filepath = entry.path().generic_string();

   auto name_start = filepath.find_last_of("/");
   auto name_end = filepath.length() - 10;
   auto name = filepath.substr(name_start + 1, name_end - name_start - 1);
   auto type = filepath.substr(name_end + 1, 4);

   if (type != "vert" && type != "frag" && type != "geom")
    continue;
   bool found = false;
   for (auto& shaderfiles : shader_list)
   {
    if (name == shaderfiles.name)
    {
     found = true;
     shaderfiles.addShaderPath(filepath, type);
    }
   }

   if (!found)
   {
    ShaderFiles new_shaderfiles;
    new_shaderfiles.name = name;
    new_shaderfiles.addShaderPath(filepath, type);
    shader_list.push_back(new_shaderfiles);
   }
  }
 }
 for (auto& shaderfiles : shader_list)
 {
  if (shaderfiles.name == "default")
  {
   auto vertex_shader = readShaderFromFile(shaderfiles.vert);
   auto fragment_shader = readShaderFromFile(shaderfiles.frag);
   default_shader = Shader::create(shaderfiles.name, vertex_shader, fragment_shader);
  }
  if (shaderfiles.geom == "")
  {
   auto vertex_shader = readShaderFromFile(shaderfiles.vert);
   auto fragment_shader = readShaderFromFile(shaderfiles.frag);
   shaders.push_back(Shader::create(shaderfiles.name, vertex_shader, fragment_shader));
  }
  else
  {
   auto vertex_shader = readShaderFromFile(shaderfiles.vert);
   auto geometry_shader = readShaderFromFile(shaderfiles.geom);
   auto fragment_shader = readShaderFromFile(shaderfiles.frag);
   shaders.push_back(Shader::create(shaderfiles.name, vertex_shader, geometry_shader, fragment_shader));
  }
 }

}

std::shared_ptr<Shader> ShaderLibrary::getDefaultShader()
{
 if (default_shader == NULL)
  VLLN_ERR("default shader not initialized");
 return default_shader;
}

void ShaderLibrary::setCameraMatrix(const glm::mat4& camMatrix)
{
 default_shader->bind();
 default_shader->setUniformMat4("uProjViewModelMat", camMatrix);
 
 for (auto& shader : shaders)
 {
  shader->bind();
  shader->setUniformMat4("uProjViewModelMat", camMatrix);
 }
}

std::shared_ptr<Shader> ShaderLibrary::getShaderByName(std::string& name)
{
 for (int i = 0; i < shaders.size(); i++)
 {
  if (shaders[i]->getName() == name)
   return shaders[i];
 }
 WARNING("shader with name: " << name << " doesn't exist");
 return getDefaultShader();
}

}//end namespace villain