#include <iostream>

#ifdef _MSC_VER
#define ERROR(x) __debugbreak();
#else
#define ERROR(x) std::cout<<x<<endl;\
exit(1);
#endif
