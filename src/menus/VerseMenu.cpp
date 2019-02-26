#include <iostream>
#include <limits>

#include "VerseMenu.hpp"

using namespace std;

VerseMenu::VerseMenu(
  PerlWrapper* customPerlWrapperPtr
) : perlWrapperPtr(customPerlWrapperPtr) {}

void VerseMenu::displayMeaningError() const {
  cout << "There are no registered meanings for that word." << '\n' << endl;
}

void VerseMenu::displayOptions() const {
  cout << "Options:" << '\n';

  for (unsigned int i = 1; i <= words.size(); i++) {
    cout << i << " - \"" << words[i - 1] << '\"' << '\n';
  }

  cout << "0 - Return to the previous menu" << '\n' << endl;
}

string VerseMenu::getWordMeaning(string word) {
  return perlWrapperPtr->getWordMeaning(word);
}

vector<string> VerseMenu::getWordsFromVerse(string verse) {
  return perlWrapperPtr->getWordsFromVerse(verse);
}

void VerseMenu::handleUserInput() {
  displayOptions();

  displayOptionInputText();

  cin >> option;

  cout << endl;

  if (!cin || option < 0 || (unsigned) option > words.size()) {
    cin.clear();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    displayOptionError();
  } else if (option != 0) {
    string meaning = getWordMeaning(words[option - 1]);

    if (meaning.size() == 0) {
      displayMeaningError();
    } else {
      cout << meaning << endl;
    }
  }
}

void VerseMenu::start(string verse) {
  words = getWordsFromVerse(verse);

  do {
    handleUserInput();
  } while (option != 0);

  cin.clear();

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
