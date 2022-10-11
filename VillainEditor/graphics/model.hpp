#pragma once

#include <string>
#include <memory>

namespace villain {
class Model
{
protected:
 std::string m_name;
 std::string m_path;

public:
 static std::shared_ptr<Model> create(const std::string& name, const std::string& path);
 virtual void loadMeshes() = 0;
 virtual void draw() = 0;
};
}