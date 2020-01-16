#pragma once
#include "MazeStructures.h"

enum ghost_type
{
  BLINKY,
  PINKY,
  CLYDE,
  INKY
};


enum ghost_state
{
  CHASE,
  SCATTER,
  FRIGHTENED
};


class Ghost
{
  public:
    Ghost();
    ~Ghost();

    virtual void setStartPosition() = 0;

    const Point getCoordinates() const;
    const direction getDirection() const;
    const ghost_type getGhostType() const;
    const ghost_state getGhostState() const;
    const bool isFrightened() const;
    const bool isEye() const;


  private:
    Point coordinates_;
    direction direction_;
    ghost_type ghostType_;
    ghost_state ghostState_;
    bool isFrightened_;
    bool isEye_;

};

