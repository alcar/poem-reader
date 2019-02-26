#ifndef MANAGER_H
#define MANAGER_H

#include <string>

#include "../wrappers/PerlWrapper.hpp"

class Manager {
  public:
    Manager(const PerlWrapper *);

  protected:
    const PerlWrapper *perlWrapperPtr;

    bool isTextFile(std::string fileName);
};

#endif
