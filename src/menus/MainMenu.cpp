#include <iostream>
#include <string>

#include "MainMenu.hpp"

using namespace std;

MainMenu::MainMenu(
  const DirectoryManager& customDirectoryManager,
  const PoemMenu& customPoemMenu
): directoryManager(customDirectoryManager), poemMenu(customPoemMenu) {}

void MainMenu::displayOptions() const {
  cout << "Options:" << '\n';
  cout << "L - List all text files" << '\n';
  cout << "T - Display the total number of text files" << '\n';
  cout << "O - Open a text file" << '\n';
  cout << "Q - Quit" << '\n' << endl;
}

void MainMenu::handleUserInput() {
  string fullOption;

  displayOptions();

  displayOptionInputText();

  getline(cin, fullOption);

  cout << endl;

  if (fullOption.size() > 1) {
    displayOptionError();
  } else {
    option = fullOption[0];

    switch (option) {
      case 'L':
      case 'l':
        directoryManager.displayTextFileList();

        break;

      case 'T':
      case 't':
        directoryManager.displayTextFilesTotal();

        break;

      case 'O':
      case 'o':
        poemMenu.start();

        break;

      case 'Q':
      case 'q':
        break;

      default:
        displayOptionError();
    }
  }
}

void MainMenu::start() {
  cout << "Welcome to Poem Reader!" << '\n' << endl;

  do {
    handleUserInput();
  } while (option != 'Q' && option != 'q');

  cout << "Thanks for using Poem Reader!" << endl;
}
