#include "window/filedialog.hpp"

#include <nfd.h>
#include <stdio.h>
#include <stdlib.h>

namespace villain {


std::string FileBrowser::selectFile()
{
 NFD_Init();

 nfdchar_t* outPath;
 //nfdfilteritem_t filterItem[1] = { { "All", "" } };
 nfdresult_t result = NFD_OpenDialog(&outPath, NULL, 0, NULL);
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

std::string FileBrowser::saveFile()
{
 NFD_Init();

 nfdchar_t* outPath;
 //nfdfilteritem_t filterItem[1] = { { "All", "" } };
 nfdresult_t result = NFD_SaveDialog(&outPath, NULL, 0, NULL, NULL);
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