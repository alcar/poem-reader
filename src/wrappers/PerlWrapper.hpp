#ifndef PERL_WRAPPER_H
#define PERL_WRAPPER_H

#include <EXTERN.h>
#include <perl.h>
#include <string>
#include <vector>

class PerlWrapper {
  public:
    PerlWrapper(int, char **, char **);

    ~PerlWrapper();

    std::string getWordMeaning(std::string) const;

    std::vector<std::string> getWordsFromVerse(std::string) const;

    bool isTextFile(std::string) const;

  private:
    PerlInterpreter *my_perl;
};

#endif
