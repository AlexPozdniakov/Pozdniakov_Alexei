#pragma once
#include <string>
#include "ConsoleColor.h"
using std::string;

namespace pacman
{

  class ConsoleTile
  {
    public:
      string tile;
      color color;
      ConsoleTile(string tile_ = "  ", pacman::color color_ = color::GRAY) : tile(tile_), color(color_) { }
  };


  enum ascii_tile : unsigned char
  {
    DARK_SMILE = 1,
    SMILE = 2,
    HEART = 3,
    ROMB = 4,
    CLUBS = 5,
    SPADE = 6,
    TWO_EXLAMATION_MARKS = 19
  };

}