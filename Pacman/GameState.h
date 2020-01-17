#pragma once
#include "Maze.h"
#include "Pacman.h"

namespace pacman
{

  class Game;

  class GameState
  {
    public:
      GameState();
      ~GameState();

      const Maze* getMaze() const;
      const Point getPacmanPosition() const;
      void setPacmanStartPosition();

      const int getScore() const;
      const int getLives() const;
      const int getLevel() const;

      void setFood(const Point cell, food food);

      const bool isCellFree(const Point& cell) const;
      const bool isPossibleMove(const Point& cell, direction direction) const;
      const Point getNextMovePoint(const Point& cell, direction direction) const;

      friend Game;

    private:
      Maze* maze_;
      Pacman pacman_;

      int score_;
      int lives_;
      int level_;

      const bool isAjacentCellFree(const Point& cell, direction direction) const;
      const Point getAdjacentCell(const Point& cell, direction direction) const;
      const bool isPossibleMoveThroughTunnel(const Point& cell, direction direction) const;
  };

}