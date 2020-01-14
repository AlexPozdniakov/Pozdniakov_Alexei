#include "Pacman.h"
#include "GameState.h"


Pacman::Pacman(GameState& gameState) : gameState_(gameState)
{
  coordinates_.x = 0;
  coordinates_.y = 0;
  direction_ = direction::NONE;
}



void Pacman::setStartPosition()
{
  coordinates_.x = 13;
  coordinates_.y = 26;
  direction_ = direction::NONE;
}



void Pacman::Move()
{
  bool isAjacentCellFree = gameState_.isAjacentCellFree(coordinates_, direction_);
  if (isAjacentCellFree) {
    coordinates_ = gameState_.getAdjacentCell(coordinates_, direction_);
  }
}



void Pacman::Update(direction eventArgument)
{
  bool isAjacentCellFree = gameState_.isAjacentCellFree(coordinates_, eventArgument);
  if (isAjacentCellFree) {
    direction_ = eventArgument;
  }
}



Point Pacman::getCoordinates() const
{
  return coordinates_;
}



direction Pacman::getDirection() const
{
  return direction_;
}
