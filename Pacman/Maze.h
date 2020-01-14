#pragma once
#include "MazeStructures.h"

class Maze
{
  public:
    Maze();
    ~Maze();

    const Cell getCell(const Point& point) const;
    const int getColumns() const;
    const int getRows() const;

    inline bool isCellInRange(const Point& point) const;

  private:
    Cell** cells_;

    const int columns_ = 28;
    const int rows_ = 36;

    // for the size of 28x36 only
    void initStandardMaze();
};