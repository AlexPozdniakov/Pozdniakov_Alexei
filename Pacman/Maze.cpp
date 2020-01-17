#include <exception>
#include "Maze.h"

namespace pacman
{

  Maze::Maze()
  { 
    cells_ = new Cell*[rows_];

    for (int i = 0; i < rows_; i++) {
      cells_[i] = new Cell[columns_];
    }

    initStandardMaze();
  }



  Maze::~Maze()
  {
    if (cells_ != nullptr) {

      for (int i = 0; i < rows_; i++) {
        if (cells_[i] != nullptr) {
          delete[] cells_[i];
          cells_[i] = nullptr;
        }
      }
      delete[] cells_;
      cells_ = nullptr;
    }
  }



  void Maze::initStandardMaze()
  {
    if (rows_ < 36 || columns_ < 28) {
      throw std::exception("wrong row/column size");
    }

    char pacmanMap[36][29] = {
      "                            ",
      "                            ",
      "                            ",
      "wwwwwwwwwwwwwwwwwwwwwwwwwwww",
      "w............ww............w",
      "w.wwww.wwwww.ww.wwwww.wwww.w",
      "w@wwww.wwwww.ww.wwwww.wwww@w",
      "w.wwww.wwwww.ww.wwwww.wwww.w",
      "w..........................w",
      "w.wwww.ww.wwwwwwww.ww.wwww.w",
      "w.wwww.ww.wwwwwwww.ww.wwww.w",
      "w......ww....ww....ww......w",
      "wwwwww.wwwww ww wwwww.wwwwww",
      "     w.wwwww ww wwwww.w     ",
      "     w.ww          ww.w     ",
      "     w.ww wwwddwww ww.w     ",
      "wwwwww.ww w      w ww.wwwwww",
      "tttttt.   w      w   .tttttt",
      "wwwwww.ww w      w ww.wwwwww",
      "     w.ww wwwwwwww   .w     ",
      "     w.ww          ww.w     ",
      "     w.ww wwwwwwww ww.w     ",
      "wwwwww.ww wwwwwwww ww.wwwwww",
      "w............ww............w",
      "w.wwww.wwwww.ww.wwwww.wwww.w",
      "w.wwww.wwwww.ww.wwwww.wwww.w",
      "w@..ww.......  .......ww..@w",
      "www.ww.ww.wwwwwwww.ww.ww.www",
      "www.ww.ww.wwwwwwww.ww.ww.www",
      "w......ww....ww....ww......w",
      "w.wwwwwwwwww.ww.wwwwwwwwww.w",
      "w.wwwwwwwwww.ww.wwwwwwwwww.w",
      "w..........................w",
      "wwwwwwwwwwwwwwwwwwwwwwwwwwww",
      "                            ",
      "                            "
    };

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < columns_; j++) {
        char symbol = pacmanMap[i][j];
        Cell& cell = cells_[i][j];

        switch (symbol) {
          case 'w':
            cell.isWall = true;
            break;

          case 'd':
            cell.isDoor = true;
            break;

          case '.':
            cell.food = food::DOT;
            break;

          case '@':
            cell.food = food::ENERGIZER;
            break;

          case ' ':
            cell.food = food::EMPTY;
            break;

          case 't':
            cell.isTunnel = true;
            break;
        }

      }
    }

  }



  const Cell Maze::getCell(const Point& point) const
  {
    if (isCellInRange(point)) {
      return cells_[point.y][point.x];
    }
    else {
      throw std::exception("wrong point");
    }
  }



  void Maze::setFood(const Point cell, food food)
  {
    if (isCellInRange(cell)) {
      cells_[cell.y][cell.x].food = food;
    }
    else {
      throw std::exception("wrong point");
    }
  }



  const inline bool Maze::isCellInRange(const Point& point) const
  {
    return (point.x >= 0 && point.x < columns_ &&
      point.y >= 0 && point.y < rows_);
  }



  const int Maze::getColumns() const
  {
    return columns_;
  }



  const int Maze::getRows() const
  {
    return rows_;
  }

}