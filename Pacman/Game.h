#pragma once
#include <vector>
#include "GameUI.h"
#include "ConsoleUI.h"
#include "GameState.h"
#include "Event.h"
using std::vector;
using std::string;
class GameUI;


enum main_menu_options : char
{
  START_GAME,
  HIGH_SCORES,
  EXIT
};


class Game
{
  public:
    Game();
    ~Game();

    void run();
    void mainMenu();
    void startGame();

  private:
    GameState* gameState_;
    GameUI* gameUI_;
    bool isPaused_;

    vector<string> menuItems_;
    int selectedMenuItem_;

    Event<direction> changedPacmanDirectionEvent;

    void handleSelectedMenuItem(int menuItemIndex);
    void handlePacmanControl();
};

