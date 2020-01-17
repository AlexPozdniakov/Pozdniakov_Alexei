#include "Pacman.h"
#include "GameState.h"

namespace pacman
{

  Pacman::Pacman(const GameState& gameState) : gameState_(gameState)
  {
    coordinates_.x = 0;
    coordinates_.y = 0;
    direction_ = direction::NONE;
  }



  void Pacman::setStartPosition()
  {
    const int pacmanStartPositionX = 13;
    const int pacmanStartPositionY = 26;

    coordinates_.x = pacmanStartPositionX;
    coordinates_.y = pacmanStartPositionY;
    direction_ = direction::NONE;
  }



  void Pacman::move()
  {
    bool isPossibleMove = gameState_.isPossibleMove(coordinates_, direction_);
    if (isPossibleMove) {
      coordinates_ = gameState_.getNextMovePoint(coordinates_, direction_);
    }
  }



  void Pacman::update(const direction eventArgument)
  {
    bool isPossibleMove = gameState_.isPossibleMove(coordinates_, eventArgument);
    if (isPossibleMove) {
      direction_ = eventArgument;
    }
  }



  const Point Pacman::getCoordinates() const
  {
    return coordinates_;
  }



  const direction Pacman::getDirection() const
  {
    return direction_;
  }

}