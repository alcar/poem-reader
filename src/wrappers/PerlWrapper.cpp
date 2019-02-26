#include <algorithm>

#include "PerlWrapper.hpp"

using namespace std;

PerlWrapper::PerlWrapper(int argc, char **argv, char **env) {
  char *parserArgv[] = { (char *) "", (char *) "src/utils/poemSquire.pl" };

  PERL_SYS_INIT3(&argc, &argv, &env);

  my_perl = perl_alloc();

  perl_construct(my_perl);

  perl_parse(my_perl, NULL, argc, parserArgv, env);

  PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
}

PerlWrapper::~PerlWrapper() {
  perl_destruct(my_perl);

  perl_free(my_perl);

  PERL_SYS_TERM();
}

string PerlWrapper::getWordMeaning(string word) const {
  dSP;

  ENTER;
  SAVETMPS;

  PUSHMARK(SP);

  XPUSHs(sv_2mortal(newSVpv(word.c_str(), word.size())));

  PUTBACK;

  call_pv("getWordMeaning", G_SCALAR);

  SPAGAIN;

  string meaning = POPp;

  PUTBACK;

  FREETMPS;
  LEAVE;

  return meaning;
}

vector<string> PerlWrapper::getWordsFromVerse(string verse) const {
  dSP;

  unsigned int wordCount;
  vector<string> wordList;

  ENTER;
  SAVETMPS;

  PUSHMARK(SP);

  XPUSHs(sv_2mortal(newSVpv(verse.c_str(), verse.size())));

  PUTBACK;

  wordCount = call_pv("getWordsFromVerse", G_ARRAY);

  SPAGAIN;

  for (unsigned int i = 0; i < wordCount; i++) {
    wordList.push_back(POPp);
  }

  PUTBACK;

  FREETMPS;
  LEAVE;

  reverse(wordList.begin(), wordList.end());

  return wordList;
}

bool PerlWrapper::isTextFile(string fileName) const {
  dSP;

  ENTER;
  SAVETMPS;

  PUSHMARK(SP);

  XPUSHs(sv_2mortal(newSVpv(fileName.c_str(), fileName.size())));

  PUTBACK;

  call_pv("isTextFile", G_SCALAR);

  SPAGAIN;

  unsigned int result = POPi;

  PUTBACK;

  FREETMPS;
  LEAVE;

  if (result == 0) {
    return false;
  }

  return true;
}
