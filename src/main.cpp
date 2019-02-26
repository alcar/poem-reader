#include <iostream>

#include "managers/DirectoryManager.hpp"
#include "managers/FileManager.hpp"
#include "menus/MainMenu.hpp"
#include "menus/PoemMenu.hpp"
#include "menus/VerseMenu.hpp"
#include "wrappers/PerlWrapper.hpp"

using namespace std;

int main(int argc, char **argv, char **env) {
  PerlWrapper *perlWrapperPtr = new PerlWrapper(argc, argv, env);

  DirectoryManager directoryManager(perlWrapperPtr);
  FileManager fileManager(perlWrapperPtr);
  VerseMenu verseMenu(perlWrapperPtr);

  PoemMenu poemMenu(fileManager, verseMenu);

  MainMenu mainMenu(directoryManager, poemMenu);

  mainMenu.start();

  return 0;
}
