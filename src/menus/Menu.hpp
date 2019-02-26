#ifndef MENU_H
#define MENU_H

class Menu {
  public:
    virtual void start();

  protected:
    void displayOptionError() const;

    void displayOptionInputText() const;

  private:
    char option;

    virtual void displayOptions() const;

    virtual void handleUserInput();
};

#endif
