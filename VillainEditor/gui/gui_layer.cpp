#include "gui_layer.hpp"

namespace villain {

GuiLayer::GuiLayer(void* window)
 :m_outliner(m_scene), m_controlbar(m_scene)
{
 // Setup Dear ImGui context
 //IMGUI_CHECKVERSION();
 ImGui::CreateContext();
 ImGuiIO& io = ImGui::GetIO();
 io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
 //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
 io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
 io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
 //io.ConfigViewportsNoAutoMerge = true;
 //io.ConfigViewportsNoTaskBarIcon = true;

 // Setup Dear ImGui style
 ImGui::StyleColorsDark();
 //ImGui::StyleColorsLight();

 // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
 ImGuiStyle& style = ImGui::GetStyle();
 if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
 {
  style.WindowRounding = 0.0f;
  style.Colors[ImGuiCol_WindowBg].w = 1.0f;
 }

 // Setup Platform/Renderer backends
 ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window, true);
 ImGui_ImplOpenGL3_Init("#version 130");

}

GuiLayer::~GuiLayer()
{
 ImGui::DestroyContext();
}

void GuiLayer::attachScene(Scene* scene)
{
 m_scene = scene;
}

void GuiLayer::render()
{
 // Start the Dear ImGui frame
 ImGui_ImplOpenGL3_NewFrame();
 ImGui_ImplGlfw_NewFrame();
 ImGui::NewFrame();
 if (ImGui::BeginMainMenuBar())
 {
  if (ImGui::BeginMenu("File"))
  {
   if (ImGui::MenuItem("New"))
   {
    Editor::getEditorInstance();
   }
   if (ImGui::MenuItem("Open", "Ctrl+O")) {}
   //if (ImGui::BeginMenu("Open Recent"))
   //{
   // for(file in recent)
   //  ImGui::MenuItem(file);
   // ImGui::EndMenu();
   //}
   ImGui::EndMenu();
  }
  if (ImGui::BeginMenu("Edit"))
  {
   if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
   if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
   ImGui::Separator();
   if (ImGui::MenuItem("Cut", "CTRL+X")) {}
   if (ImGui::MenuItem("Copy", "CTRL+C")) {}
   if (ImGui::MenuItem("Paste", "CTRL+V")) {}
   ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();
 }

 //for docking to main window
 ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

 if (show_demo_window)
  ImGui::ShowDemoWindow(&show_demo_window);

 PropertiesPanel::render();
 m_outliner.render();
 m_assetlib.render();
 m_controlbar.render();
 m_assetbrowser.render();

 ImGui::Render();

 ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
 ImGuiIO& io = ImGui::GetIO();
 if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
 {
  GLFWwindow* backup_current_context = glfwGetCurrentContext();
  ImGui::UpdatePlatformWindows();
  ImGui::RenderPlatformWindowsDefault();
  glfwMakeContextCurrent(backup_current_context);
 }
}

void GuiLayer::renderSelector()
{
 ImGui_ImplOpenGL3_NewFrame();
 ImGui_ImplGlfw_NewFrame();
 ImGui::NewFrame();
 ImGuiIO& io = ImGui::GetIO();

 ImGuiViewport* viewport = ImGui::GetMainViewport();
 ImGui::SetNextWindowPos(viewport->Pos);
 ImGui::SetNextWindowSize(viewport->Size);
 ImGui::SetNextWindowViewport(viewport->ID);

 ImGuiWindowFlags window_flags = 0;

 window_flags |=
  ImGuiWindowFlags_NoTitleBar |
  ImGuiWindowFlags_NoScrollbar |
  ImGuiWindowFlags_NoResize |
  ImGuiWindowFlags_AlwaysAutoResize |
  ImGuiWindowFlags_NoMove |
  ImGuiWindowFlags_NoDocking;

 ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
 ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(50, 50));
 ImGui::Begin("ControlBar", NULL, window_flags);
 
 struct TextFilters
 {
  // Return 0 (pass) if the character is letter digit or '_'
  static int imguiUpLowDigUndSc(ImGuiInputTextCallbackData* data)
  {
   //digits
   if (data->EventChar >= 48 && data->EventChar <= 57)
    return 0;
   //upper
   if (data->EventChar >= 65 && data->EventChar <= 90)
    return 0;
   //lower
   if (data->EventChar >= 97 && data->EventChar <= 122)
    return 0;
   //'_'
   if (data->EventChar == 95)
    return 0;
   return 1;
  }
 };

 static char projName[64] = "";
 if (ImGui::Button("New", ImVec2(100, 50)))
  Editor::getEditorInstance()->createNewProject(projName);
 ImGui::SameLine();
 ImGui::InputText("Project Name", projName, 64, ImGuiInputTextFlags_CallbackCharFilter, TextFilters::imguiUpLowDigUndSc);


 if (ImGui::Button("Select", ImVec2(100, 50)))
   Editor::getEditorInstance()->selectProject();

 ImGui::End();
 ImGui::PopStyleVar(2);

 if (show_demo_window)
  ImGui::ShowDemoWindow(&show_demo_window);

 ImGui::Render();

 ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
 io = ImGui::GetIO();
 if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
 {
  GLFWwindow* backup_current_context = glfwGetCurrentContext();
  ImGui::UpdatePlatformWindows();
  ImGui::RenderPlatformWindowsDefault();
  glfwMakeContextCurrent(backup_current_context);
 }
}


void GuiLayer::onSceneReload()
{
 m_outliner.onSceneReload();

}

void GuiLayer::setProjectDirectory(const std::string& projectDirectory)
{
 m_assetbrowser.init(projectDirectory);
}

float GuiLayer::getDeltaTime()
{
 return ImGui::GetIO().DeltaTime;
}
}