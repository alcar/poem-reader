#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../managers/DirectoryManager.hpp"
#include "../menus/Menu.hpp"
#include "../menus/PoemMenu.hpp"

class MainMenu : Menu {
  public:
    MainMenu(const DirectoryManager&, const PoemMenu&);

    void start();

  private:
    DirectoryManager directoryManager;
    PoemMenu poemMenu;

    char option;

    void displayOptions() const;

    void handleUserInput();
};

#endif
