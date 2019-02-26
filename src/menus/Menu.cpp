#include <iostream>
#include <string>

#include "Menu.hpp"

using namespace std;

void Menu::displayOptionError() const {
  cout << "Error: invalid option." << '\n' << endl;
}

void Menu::displayOptionInputText() const {
  cout << "Please choose an option: ";
}

void Menu::displayOptions() const {
  cout << "Options:" << '\n';
  cout << "Q - Quit" << '\n' << endl;
}

void Menu::handleUserInput() {
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
      case 'Q':
      case 'q':
        break;

      default:
        displayOptionError();
    }
  }
}

void Menu::start() {
  do {
    handleUserInput();
  } while (option != 'Q' && option != 'q');
}
