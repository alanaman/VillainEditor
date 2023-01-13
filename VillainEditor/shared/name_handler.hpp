#pragma once

#include "logging.hpp"


namespace villain {

class NameHandler
{
private:
 std::vector<std::reference_wrapper<std::string>> names;
 int getNumberExtension(const std::string& name);
 std::string getNext(std::string& name);

public:
 void addEntry(std::string& new_entry);
 void removeEntry(std::string& name);
 void rename(std::string& to_be_renamed, std::string new_name);

 void clear() { names.clear(); };


};

}