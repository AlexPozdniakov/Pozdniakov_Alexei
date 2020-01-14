#pragma once
#include "MazeStructures.h"
#include "IObserver.h"

class GameState;

class Pacman : public IObserver<direction>
{
  public:
    Pacman(GameState& gameState);

    Point getCoordinates() const;
    direction getDirection() const;

    void setStartPosition();
    void Move();

    void Update(direction eventArgument) override;

  private:
    Point coordinates_;
    direction direction_;

    GameState& gameState_;
};

