#pragma once

#include "imgui/imgui.h"

#include "properties.hpp"
#include "asset_library/meshlibrary.hpp"
#include "graphics/material.hpp"
#include "graphics/mesh.hpp"
#include "entity.hpp"

namespace villain {

class PropertiesPanel
{

private:
 static bool show_properties_window;
 static Properties m_properties;

 static std::shared_ptr<Entity> selected_entity;
 static int selected_material_id;
 static int selected_mesh_id;
 static std::shared_ptr<Shader> selected_shader;
 static std::vector<int> mesh_def_mats;

 static bool is_context_default;

 static void inline renderFloatProperty(Property<float>* prop);
 static void inline renderVec3Property(Property<glm::vec3>* prop);
 static void inline renderIntProperty(Property<int>* prop);
 static void inline renderTransformProperty(Property<Transform>* prop);
 static void inline renderMeshProperty(Property<std::shared_ptr<Mesh>>* prop);

 static void inline renderShaderProperty(Property<std::shared_ptr<Shader>>* prop);
 static void inline renderDefaultMaterialProperty();

 static void renderInstanceProperties();
 static void renderDefaultProperties();
public:
 static void render();

 static void onEntitySelection(std::shared_ptr<Entity> entity);
 static void onMeshSelection(int mesh_id);
 static void onMaterialSelection(int material_id);
 static void onShaderSelection(std::shared_ptr<Shader> shader);

 static void onSceneReload() {};

 static void clear();


};
}