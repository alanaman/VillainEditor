#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <functional>


#ifdef _MSC_VER
#define ERROR(x)  {std::cout<<"ERROR: "<<x<<std::endl;__debugbreak();}
#else
#define ERROR(x) std::cout<<x<<std::endl;\
exit(1);
#endif

#define INFO(x) std::cout<<x<<std::endl;

#define WARNING(x) std::cout<<"WARNING: "<<x<<std::endl;

#define ASSERT(x) if(!(x)) ERROR(#x);
