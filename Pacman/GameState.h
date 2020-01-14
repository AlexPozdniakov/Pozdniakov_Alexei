#pragma once
#include "Maze.h"
#include "Pacman.h"

class Game;

class GameState
{
  public:
    GameState();
    ~GameState();

    const Maze* getMaze() const;
    const Point getPacmanPosition() const;
    void setPacmanStartPosition();

    int getScore() const;
    int getLives() const;
    int getLevel() const;

    bool isCellFree(const Point& cell) const;
    bool isAjacentCellFree(const Point& cell, direction direction) const;
    Point getAdjacentCell(const Point& cell, direction direction) const;

    friend Game;

  private:
    Maze* maze_;
    Pacman pacman_; 

    int score_;
    int lives_;
    int level_;

};

