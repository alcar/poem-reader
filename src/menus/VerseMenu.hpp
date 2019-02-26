#ifndef VERSE_MENU_H
#define VERSE_MENU_H

#include <string>
#include <vector>

#include "../menus/Menu.hpp"
#include "../wrappers/PerlWrapper.hpp"

class VerseMenu : Menu {
  public:
    VerseMenu(PerlWrapper*);

    void start(std::string);

  private:
    PerlWrapper *perlWrapperPtr;

    std::vector<std::string> words;

    int option;

    void displayMeaningError() const;

    void displayOptions() const;

    std::string getWordMeaning(std::string);

    std::vector<std::string> getWordsFromVerse(std::string);

    void handleUserInput();
};

#endif
