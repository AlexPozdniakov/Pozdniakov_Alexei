#pragma once
#include <vector>
#include "GameState.h"
using std::string;
using std::vector;

namespace pacman
{

  class GameUI
  {
    public:
      virtual ~GameUI() {}
      virtual void setMazeWidthHeight(int width, int height) const = 0;
      virtual void displayMainMenu(vector<string>& menu, int selectedIndex) const = 0;
      // virtual void displayHighScores() = 0;
      virtual void draw(const GameState& gameState) const = 0;
  };

}