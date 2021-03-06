#pragma once
#include "MazeStructures.h"

namespace pacman
{

  class Maze
  {
    public:
      Maze();
      ~Maze();

      const Cell getCell(const Point& point) const;
      const int getColumns() const;
      const int getRows() const;

      void setFood(const Point cell, food food);
      void resetFood();

      const inline bool isCellInRange(const Point& point) const;
      const bool isThereAnyFood() const;

    private:
      Cell** cells_;

      const int columns_ = 28;
      const int rows_ = 36;

      // for the size of 28x36 only
      void initStandardMaze();
  };

}