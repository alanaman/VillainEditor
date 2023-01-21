#include "name_handler.hpp"

//namespace std {
//template <>
//struct std::hash<std::reference_wrapper<std::string>> {
// size_t operator()(const std::reference_wrapper<std::string>& x) const {
//  return std::hash<std::string>()(x);
// }
//};
//
//template <>
//struct std::equal_to<std::reference_wrapper<std::string>> {
// size_t operator()(const std::reference_wrapper<std::string>& a, const std::reference_wrapper<std::string>& b) const {
//  return std::equal_to<std::string>()(a, b);
// }
//};
//}
namespace villain {

int NameHandler::getNumberExtension(const std::string& name)
{
 if (name.length() < 4)
  return -1;
 if (
  name[name.length() - 4] == '.' &&
  isdigit(name[name.length() - 3]) &&
  isdigit(name[name.length() - 2]) &&
  isdigit(name[name.length() - 1])
  )
 {
  return stoi(name.substr(name.length() - 3));
 }
 return -1;
}

void NameHandler::addEntry(std::string& new_entry)
{
 //auto x = names.find(new_entry);
 //if (x != names.end())
 //{
 // rename(x->get(), getNext(x->get()));
 //}
 //names.insert(new_entry);


}

void villain::NameHandler::removeEntry(std::string& name)
{
 //names.erase(name);
}

void NameHandler::rename(std::string& to_be_renamed, std::string new_name)
{
 /*auto x = names.find(new_name);
 if (x != names.end())
 {
  rename(x->get(), getNext(x->get()));
 }

 auto prev_entry = names.find(to_be_renamed);
 names.erase(prev_entry);
 prev_entry->get() = new_name;
 names.insert(*prev_entry);*/

}

std::string NameHandler::getNext(std::string& name)
{
 int ext = getNumberExtension(name);
 if (ext == -1)
  return name + ".001";
 std::string new_ext_string = std::to_string(ext + 1);

 return
  name.substr(0, name.length() - 3) +
  std::string('0', 3 - new_ext_string.length()) +
  new_ext_string;
}

}