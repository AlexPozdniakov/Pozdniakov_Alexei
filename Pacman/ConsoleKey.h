#pragma once

namespace pacman
{

  enum key : unsigned char
  {
    ARROW_UP = 72,
    ARROW_DOWN = 80,
    ARROW_LEFT = 75,
    ARROW_RIGHT = 77,
    SYMBOL_BEFORE_ARROWS = 224,

    RUS_W_CAPITAL = 150,
    RUS_S_CAPITAL = 155,
    RUS_A_CAPITAL = 148,
    RUS_D_CAPITAL = 130,

    RUS_W_LOWERCASE = 230,
    RUS_S_LOWERCASE = 235,
    RUS_A_LOWERCASE = 228,
    RUS_D_LOWERCASE = 162,

    RUS_P_CAPITAL = 135,
    RUS_P_LOWERCASE = 167,

    ENG_W_CAPITAL = 'W',
    ENG_S_CAPITAL = 'S',
    ENG_A_CAPITAL = 'A',
    ENG_D_CAPITAL = 'D',

    ENG_W_LOWERCASE = 'w',
    ENG_S_LOWERCASE = 's',
    ENG_A_LOWERCASE = 'a',
    ENG_D_LOWERCASE = 'd',

    ENG_P_CAPITAL = 'P',
    ENG_P_LOWERCASE = 'p',

    ENTER = 13,
    ESCAPE = 27
  };

}