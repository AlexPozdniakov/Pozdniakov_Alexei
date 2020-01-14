#include "Ghost.h"


Ghost::Ghost()
{
}



Ghost::~Ghost()
{
}



Point Ghost::getCoordinates() const
{
  return coordinates_;
}



direction Ghost::getDirection() const
{
  return direction_;
}



ghost_type Ghost::getGhostType() const
{
  return ghostType_;
}



ghost_state Ghost::getGhostState() const
{
  return ghostState_;
}



bool Ghost::isFrightened() const
{
  return isFrightened_;
}



bool Ghost::isEye() const
{
  return isEye_;
}
