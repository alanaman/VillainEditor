#pragma once

#include <imgui/imgui.h>
#include "logging.hpp"
#include <filesystem>


namespace villain {

class AssetBrowser
{
private:
 std::string m_rootDir;
 std::string m_currentDir;
 struct Entry
 {
  std::string name;
  bool isDir;
 };
 std::vector<Entry> m_entries;

public:
 void init(const std::string& projectDirectory);
 void render();
 void update_entries(const std::string &dirName);
 ~AssetBrowser()=default;
};
}