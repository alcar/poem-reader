#include <dirent.h>
#include <iostream>

#include "Manager.hpp"

using namespace std;

Manager::Manager(
  const PerlWrapper *customPerlWrapperPtr
) : perlWrapperPtr(customPerlWrapperPtr) {}

bool Manager::isTextFile(string fileName) {
  return perlWrapperPtr->isTextFile(fileName);
}
