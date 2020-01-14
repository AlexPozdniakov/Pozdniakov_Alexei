#include "Game.h"


void main()
{
  Game* game = new Game();
  game->run();
  delete game;
}