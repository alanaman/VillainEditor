#include "control_bar.hpp"

namespace villain {

ControlBar::ControlBar(Scene*& scene)
 :m_scene(scene)
{
}

void ControlBar::render()
{
 ImGuiWindowFlags window_flags = 0;

 window_flags |=
  ImGuiWindowFlags_NoTitleBar |
  ImGuiWindowFlags_NoScrollbar |
  ImGuiWindowFlags_NoResize |
  ImGuiWindowFlags_AlwaysAutoResize;

 ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 5));
 ImGui::Begin("ControlBar", NULL, window_flags);
 //ImGui::
 if (!m_scene->isPlaying())
 {
  if (ImGui::Button("Start", ImVec2(50, 50)))
   m_scene->startPlay();
 }
 else
 {
  if (ImGui::Button("Stop", ImVec2(50, 50)))
   m_scene->stopPlay();
 }
 ImGui::SameLine();
 if (ImGui::Button("Save", ImVec2(50, 50)))
  m_scene->saveScene();

 ImGui::End();
 ImGui::PopStyleVar();

}

}