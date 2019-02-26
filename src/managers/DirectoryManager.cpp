#include <dirent.h>
#include <iostream>

#include "DirectoryManager.hpp"

using namespace std;

DirectoryManager::DirectoryManager(
  PerlWrapper *perlWrapperPtr
) : Manager(perlWrapperPtr) {}

void DirectoryManager::displayTextFileList() {
  struct dirent *dirEntry;
  DIR *dirStream;

  string fileName;

  bool hasFound = false;

  dirStream = opendir("./");

  while ((dirEntry = readdir(dirStream)) != NULL) {
    fileName = dirEntry->d_name;

    if (isTextFile(fileName)) {
      if (hasFound == false) {
        hasFound = true;

        cout << "Text files:" << endl;
      }

      cout << "- " << fileName << '\n';
    }
  }

  closedir(dirStream);

  if (hasFound == false) {
    cout << "There are no text files in the current directory." << endl;
  }

  cout << endl;
}

void DirectoryManager::displayTextFilesTotal() {
  struct dirent *dirEntry;
  DIR *dirStream;

  string fileName;
  unsigned int fileTotal = 0;

  dirStream = opendir("./");

  while ((dirEntry = readdir(dirStream)) != NULL) {
    fileName = dirEntry->d_name;

    if (isTextFile(fileName)) {
      fileTotal += 1;
    }
  }

  closedir(dirStream);

  cout << "Total number of text files: " << fileTotal << endl;

  cout << endl;
}
