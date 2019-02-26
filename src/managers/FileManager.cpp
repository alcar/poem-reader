#include <iostream>

#include "FileManager.hpp"

using namespace std;

FileManager::FileManager(
  PerlWrapper *perlWrapperPtr
) : Manager(perlWrapperPtr) {}

list<string> FileManager::chooseAndReadFile() const {
  string currentLine;
  ifstream file;
  list<string> lineList;

  string fileName = getFileNameInput();

  bool isValidFileName = perlWrapperPtr->isTextFile(fileName);

  if (!isValidFileName) {
    return lineList;
  };

  file.open(fileName, ios_base::in);

  if (!file.is_open()) {
    return lineList;
  };

  while (getline(file, currentLine)) {
    if (currentLine != "") {
      lineList.push_back(currentLine);
    }
  }

  file.close();

  return lineList;
}

string FileManager::getFileNameInput() const {
  string fileName;

  cout << "Please enter a text file name (with its extension): ";

  getline(cin, fileName);

  cout << endl;

  return fileName;
}
