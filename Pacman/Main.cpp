#include <iostream>
#include <conio.h>
#include <exception>
#include "Game.h"
using std::exception;

int main()
{
  ConsoleUI* consoleUI = new ConsoleUI();
  if (consoleUI != nullptr) {

    Game* game = new Game(consoleUI);
    if (game != nullptr) {

      try {
        game->run();
      }
      catch (exception e) {
        system("cls");
        std::cout << e.what() << std::endl;
        _getch();
      }

      delete game;
    }
    delete consoleUI;
  }

  return 0;
}