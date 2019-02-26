#include <iostream>

#include "PoemMenu.hpp"

using namespace std;

PoemMenu::PoemMenu(
  const FileManager& customFileManager,
  const VerseMenu& customVerseMenu
) : fileManager(customFileManager), verseMenu(customVerseMenu) {}

void PoemMenu::displayOptions() const {
  cout << "Current verse:" << '\n';
  cout << getCurrentVerse() << '\n' << endl;

  cout << "Options:" << '\n';

  if (!isAtBeginning()) {
    cout << "P - Go to the previous verse" << '\n';
  }

  if (!isAtEnd()) {
    cout << "N - Go to the next verse" << '\n';
  }

  cout << "M - Get the meaning of a word from the current verse" << '\n';

  if (!isAtBeginning()) {
    cout << "F - Go to the first verse" << '\n';
  }

  if (!isAtEnd()) {
    cout << "L - Go to the last verse" << '\n';
  }

  cout << "Q - Close the file and return to the main menu" << '\n' << endl;
}

string PoemMenu::getCurrentVerse() const {
  return *verseIterator;
}

void PoemMenu::goToFirstVerse() {
  verseIterator = verses.begin();
}

void PoemMenu::goToLastVerse() {
  verseIterator = prev(verses.end(), 1);
}

void PoemMenu::goToNextVerse() {
  verseIterator = next(verseIterator);
}

void PoemMenu::goToPreviousVerse() {
  verseIterator = prev(verseIterator);
}

void PoemMenu::handleUserInput() {
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
      case 'P':
      case 'p':
        if (isAtBeginning()) {
          displayOptionError();
        } else {
          goToPreviousVerse();
        }

        break;

      case 'N':
      case 'n':
        if (isAtEnd()) {
          displayOptionError();
        } else {
          goToNextVerse();
        }

        break;

      case 'M':
      case 'm':
        verseMenu.start(getCurrentVerse());

        break;

      case 'F':
      case 'f':
        if (isAtBeginning()) {
          displayOptionError();
        } else {
          goToFirstVerse();
        }

        break;

      case 'L':
      case 'l':
        if (isAtEnd()) {
          displayOptionError();
        } else {
          goToLastVerse();
        }

        break;

      case 'Q':
      case 'q':
        break;

      default:
        displayOptionError();
    }
  }
}

bool PoemMenu::isAtBeginning() const {
  return verseIterator == verses.begin();
}

bool PoemMenu::isAtEnd() const {
  return next(verseIterator) == verses.end();
}

void PoemMenu::start() {
  verses = fileManager.chooseAndReadFile();

  if (verses.empty()) {
    cout << "Error: invalid file." << '\n' << endl;
  } else {
    verseIterator = verses.begin();

    do {
      handleUserInput();
    } while (option != 'Q' && option != 'q');
  }
}
