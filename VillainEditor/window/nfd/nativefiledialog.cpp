#include "window/filedialog.hpp"

#include <nfd.h>
#include <stdio.h>
#include <stdlib.h>

namespace villain {


std::string FileBrowser::selectFile()
{
 NFD_Init();

 nfdchar_t* outPath;
 nfdresult_t result = NFD_OpenDialog(&outPath, NULL, 0, NULL);
 std::string s = "";
 if (result == NFD_OKAY)
 {
  s = outPath;
  NFD_FreePath(outPath);
 }
 else if (NFD_GetError())
 {
  ERROR(NFD_GetError());
 }

 NFD_Quit();
 return s;
}

std::string FileBrowser::saveFile()
{
 NFD_Init();

 nfdchar_t* outPath;
 nfdresult_t result = NFD_SaveDialog(&outPath, NULL, 0, NULL, NULL);
 std::string s = "";
 if (result == NFD_OKAY)
 {
  s = outPath;
  NFD_FreePath(outPath);
 }
 else if (NFD_GetError())
 {
  ERROR(NFD_GetError());
 }

 NFD_Quit();
 return s;
}

std::string FileBrowser::selectDirectory()
{
 NFD_Init();

 nfdchar_t* outPath;
 nfdresult_t result = NFD_PickFolder(&outPath, NULL);
 std::string s = "";
 if (result == NFD_OKAY)
 {
  s = outPath;
  NFD_FreePath(outPath);
 }
 else if(NFD_GetError())
 {
  ERROR(NFD_GetError());
 }

 NFD_Quit();
 return s;
}

}