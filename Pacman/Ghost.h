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


class Ghost abstract
{
  public:
    Ghost();
    ~Ghost();

    virtual void setStartPosition() = 0;

    Point getCoordinates() const;
    direction getDirection() const;
    ghost_type getGhostType() const;
    ghost_state getGhostState() const;
    bool isFrightened() const;
    bool isEye() const;


  private:
    Point coordinates_;
    direction direction_;
    ghost_type ghostType_;
    ghost_state ghostState_;
    bool isFrightened_;
    bool isEye_;

};

