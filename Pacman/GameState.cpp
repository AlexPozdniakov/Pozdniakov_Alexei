#include "GameState.h"

namespace pacman
{

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



  const bool GameState::isCellFree(const Point& cellPoint) const
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



  const bool GameState::isAjacentCellFree(const Point& cell, direction direction) const
  {
    Point nextPoint = getAdjacentCell(cell, direction);
    return isCellFree(nextPoint);
  }



  const Point GameState::getAdjacentCell(const Point& cell, direction direction) const
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



  const bool GameState::isPossibleMoveThroughTunnel(const Point& cell, direction direction) const
  {
    Cell startingCell = maze_->getCell(cell);

    if (startingCell.isTunnel == false) {
      return false;
    }
    int columns = maze_->getColumns();
    bool canMoveLeft = direction == direction::LEFT && cell.x == 0;
    bool canMoveRight = direction == direction::RIGHT && cell.x == columns - 1;

    return canMoveLeft || canMoveRight;
  }



  const bool GameState::isPossibleMove(const Point& cell, direction direction) const
  {
    return (isPossibleMoveThroughTunnel(cell, direction) || isAjacentCellFree(cell, direction));
  }



  const Point GameState::getNextMovePoint(const Point& cell, direction direction) const
  {
    if (isPossibleMoveThroughTunnel(cell, direction)) {
      Point nextPoint = cell;
      if (direction == direction::LEFT) {
        int columns = maze_->getColumns();
        nextPoint.x = columns - 1;
      }
      else if (direction == direction::RIGHT) {
        nextPoint.x = 0;
      }
      return nextPoint;
    }
    else {
      return getAdjacentCell(cell, direction);
    }
  }



  const bool GameState::isLevelComplete()
  {
    bool isLevelComplete = !(maze_->isThereAnyFood());
    if (isLevelComplete) {
      level_++;
    }
    return isLevelComplete;
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



  const int GameState::getScore() const
  {
    return score_;
  }



  const int GameState::getLives() const
  {
    return lives_;
  }



  const int GameState::getLevel() const
  {
    return level_;
  }



  void GameState::setFood(const Point cell, food food)
  {
    maze_->setFood(cell, food);
  }



  void GameState::resetFood()
  {
    maze_->resetFood();
  }

}