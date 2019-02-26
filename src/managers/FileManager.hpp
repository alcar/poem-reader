#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <list>
#include <string>

#include "Manager.hpp"

class FileManager : Manager {
  public:
    FileManager(PerlWrapper *);

    std::list<std::string> chooseAndReadFile() const;

  private:
    std::string getFileNameInput() const;
};

#endif
