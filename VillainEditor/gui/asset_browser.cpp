#include "asset_browser.hpp"


namespace fs = std::filesystem;

namespace villain{

void AssetBrowser::init(const std::string& projectDirectory)
{
 m_rootDir = projectDirectory;
 m_currentDir = projectDirectory;
 for (const auto &entry : fs::directory_iterator(m_currentDir))
  m_entries.push_back({ entry.path().filename().string(), entry.is_directory()});
}

void AssetBrowser::render()
{
 if (ImGui::Begin("Asset Browser"))
 {
  if (ImGui::Selectable("..", false, ImGuiSelectableFlags_AllowDoubleClick) && m_currentDir != m_rootDir)
   if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
    update_entries("..");
  for (const auto &entry :m_entries)
  {
   if (entry.isDir)
   {
    auto flag = ImGuiSelectableFlags_AllowDoubleClick;
    if (ImGui::Selectable(entry.name.c_str(), false, flag))
     if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
     {
      AssetBrowser::update_entries(entry.name);
      break;
     }
   }
   else
    ImGui::Selectable(entry.name.c_str());
  }

 }
 ImGui::End();
}
void AssetBrowser::update_entries(const std::string &dirName)
{
 if (dirName == "..")
 {
  m_currentDir = fs::path{ m_currentDir }.parent_path().string();
  m_entries = {};
 }
 else
 {
  auto dirPath = fs::path(m_currentDir);
  auto filePath = fs::path(dirName);
  auto finPath = dirPath / filePath;
  m_currentDir = finPath.string();
  m_entries = {};
 }
 for (const auto &entry : fs::directory_iterator(m_currentDir))
  m_entries.push_back( { entry.path().filename().string(), entry.is_directory()});
}

}