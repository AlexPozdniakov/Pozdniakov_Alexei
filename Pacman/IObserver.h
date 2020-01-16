#pragma once

template <class T>
class IObserver
{
  public:
    virtual void update(const T) = 0;
};