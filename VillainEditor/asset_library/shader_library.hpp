#pragma once

#include "logging.hpp"
#include "window/filedialog.hpp"
#include <filesystem>

#include "graphics/material.hpp"

#include "asset_lib_macros.hpp"

namespace villain {

class ShaderLibrary
{
 struct ShaderFiles
 {
  std::string name = "";
  std::string vert = "";
  std::string geom = "";
  std::string frag = "";

  void addShaderPath(std::string& filepath, std::string& type)
  {
   if (type == "vert")
    vert = filepath;
   else if (type == "geom")
    geom = filepath;
   else if (type == "frag")
    frag = filepath;
  }
 };

 static std::vector<std::shared_ptr<Shader>> shaders;
 static std::shared_ptr<Shader> default_shader;

 static std::string readShaderFromFile(std::string& filepath);

public:
 static void init();
 static std::shared_ptr<Shader> getDefaultShader();
 static void setCameraMatrix(const glm::mat4& camMatrix);

 static std::shared_ptr<Shader> getShaderByIndex(int index) { return shaders[index]; };
 static int getNumShaders() { return (int)shaders.size(); };
 static std::shared_ptr<Shader> getShaderByName(std::string& name);

 friend class AssetLibrary;
 friend class Renderer;

};

}