#include "window/filedialog.hpp"

#include <nfd.h>
#include <stdio.h>
#include <stdlib.h>

namespace villain {


std::string FileBrowser::selectFile()
{
 NFD_Init();

 nfdchar_t* outPath;
 nfdfilteritem_t filterItem[2] = { { "Source code", "c,cpp,cc" }, { "Headers", "h,hpp" } };
 nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 2, NULL);
 std::string s = "";
 if (result == NFD_OKAY)
 {
  s = outPath;
  NFD_FreePath(outPath);
 }
 //else if (result == NFD_CANCEL)
 //{
 // puts("User pressed cancel.");
 //}
 else
 {
  printf("Error: %s\n", NFD_GetError());
 }

 NFD_Quit();
 return s;
}
}