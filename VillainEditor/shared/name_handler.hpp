#pragma once

#include "logging.hpp"


namespace std {
template <>
struct std::hash<std::reference_wrapper<std::string>> {
 size_t operator()(const std::reference_wrapper<std::string>& x) const {
  return std::hash<std::string>()(x);
 }
};

template <>
struct std::equal_to<std::reference_wrapper<std::string>> {
 size_t operator()(const std::reference_wrapper<std::string>& a, const std::reference_wrapper<std::string>& b) const {
  return std::equal_to<std::string>()(a, b);
 }
};
}

namespace villain {

class NameHandler
{
private:
 std::unordered_set<std::reference_wrapper<std::string>> names;
 int getNumberExtension(const std::string& name);
 std::string getNext(std::string& name);

public:
 void addEntry(std::string& new_entry);
 void removeEntry(std::string& name);
 void rename(std::string& to_be_renamed, std::string new_name);

 void clear() { names.clear(); };


};

}