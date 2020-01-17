#include "Ghost.h"

namespace pacman
{

  Ghost::Ghost()
  {
  }



  Ghost::~Ghost()
  {
  }



  const Point Ghost::getCoordinates() const
  {
    return coordinates_;
  }



  const direction Ghost::getDirection() const
  {
    return direction_;
  }



  const ghost_type Ghost::getGhostType() const
  {
    return ghostType_;
  }



  const ghost_state Ghost::getGhostState() const
  {
    return ghostState_;
  }



  const bool Ghost::isFrightened() const
  {
    return isFrightened_;
  }



  const bool Ghost::isEye() const
  {
    return isEye_;
  }

}