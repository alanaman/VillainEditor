#include <iostream>
#include <fstream>

#ifdef _MSC_VER
#define ERROR(x) __debugbreak();
#else
#define ERROR(x) std::cout<<x<<std::endl;\
exit(1);
#endif

#define INFO(x) std::cout<<x<<std::endl;
