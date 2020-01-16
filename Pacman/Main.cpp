#include "Game.h"


int main()
{
  ConsoleUI* consoleUI = new ConsoleUI();
  if (consoleUI != nullptr) {

    Game* game = new Game(consoleUI);
    if (game != nullptr) {
      game->run();
      delete game;
    }
    delete consoleUI;
  }

  return 0;
}