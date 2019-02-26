#ifndef POEM_MENU_H
#define POEM_MENU_H

#include <list>
#include <string>

#include "../managers/FileManager.hpp"
#include "../menus/Menu.hpp"
#include "../menus/VerseMenu.hpp"

class PoemMenu : Menu {
  public:
    PoemMenu(const FileManager&, const VerseMenu&);

    void start();

  private:
    FileManager fileManager;
    VerseMenu verseMenu;

    std::list<std::string> verses;

    std::list<std::string>::iterator verseIterator;

    char option;

    void displayOptions() const;

    std::string getCurrentVerse() const;

    void goToFirstVerse();

    void goToLastVerse();

    void goToNextVerse();

    void goToPreviousVerse();

    void handleUserInput();

    bool isAtBeginning() const;

    bool isAtEnd() const;
};

#endif
