#pragma once
#include "MazeStructures.h"
#include "IObserver.h"

namespace pacman
{

  class GameState;

  class Pacman : public IObserver<direction>
  {
    public:
      Pacman(const GameState& gameState);

      const Point getCoordinates() const;
      const direction getDirection() const;

      void setStartPosition();
      void move();

      virtual void update(const direction eventArgument) override;

    private:
      Point coordinates_;
      direction direction_;

      const GameState& gameState_;
  };

}