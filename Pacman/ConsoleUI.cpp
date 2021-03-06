#include "ConsoleUI.h"
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <wincon.h>
using namespace std;

namespace pacman
{

  ConsoleUI::ConsoleUI()
  {
    hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole_, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole_, &cursorInfo);

    defaultColor_ = color::GRAY;
    setTiles();
  }



  void ConsoleUI::setTiles()
  {
    string space = " ";
    char c = ascii_tile::SMILE;
    pacmanTile_ =           ConsoleTile(space + c, color::YELLOW);
    ghostTile_ =            ConsoleTile(space + c, color::LIGHT_RED);
    frightenedGhostTile_ =  ConsoleTile(space + c, color::LIGHT_BLUE);
  
    dotTile_ =        ConsoleTile(" .", color::YELLOW);
    c = ascii_tile::ROMB;
    energizerTile_ =  ConsoleTile(space + c, color::YELLOW);
    c = ascii_tile::SPADE;
    fruitTile_ =      ConsoleTile(space + c, color::LIGHT_GREEN);
  
    wallTile_ =   ConsoleTile("##", color::LIGHT_BLUE);
    doorTile_ =   ConsoleTile("==", color::PINK);
    tunnelTile_ = ConsoleTile("  ");
    emptyTile_ =  ConsoleTile("  ");
  }



  void ConsoleUI::setMazeWidthHeight(int width, int height)
  {
    consoleWidth_ = width * 2;
    consoleHeight_ = height + 1;
    COORD crd = { consoleWidth_, consoleHeight_ };
    SMALL_RECT rect = { 0, 0, crd.X - 1, crd.Y - 1 };

    SetConsoleWindowInfo(hConsole_, true, &rect);
    SetConsoleScreenBufferSize(hConsole_, crd);
  }



  void ConsoleUI::displayMainMenu(vector<string>& menu, int selectedIndex) const
  {
    system("cls");
    color highlightedColor = color::YELLOW;

    const int startCoordinationX = 10;
    const int startCoordinationY = 10;
    const int verticalInterval = 2;

    for (int i = 0; i < menu.size(); i++) {
      int x = startCoordinationX;
      int y = startCoordinationY + verticalInterval * i;

      if (i == selectedIndex)
        displayTextByCoordinates(menu.at(i), x, y, highlightedColor);
      else
        displayTextByCoordinates(menu.at(i), x, y, defaultColor_);
    }
  }



  void ConsoleUI::displayMessage(string message) const
  {
    SetConsoleTextAttribute(hConsole_, BACKGROUND_BLUE | color::YELLOW);
    
    SHORT positionX = 0;
    SHORT positionY = consoleHeight_ / 4;
    SetConsoleCursorPosition(hConsole_, {positionX, positionY});
    
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < consoleWidth_; j++) {
        cout << " ";
      }
    }

    positionX = 5;
    positionY = positionY + 2;
    SetConsoleCursorPosition(hConsole_, { positionX, positionY });
    cout << message;

    setColor(defaultColor_);
    SetConsoleCursorPosition(hConsole_, { 0,0 });
  }



  inline void ConsoleUI::setColor(color color) const
  {
    SetConsoleTextAttribute(hConsole_, color);
  }



  void ConsoleUI::displayColoredText(string text, color color) const
  {
    setColor(color);
    cout << text;
    setColor(defaultColor_);
  }



  void ConsoleUI::displayTextByCoordinates(string text, int x, int y, color color) const
  {
    COORD crd = { x, y };
    SetConsoleCursorPosition(hConsole_, crd);
    displayColoredText(text, color);
  }



  void ConsoleUI::displayTextByCoordinates(string text, int x, int y) const
  {
    COORD crd = { x, y };
    SetConsoleCursorPosition(hConsole_, crd);
    cout << text;
  }



  void ConsoleUI::draw(const GameState& gameState) const
  {
    SetConsoleCursorPosition(hConsole_, { 0, 0 });
    drawMaze(gameState);
    drawPacman(gameState);
  }



  void ConsoleUI::drawMaze(const GameState& gameState) const
  {
    setColor(defaultColor_);

    const Maze* maze = gameState.getMaze();

    const int rows = maze->getRows();
    const int columns = maze->getColumns();

    const int emptyRows = 3;
    for (int i = 0; i < emptyRows; i++) {
      for (int j = 0; j < columns; j++) {
        displayColoredText(emptyTile_.tile, emptyTile_.color);
      }
    }
    displayLevelScore(gameState);


    Point pt;
    Cell cell;

    SetConsoleCursorPosition(hConsole_, { 0, emptyRows });

    for (int i = emptyRows; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        pt.y = i;
        pt.x = j;
        cell = maze->getCell(pt);

        if (cell.isWall) {
          displayColoredText(wallTile_.tile, wallTile_.color);
        }
        else if (cell.isDoor) {
          displayColoredText(doorTile_.tile, doorTile_.color);
        }
        else if (cell.isTunnel) {
          displayColoredText(tunnelTile_.tile, tunnelTile_.color);
        }
        else {
          switch (cell.food)
          {
          case food::EMPTY:
            displayColoredText(emptyTile_.tile, emptyTile_.color);
            break;
          case food::DOT:
            displayColoredText(dotTile_.tile, dotTile_.color);
            break;
          case food::ENERGIZER:
            displayColoredText(energizerTile_.tile, energizerTile_.color);
            break;
          case food::FRUIT:
            displayColoredText(fruitTile_.tile, fruitTile_.color);
            break;
          }
        }

      }
      //cout << endl;  // not necessary as we set console width height
    }

    displayLives(gameState);
  }



  void ConsoleUI::drawPacman(const GameState& gameState) const
  {
    Point pacman = gameState.getPacmanPosition();
    int x = pacman.x * 2;
    int y = pacman.y;
    displayTextByCoordinates(pacmanTile_.tile, x, y, pacmanTile_.color);
  }



  void ConsoleUI::drawGhosts(const GameState& gameState) const
  {
  
  }



  void ConsoleUI::displayLives(const GameState& gameState) const
  {
    const string lives = "Lives: " + to_string(gameState.getLives());
    displayTextByCoordinates(lives, 2, 35, color::YELLOW);
  }



  void ConsoleUI::displayLevelScore(const GameState& gameState) const
  {
    const string score = "Score: " + to_string(gameState.getScore());
    const string level = "Level " + to_string(gameState.getLevel());

    displayTextByCoordinates(level, 15, 0, color::LIGHT_CYAN);
    displayTextByCoordinates(score, 15, 1, color::WHITE);
  }

}