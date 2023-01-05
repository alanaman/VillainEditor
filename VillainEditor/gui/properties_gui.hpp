#pragma once

#include "imgui/imgui.h"

#include "scene/properties.hpp"
#include "scene/entity.hpp"

namespace villain {

class PropertiesPanel
{

private:
 static bool show_properties_window;
 static Properties m_properties;


 static void inline renderFloatProperty(Property<float>* prop);
 static void inline renderVec3Property(Property<glm::vec3>* prop);
 static void inline renderIntProperty(Property<int>* prop);

public:
 static void onEntitySelection(std::shared_ptr<Entity> entity);


 static void render();
};
}