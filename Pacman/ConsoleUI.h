#pragma once
#include <Windows.h>
#include <string>
#include "GameUI.h"
#include "ConsoleColor.h"
#include "ConsoleTile.h"
using std::string;

class ConsoleUI : public GameUI
{
  public:
    ConsoleUI();
    virtual void setMazeWidthHeight(int width, int height) const override;

    virtual void displayMainMenu(vector<string>& menu, int selectedIndex) const override;
    virtual void draw(const GameState& gameState) const override;


  private:
    HANDLE hConsole_;
    color defaultColor_;

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
    void displayLevelScoreLives(const GameState& gameState) const;

    void setColor(color color) const;
    void displayColoredText(string text, color color) const;

    void displayTextByCoordinates(string text, int x, int y) const;
    void displayTextByCoordinates(string text, int x, int y, color color) const;
};

