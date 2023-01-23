#include "name_handler.hpp"


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

//int NameHandler::getIndex(std::string& name)
//{
 //for (int idx=0;idx<names.size();idx++)
 //{
 // if (name.get() == names[idx].get())
 //  return idx;
 //}
 //return -1;
//}

void NameHandler::addEntry(std::string& new_entry)
{
 //auto idx = getIndex(new_entry);
 //if (idx==-1)
 //{
 // rename(names[idx].get(), getNext(names[idx].get()));
 //}
 //names.push_back(new_entry);
 auto x = names.find(new_entry);
 if (x != names.end())
 {
  rename(x->get(), getNext(x->get()));
 }
 names.insert(new_entry);
}

void villain::NameHandler::removeEntry(std::string& name)
{
 names.erase(name);
}

void NameHandler::rename(std::string& to_be_renamed, std::string new_name)
{
 auto x = names.find(new_name);
 if (x != names.end())
 {
  rename(x->get(), getNext(x->get()));
 }

 auto prev_entry = names.find(to_be_renamed);
 names.erase(prev_entry);
 to_be_renamed = new_name;
 names.insert(to_be_renamed);

}

std::string NameHandler::getNext(std::string& name)
{
 int ext = getNumberExtension(name);
 if (ext == -1)
  return name + ".001";
 std::string new_ext_string = std::to_string(ext + 1);

 return
  name.substr(0, name.length() - 3) +
  std::string(3 - new_ext_string.length(), '0') +
  new_ext_string;
}

}