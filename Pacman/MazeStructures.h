#pragma once

class Point
{
  public:
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int X, int Y) : x(X), y(Y) {}
};


enum direction : char
{
  NONE,
  UP,
  RIGHT,
  DOWN,
  LEFT
};


enum food : char
{
  EMPTY,
  DOT,
  ENERGIZER,
  FRUIT
};


class Cell
{
  public:
    food food;
    bool isWall;
    bool isTunnel;
    bool isDoor;
    Cell() : food(food::EMPTY), isWall(false), isTunnel(false), isDoor(false) {}
};
