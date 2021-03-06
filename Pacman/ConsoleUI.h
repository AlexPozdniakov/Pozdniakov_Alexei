#pragma once
#include <Windows.h>
#include <string>
#include "GameUI.h"
#include "ConsoleColor.h"
#include "ConsoleTile.h"
using std::string;

namespace pacman
{

  class ConsoleUI : public GameUI
  {
    public:
      ConsoleUI();
      virtual void setMazeWidthHeight(int width, int height) override;

      virtual void displayMainMenu(vector<string>& menu, int selectedIndex) const override;
      virtual void displayMessage(string message) const override;
      virtual void draw(const GameState& gameState) const override;


    private:
      HANDLE hConsole_;
      color defaultColor_;
      int consoleWidth_;
      int consoleHeight_;

      ConsoleTile pacmanTile_;
      ConsoleTile ghostTile_;
      ConsoleTile frightenedGhostTile_;
      ConsoleTile wallTile_;
      ConsoleTile doorTile_;
      ConsoleTile tunnelTile_;
      ConsoleTile emptyTile_;
      ConsoleTile dotTile_;
      ConsoleTile energizerTile_;
      ConsoleTile fruitTile_;

      void setTiles();

      void drawMaze(const GameState& gameState) const;
      void drawPacman(const GameState& gameState) const;
      void drawGhosts(const GameState& gameState) const;
      void displayLives(const GameState& gameState) const;
      void displayLevelScore(const GameState& gameState) const;

      inline void setColor(color color) const;
      void displayColoredText(string text, color color) const;

      void displayTextByCoordinates(string text, int x, int y) const;
      void displayTextByCoordinates(string text, int x, int y, color color) const;
  };

}