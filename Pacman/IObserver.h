#pragma once

template <class T>
class IObserver
{
  public:
    virtual void Update(T) = 0;
};