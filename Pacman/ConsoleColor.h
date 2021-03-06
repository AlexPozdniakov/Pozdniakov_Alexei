#pragma once
#include <Windows.h>

namespace pacman
{

  enum color : char
  {
    DARK_BLUE =   FOREGROUND_BLUE,
    DARK_GREEN =  FOREGROUND_GREEN,
    DARK_RED =    FOREGROUND_RED,
    LIGHT_BLUE =  FOREGROUND_BLUE   | FOREGROUND_INTENSITY,
    LIGHT_GREEN = FOREGROUND_GREEN  | FOREGROUND_INTENSITY,
    LIGHT_RED =   FOREGROUND_RED    | FOREGROUND_INTENSITY,

    BLACK =       0,
    DARK_GRAY =   FOREGROUND_INTENSITY,
    GRAY =        FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN,
    WHITE =       FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,

    DARK_CYAN =   FOREGROUND_BLUE | FOREGROUND_GREEN,
    LIGHT_CYAN =  FOREGROUND_BLUE | FOREGROUND_GREEN  | FOREGROUND_INTENSITY,

    MAGNETA =     FOREGROUND_RED | FOREGROUND_BLUE,
    PINK =        FOREGROUND_RED | FOREGROUND_BLUE    | FOREGROUND_INTENSITY,

    DARK_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
    YELLOW =      FOREGROUND_RED | FOREGROUND_GREEN   | FOREGROUND_INTENSITY
  };

}