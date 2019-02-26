#ifndef DIRECTORY_MANAGER_H
#define DIRECTORY_MANAGER_H

#include <string>

#include "Manager.hpp"

class DirectoryManager : Manager {
  public:
    DirectoryManager(PerlWrapper *);

    void displayTextFileList();

    void displayTextFilesTotal();
};

#endif
