#pragma once
#include <vector>
#include "GameUI.h"
#include "ConsoleUI.h"
#include "GameState.h"
#include "Event.h"
using std::vector;
using std::string;
class GameUI;

namespace pacman
{

  enum main_menu_options : char
  {
    START_GAME,
    HIGH_SCORES,
    EXIT
  };


  class Game
  {
    public:
      Game(GameUI* gameUI);
      ~Game();

      void run();
      void mainMenu();
      void startGame();

    private:
      GameState* gameState_;
      GameUI* gameUI_;
      bool isPaused_;

      int pointsForDot_;
      int pointsForEnergizer_;

      vector<string> menuItems_;
      int selectedMenuItem_;

      Event<direction> changedPacmanDirectionEvent_;

      void handleSelectedMenuItem(const int menuItemIndex);
      void handlePacmanControl();

      void eatFood();
  };

}