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

 
 // Load Fonts
// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
// - Read 'docs/FONTS.md' for more instructions and details.
// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
//io.Fonts->AddFontDefault();
//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
//IM_ASSERT(font != NULL);
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

 //for docking to main window
 ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

 // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
 if (show_demo_window)
  ImGui::ShowDemoWindow(&show_demo_window);

 //ImGui::ShowExampleAppWindowTitles(&x);

 // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
 {
  static float f = 0.0f;

  ImGui::Begin("Properties", &show_properties_window);                          // Create a window called "Hello, world!" and append into it.


  auto entity = m_outliner.getSelectedEntity();
  if (entity)
  {
   Transform& trans = entity->getLocalTransformRef();
   ImGui::Text("Transform");               // Display some text (you can use a format strings too)

   ImGui::DragFloat3("Position", &trans.getPositionRef()[0]);
   ImGui::DragFloat3("Scale", &trans.getScaleRef()[0]);
   ImGui::DragFloat3("Rotation", &trans.getRotationRef()[0]);
  //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
   std::vector<std::shared_ptr<Property>> properties;
   entity->collectProperties(properties);

   for (auto property : properties)
   {
    switch (property->getType())
    {
    case PropertyType::FLOAT:
    {
     ImGui::DragFloat(
      property->name.c_str(),
      &(std::dynamic_pointer_cast<PropertyFloat>(property)->val)
     );
     break;
    }
    //case PropertyType::INT:
    //{
    // ImGui::DragInt(property->name.c_str(), (int*)property->value_ptr);
    // break;
    //}
    //case PropertyType::VEC3:
    //{
    // ImGui::DragFloat3(property->name.c_str(), (float*)property->value_ptr);
    // break;
    //}
    default:
     break;
    }
   }
  }
  //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::End();
 }

 m_outliner.render();
 m_assetlib.render();
 m_controlbar.render();

 // 3. Show another simple window.
 if (show_another_window)
 {
  ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
  ImGui::Text("Hello from another window!");
  if (ImGui::Button("Close Me"))
   show_another_window = false;
  ImGui::End();
 }

 // Rendering
 ImGui::Render();

 ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
 // Update and Render additional Platform Windows
// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
 ImGuiIO& io = ImGui::GetIO();
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
}