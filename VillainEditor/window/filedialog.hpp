#pragma once
#include "logging.hpp"

namespace villain {

class FileBrowser
{
public:
 static std::string selectFile();

 static std::string saveFile();

 static std::string selectDirectory();
};
}