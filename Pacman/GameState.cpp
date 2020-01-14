#include "GameState.h"


GameState::GameState() : pacman_(*this)
{
  maze_ = new Maze();
  lives_ = 3;
  score_ = 0;
  level_ = 1;

  pacman_.setStartPosition();
}



GameState::~GameState()
{
  if (maze_ != nullptr) {
    delete maze_;
    maze_ = nullptr;
  }
}



bool GameState::isCellFree(const Point& cellPoint) const
{
  bool isCellInRange = maze_->isCellInRange(cellPoint);
  if (isCellInRange) {
    Cell cell = maze_->getCell(cellPoint);
    return (cell.isDoor == false && cell.isWall == false);
  }
  else {
    return false;
  }
}



bool GameState::isAjacentCellFree(const Point& cell, direction direction) const
{
  Point nextPoint = getAdjacentCell(cell, direction);
  return isCellFree(nextPoint);
}



Point GameState::getAdjacentCell(const Point& cell, direction direction) const
{
  Point nextPoint = cell;
  switch (direction) {
    case NONE:
      return cell;
    case UP:
      nextPoint.y--;
      break;
    case RIGHT:
      nextPoint.x++;
      break;
    case DOWN:
      nextPoint.y++;
      break;
    case LEFT:
      nextPoint.x--;
      break;
  }
  return nextPoint;
}



void GameState::setPacmanStartPosition()
{
  pacman_.setStartPosition();
}



const Point GameState::getPacmanPosition() const
{
  return pacman_.getCoordinates();
}



const Maze* GameState::getMaze() const
{
  return maze_;
}



int GameState::getScore() const
{
  return score_;
}



int GameState::getLives() const
{
  return lives_;
}



int GameState::getLevel() const
{
  return level_;
}
